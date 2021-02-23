#include <iostream>
#include <cmath>
#include <vector>
class Point
{
private:
    double x_ = 0;
    double y_ = 0;
public:
    Point(double a = 0, double b = 0)
    : x_(a),
    y_(b)
    {}
    Point(const Point &other)
    : x_(other.x_),
    y_(other.y_)
    {}
    Point& operator= (const Point &other)
    {
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }
    double distanse(Point &other) const
    {
        return sqrt((x_ - other.x_)*(x_ - other.x_) + (y_ - other.y_)*(y_ - other.y_));
    }
    bool operator== (const Point& other) const
    {
        return (-0.000000001<= (x_ - other.x_) <= 0.000000001
                && -0.000000001 <= (y_ - other.y_) <= 0.000000001);
    }
};
class BrokenLine
{
private:
    std::vector<Point*> listOfPoints_;
    int numOfPoints_ = 0;
public:
    BrokenLine(std::vector<Point*>*l = nullptr)
    {
        if (l == nullptr){
            listOfPoints_.resize(0);
            numOfPoints_ = 0;
        } else {
            numOfPoints_ = l->size();
            for (int i = 0; i < numOfPoints_; i++){
                listOfPoints_[i] = (*l)[i];
            }
        }
    }
    BrokenLine(const BrokenLine &other)
    {
        numOfPoints_ = other.listOfPoints_.size();
        for (int i = 0; i < numOfPoints_; i++) {
            listOfPoints_[i] = other.listOfPoints_[i];
        }
    }
    BrokenLine& operator= (const BrokenLine &other)
    {
        numOfPoints_ = other.listOfPoints_.size();
        for (int i = 0; i < numOfPoints_; i++) {
            listOfPoints_[i] = other.listOfPoints_[i];
        }
        return *this;
    }
};

int main() {
}