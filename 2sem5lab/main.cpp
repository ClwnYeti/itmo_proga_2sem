#include <iostream>


template <class Value_T>
class CircleBuffer
{
private:
    int capasity_ = 0;
    Value_T* data_;
    Value_T* dataEnd_;
    Value_T* startEl_;
    Value_T* endEl_;
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
            index_ = ((index_ + ind) % capasity_  + capasity_) % capasity_;
        }
        CircleIterator& operator-= (int ind)
        {
            index_ = ((index_ - ind) % capasity_ + capasity_) % capasity_;
        }
        CircleIterator& operator+ (int ind) const
        {
            CircleIterator other = this;
            other += ind;
            return other;
        }
        int operator- (const CircleIterator& other) const
        {
            return (index_ - other.index_ + capasity_) % capasity_;
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
            return *(data_ + ((index_ + ind) % capasity_  + capasity_) % capasity_);
        }
        Value_T& operator* ()
        {
            return operator[](0);
        }

    };
    CircleBuffer() = default;
    CircleBuffer(int s)
    : capasity_(s)
    {
        data_ = new Value_T(s);
        dataEnd_ = data_ + capasity_;
        startEl_ = data_[0];
        endEl_ = data_[0];
    }
    bool isFull()
    {
        return ((int )(startEl_ - endEl_) + capasity_) % capasity_ == 1;
    }
    bool isEmpty()
    {
        return ((int )(endEl_ - startEl_) + capasity_) % capasity_ == 0;
    }
};
int main() {
}
