#include <iostream>


template <class Value_T>
class CircleBuffer
{
private:
    int capacity_ = 0;
    Value_T* data_;
    Value_T* dataEnd_;
    int firstEl_;
    int endEl_;
public:
    class CircleIterator: public std::iterator<std::random_access_iterator_tag, Value_T>
    {
    private:
        unsigned int index_ = 0;
    public:
        CircleIterator() = default;
        CircleIterator& operator= (const CircleIterator& other) = default;
        bool operator== (const CircleIterator& other) const
        {
            return index_ == other.index_;
        }

        bool operator!= (const CircleIterator& other) const
        {
            return !this == other;
        }
        CircleIterator& operator+= (int ind)
        {
            index_ = ((index_ + ind) % capacity_ + capacity_) % capacity_;
        }
        CircleIterator& operator-= (int ind)
        {
            index_ = ((index_ - ind) % capacity_ + capacity_) % capacity_;
        }
        CircleIterator& operator+ (int ind) const
        {
            CircleIterator other = this;
            other += ind;
            return other;
        }
        int operator- (const CircleIterator& other) const
        {
            return (index_ - other.index_ + capacity_) % capacity_;
        }
        CircleIterator& operator++ ()
        {
            CircleIterator other = this;
            this += 1;
            return other;
        }
        CircleIterator& operator-- ()
        {
            CircleIterator other = this;
            this += 1;
            return other;
        }
        CircleIterator& operator++ (int)
        {
            this += 1;
            return this;
        }
        CircleIterator& operator-- (int)
        {
            this -= 1;
            return this;
        }
        CircleIterator& operator- (int ind) const
        {
            CircleIterator other = this;
            other -= ind;
            return other;
        }
        Value_T& operator[] (int ind)
        {
            return *(data_ + ((index_ + ind) % capacity_ + capacity_) % capacity_);
        }
        Value_T& operator* ()
        {
            return operator[](0);
        }

    };
    CircleBuffer() = default;
    CircleBuffer(int s)
    : capacity_(s + 1)
    {
        data_ = new Value_T(s + 1);
        dataEnd_ = data_ + capacity_;
        firstEl_ = 0;
        endEl_ = 0;
    }
    bool isFull()
    {
        return ((firstEl_ - endEl_) + capacity_) % capacity_ == 1;
    }
    bool isEmpty()
    {
        return ((endEl_ - firstEl_) + capacity_) % capacity_ == 0;
    }
    bool push_back(Value_T& i)
    {
        if (isFull())
            return false;
        data_[endEl_] = i;
        endEl_ = (endEl_ + 1 + capacity_) % capacity_;
        return true;
    }
    bool push_front(Value_T& i)
    {
        if (isFull())
            return false;
        if (isEmpty())
        {
            data_[firstEl_] = i;
            endEl_ = (endEl_ + 1 + capacity_) % capacity_;
        } else
        {
            firstEl_ = (firstEl_ - 1 + capacity_) % capacity_;
            data_[firstEl_] = i;
        }
        return true;
    }
    bool pop_front()
    {
        if (isEmpty())
            return false;
        firstEl_++;
    }
    bool pop_back()
    {
        if (isEmpty())
            return false;
        endEl_--;
    }
    Value_T& operator[](int index)
    {
        int k = (firstEl_ + index % capacity_ + capacity_) % capacity_;
        if ((endEl_ > firstEl_ && firstEl_ <= k && k < endEl_) ||
            ((endEl_ < firstEl_) && !(firstEl_ <= k && k < endEl_)))
                return data_[k];
        throw std::invalid_argument("Out of range");
    }
    Value_T& first()
    {
        return operator[](firstEl_);
    }
    Value_T& last()
    {
        return operator[](endEl_);
    }
    void changeCapacity(int k)
    {
        delete data_;
        capacity_ = k + 1;
        firstEl_ = 0;
        endEl_ = 0;
        data_ = new Value_T(capacity_);
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
    for (int i = 0; i < 2; i++)
    {
        ex.push_front(i);
        ex.push_back(i);
    }
    std::cout << "\n";
    for (int i = 0; i < 4; i++)
    {
        std::cout << ex[i] << "\n";
    }
}
