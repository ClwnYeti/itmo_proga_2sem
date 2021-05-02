#include <iostream>
#include <vector>

template <class Iterator, class UnaryPredicate>

bool all_of(Iterator begin, Iterator end, UnaryPredicate f)
{
    for (Iterator i = begin; i != end; std::next(i))
    {
        if (!f(*i)){
            return false;
        }
    }
    return true;
}
template <class Iterator, class UnaryPredicate>
bool any_of(Iterator& begin, Iterator& end, UnaryPredicate f)
{
    for (Iterator i = begin; i != end; std::next(i))
    {
        if (f(i)){
            return true;
        }
    }
    return false;
}
template <class Iterator, class UnaryPredicate>
bool none_of(Iterator& begin, Iterator& end, UnaryPredicate f)
{
    for (Iterator i = begin; i != end; std::next(i))
    {
        if (f(i)){
            return false;
        }
    }
    return true;
}
template <class Iterator, class UnaryPredicate>
bool one_of(Iterator& begin, Iterator& end, UnaryPredicate f)
{
    int k = 0;
    for (Iterator i = begin; i != end; std::next(i))
    {
        if (f(i))
        {
            k++;
            if (k > 1){
                return false;
            }
        }
    }
    return true;
}
template <class Iterator, class Compare>
bool is_sorted(Iterator& begin, Iterator& end, Compare comp)
{
    if (begin == end--)
    {
        return true;
    }
    for (Iterator i = begin; i != end;)
    {
        if (!comp(i, std::next(i))){
            return false;
        }
    }
    return true;
}
template <class Iterator, class UnaryPredicate>
bool is_partitioned(Iterator& begin, Iterator& end, UnaryPredicate f)
{
    bool start = f(begin);
    bool flag = false;
    for (Iterator i = begin; i != end; std::next(i))
    {
        if (start != f(i)){
            if (flag)
            {
                return false;
            }
            flag = true;
            start = f(i);
        }
    }
    if (flag)
    {
        return true;
    }
    return false;
}
template <class Iterator, class UnaryPredicate>
Iterator& find_not(Iterator& begin, Iterator& end, UnaryPredicate f)
{
    for (Iterator i = begin; i != end; std::next(i)) {
        if (!f(i)) {
            return i;
        }
    }
}

template <class Iterator, class UnaryPredicate>
Iterator& find_backward(Iterator& begin, Iterator& end, UnaryPredicate f)
{
    end--;
    begin--;
    for (Iterator i = end; i != begin; std::prev(i)) {
        if (f(i)) {
            return i;
        }
    }
}
template <class Iterator, class UnaryPredicate>
bool is_palindrome(Iterator& begin, Iterator& end, UnaryPredicate f)
{
    Iterator t = end;
    for (Iterator i = begin; i != end; std::next(i)) {
        if (f(i) != f(t)) {
            return false;
        }
        std::prev(t);
    }
    return true;
}
class Point
{
private:
    double x_ = 0;
    double y_ = 0;
public:
    explicit Point(double a = 0, double b = 0)
            : x_(a),
              y_(b)
    {}
    Point(const Point &other) = default;
    Point& operator= (const Point &other) = default;
    bool operator== (const Point& other) const
    {
        return (-0.000000001<= (x_ - other.x_) && (x_ - other.x_) <= 0.000000001
                && -0.000000001 <= (y_ - other.y_) && (y_ - other.y_) <= 0.000000001);
    }
    bool operator!= (const Point& other) const
    {
        return !(*this == other);
    }
    double x() const{
        return x_;
    };
    double y() const{
        return y_;
    };
};
bool U(Point& a)
{
    return a.x() > 0 && a.y() > 0;
}
bool V(Point& a)
{
    return a.x() > 0 && a.y() < 0;
}
int main() {
    std::vector<Point> a;
    a.emplace_back(Point(1, 1));
    a.emplace_back(Point(1, 1));
    a.emplace_back(Point(1, 1));
    a.emplace_back(Point(1, 1));
    a.emplace_back(Point(1, 1));
    a.emplace_back(Point(1, 1));
    std::cout << all_of(a.begin(), a.end(), U);
}
