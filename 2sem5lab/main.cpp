#include <iostream>
#include <algorithm>

template <class Value_T>
class CircleBuffer
{
private:
    int capacity_ = 0;
    Value_T* data_;
    Value_T* dataEnd_;
    int firstEl_ = 0;
    int endEl_ = 0;
public:
    class CircleIterator: public std::iterator<std::random_access_iterator_tag, Value_T>
    {
    private:
        CircleBuffer<Value_T>* buffer_ = NULL;
        int index_ = 0;
    public:
        CircleIterator() = default;
        CircleIterator(CircleBuffer<Value_T>& buffer, int index)
        : buffer_(&buffer),
        index_((index - buffer.indexOfFirst() + buffer.capasity()) % buffer.capasity())
        {}
        CircleIterator &operator=(const CircleIterator &other) = default;

        bool operator==(const CircleIterator &other) const
        {
            return index_ == other.index_;
        }

        bool operator!=(const CircleIterator &other) const
        {
            return !*this == other;
        }

        CircleIterator &operator+=(int ind)
        {
            index_ = ((index_ + ind) % buffer_->capasity() + buffer_->capasity()) % buffer_->capasity();
            return *this;
        }

        CircleIterator &operator-=(int ind)
        {
            index_ = ((index_ - ind) % buffer_->capasity() + buffer_->capasity()) % buffer_->capasity();
            return *this;
        }

        CircleIterator operator+(int ind) const
        {
            CircleIterator other = *this;
            other += ind;
            return other;
        }

        size_t operator-(const CircleIterator &other) const
        {
            return ((index_ - other.index_ + buffer_->capasity()) % buffer_->capasity()) * sizeof(Value_T);
        }

        CircleIterator operator++()
        {
            CircleIterator other = *this;
            operator+=(1);
            return other;
        }

        CircleIterator operator--()
        {
            CircleIterator other = *this;
            operator-=(1);
            return other;
        }

        CircleIterator &operator++(int)
        {
            operator+=(1);
            return *this;
        }

        CircleIterator &operator--(int)
        {
            operator-=(1);
            return *this;
        }

        CircleIterator operator-(int ind) const
        {
            CircleIterator other = *this;
            other -= ind;
            return other;
        }

        Value_T &operator[](int ind)
        {
            return *(buffer_->data() + ((index_ + ind) % buffer_->capasity() + buffer_->capasity()) % buffer_->capasity());
        }

        Value_T &operator*()
        {
            return operator[](0);
        }
        bool operator> (const CircleIterator& other) const
        {
            return (index_ - buffer_->indexOfFirst() + buffer_->capacity_) % buffer_->capacity_ >
                   (other.index_ - buffer_->indexOfFirst() + buffer_->capacity_) % buffer_->capacity_;
        }
        bool operator>= (const CircleIterator& other) const
        {
            return (index_ - buffer_->indexOfFirst() + buffer_->capacity_) % buffer_->capacity_ >=
                   (other.index_ - buffer_->indexOfFirst() + buffer_->capacity_) % buffer_->capacity_;
        }
        bool operator< (const CircleIterator& other) const
        {
            return !operator>=(other);
        }
        bool operator<= (const CircleIterator& other) const
        {
            return !operator>(other);
        }
    };
    class CircleIteratorConst: public std::iterator<std::random_access_iterator_tag, Value_T>
            {
    private:
        const CircleBuffer<Value_T>& buffer_;
        int index_ = 0;
    public:
        CircleIteratorConst() = default;
        CircleIteratorConst(const CircleBuffer<Value_T>& buffer, int index)
                : buffer_(buffer),
                  index_((index - buffer.indexOfFirst() + buffer.capasity()) % buffer.capasity())
        {}
        CircleIteratorConst &operator=(const CircleIteratorConst &other) = default;

        bool operator==(const CircleIteratorConst &other) const
        {
            return index_ == other.index_;
        }

        bool operator!=(const CircleIteratorConst &other) const
        {
            return !*this == other;
        }

        CircleIteratorConst &operator+=(int ind)
        {
            index_ = ((index_ + ind) % buffer_.capasity() + buffer_.capasity()) % buffer_.capasity();
            return *this;
        }

        CircleIterator &operator-=(int ind)
                {
            index_ = ((index_ - ind) % buffer_.capasity() + buffer_.capasity()) % buffer_.capasity();
            return *this;
        }

        CircleIteratorConst operator+(int ind) const
        {
            CircleIteratorConst other = *this;
            other += ind;
            return other;
        }

        size_t operator-(const CircleIteratorConst &other) const
        {
            return ((index_ - other.index_ + buffer_.capasity()) % buffer_.capasity()) * sizeof(Value_T);
        }

        CircleIteratorConst operator++()
        {
            CircleIteratorConst other = *this;
            operator+=(1);
            return other;
        }

        CircleIteratorConst operator--()
        {
            CircleIterator other = *this;
            operator-=(1);
            return other;
        }

        CircleIteratorConst &operator++(int)
        {
            operator+=(1);
            return *this;
        }

        CircleIteratorConst &operator--(int)
        {
            operator-=(1);
            return *this;
        }

        CircleIteratorConst operator-(int ind) const
        {

            CircleIteratorConst other = *this;
            other -= ind;
            return other;
        }

        const Value_T &operator[](int ind) const
        {
            return *(buffer_.data() + ((index_ + ind) % buffer_.capasity() + buffer_.capasity()) % buffer_.capasity());
        }

        const Value_T &operator*() const
        {
            return operator[](0);
        }
        bool operator> (const CircleIteratorConst& other) const
        {
            return (index_ - buffer_.indexOfFirst() + buffer_.capacity_) % buffer_.capacity_ >
                   (other.index_ - buffer_.indexOfFirst() + buffer_.capacity_) % buffer_.capacity_;
        }
        bool operator>= (const CircleIteratorConst& other) const
        {
            return (index_ - buffer_.indexOfFirst() + buffer_.capacity_) % buffer_.capacity_ >=
                   (other.index_ - buffer_.indexOfFirst() + buffer_.capacity_) % buffer_.capacity_;
        }
        bool operator< (const CircleIteratorConst& other) const
        {
            return !operator>=(other);
        }
        bool operator<= (const CircleIteratorConst& other) const
        {
            return !operator>(other);
        }
    };
    CircleBuffer() = default;
    explicit CircleBuffer(int s)
    : capacity_(s + 1),
    firstEl_(0),
    endEl_(0)
    {
        data_ = new Value_T(s + 1);
        dataEnd_ = data_ + capacity_;
    }
    bool isFull()
    {
        return ((firstEl_ - endEl_) + capacity_) % capacity_ == 1;
    }
    bool isEmpty()
    {
        return endEl_ - firstEl_ == 0;
    }
    bool push_back(const Value_T& i)
    {
        if (isFull())
            return false;
        data_[endEl_] = i;
        endEl_ = (endEl_ + 1 + capacity_) % capacity_;
        return true;
    }
    bool push_front(const Value_T& i)
    {
        if (isFull())
            return false;
        firstEl_ = (firstEl_ - 1 + capacity_) % capacity_;
        data_[firstEl_] = i;
        return true;
    }
    bool pop_front()
    {
        if (isEmpty())
            return false;
        firstEl_++;
        return true;
    }
    bool pop_back()
    {
        if (isEmpty())
            return false;
        endEl_--;
        return true;
    }
    Value_T& operator[](int index)
    {
        int k = (firstEl_ + index % capacity_ + capacity_) % capacity_;
        if ((endEl_ > firstEl_ && firstEl_ <= k && k < endEl_) ||
            ((endEl_ < firstEl_) && !(firstEl_ <= k && k < endEl_)))
                return data_[k];
        throw std::invalid_argument("Out of range");
    }
    const Value_T& operator[](int index) const
    {
        int k = (firstEl_ + index % capacity_ + capacity_) % capacity_;
        if ((endEl_ > firstEl_ && firstEl_ <= k && k < endEl_) ||
            ((endEl_ < firstEl_) && !(firstEl_ <= k && k < endEl_)))
            return data_[k];
        throw std::invalid_argument("Out of range");
    }
    Value_T& front()
    {
        return data_[firstEl_];
    }
    const Value_T& front() const
    {
        return data_[firstEl_];
    }
    Value_T& back()
    {
        return data_[endEl_ - 1];
    }
    const Value_T& back() const
    {
        return data_[endEl_ - 1];
    }
    Value_T* data() const
    {
        return data_;
    }
    int capasity() const
    {
        return capacity_;
    }
    CircleIterator begin()
    {
        return CircleIterator(*this, firstEl_);
    }
    CircleIterator end()
    {
        return CircleIterator(*this, endEl_);
    }
    CircleIteratorConst begin() const
    {
        return CircleIteratorConst(*this, firstEl_);
    }
    CircleIteratorConst end() const
    {
        return CircleIteratorConst(*this, endEl_);
    }
    int indexOfFirst() const
    {
        return firstEl_;
    }
    void changeCapacity(int k)
    {
        Value_T* n = new Value_T(k + 1);
        int e = std::min((endEl_ - firstEl_ + capacity_) % capacity_, k);
        for (int i = 0; i < e; i++)
        {
            n[i] = operator[](i);
        }
        delete data_;
        capacity_ = k + 1;
        firstEl_ = 0;
        endEl_ = e;
        data_ = n;
        dataEnd_ = data_ + capacity_;
    }
};
int main() {
    CircleBuffer<int> ex(5);
    for (int i = 0; i < 2; i++)
    {
        ex.push_front(i);
        ex.push_back(i);
    }
    for (int i = 0; i < 5; i++)
    {
        std::cout << ex[i] << "\n";
    }
    ex.changeCapacity(4);

    std::cout << "\n";
    for (int i = 0; i < 4; i++)
    {
        std::cout << ex[i] << "\n";
    }
    CircleBuffer<int>::CircleIterator it(ex, 1);
    CircleBuffer<int>::CircleIteratorConst itc(ex, 1);
    CircleBuffer<int>::CircleIterator its;
}
