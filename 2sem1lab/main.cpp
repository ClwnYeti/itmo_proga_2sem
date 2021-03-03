#include <iostream>
#include <cmath>
#include <vector>
class Point
{
protected:
    double x_ = 0;
    double y_ = 0;
public:
    explicit Point(double a = 0, double b = 0)
            : x_(a),
              y_(b)
    {}
    Point(const Point &other) = default;
    Point& operator= (const Point &other) = default;
    double distance(Point &other) const
    {
        return sqrt((x_ - other.x_)*(x_ - other.x_) + (y_ - other.y_)*(y_ - other.y_));
    }
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
class VectorP
{
protected:
    double x_;
    double y_;
    double length_;
public:
    explicit VectorP(double a = 0, double b = 0)
            : x_(a),
              y_(b)
    {
        length_ = sqrt(x_ * x_ + y_ * y_);
    }
    VectorP(Point a, Point b)
            : x_(b.x() - a.x()),
              y_(b.y() - a.y())
    {
        length_ = sqrt(x_ * x_ + y_ * y_);
    }
    double scalar(VectorP &other) const
    {
        return x_ * other.x_ + y_ * other.y_;
    }
    double cos(VectorP &other) const
    {
        return scalar(other) / (length_ * other.length_);
    }
    double length() const
    {
        return length_;
    }
};
class BrokenLine
{
protected:
    std::vector<Point> listOfPoints_;
    double perimeter_ = 0;
    virtual void check(int l)
    {
        if (l < 2){
            throw std::invalid_argument("Not enough points to create");
        }
    }
    virtual void findPerimeter()
    {
        for (int i = 1; i < listOfPoints_.size(); i++){
            perimeter_ += listOfPoints_[i].distance(listOfPoints_[i - 1]);
        }
    }
    void push_into(std::vector<Point>& l)
    {
        int k = 0;
        for (int i = 0; i < l.size(); i++) {
            if (i == 0 || listOfPoints_[i - 1 - k] != l[i]) {
                listOfPoints_.resize(listOfPoints_.size() + 1);
                listOfPoints_[i - k] = l[i];
            } else {
                k++;
            }
        }
    }
public:
    BrokenLine() = default;
    explicit BrokenLine(std::vector<Point>& l) {
        push_into(l);
        check(listOfPoints_.size());
        findPerimeter();
    }
    BrokenLine(const BrokenLine &other) = default;
    BrokenLine& operator= (const BrokenLine &other) = default;
    double perimeter() const
    {
        return perimeter_;
    }
    int size()
    {
        return listOfPoints_.size();
    }
    std::vector<Point>& get_list(){
        return listOfPoints_;
    }
};

class ConnectedBrokenLine: public BrokenLine
{
protected:
    void check(int l) override
    {
        if (l < 3){
            throw std::invalid_argument("Not enough points to create");
        }
    }
    void findPerimeter() override
    {
        for (int i = 1; i < listOfPoints_.size(); i++){
            perimeter_ += listOfPoints_[i].distance(listOfPoints_[i - 1]);
        }
        perimeter_ += listOfPoints_[0].distance(listOfPoints_[listOfPoints_.size() - 1]);
    }
public:
    ConnectedBrokenLine() = default;
    explicit ConnectedBrokenLine(std::vector<Point>& l)
    {
        push_into(l);
        if (listOfPoints_[0] == listOfPoints_[listOfPoints_.size() - 1]){
            listOfPoints_.pop_back();
        }
        check(listOfPoints_.size());
        findPerimeter();
    }
    ConnectedBrokenLine(const ConnectedBrokenLine &other) = default;
};

class Polygon
{
protected:
    ConnectedBrokenLine line;
    std::vector<VectorP> listOfEdges_;
    double area_ = 0;
    Polygon() = default;
    virtual void check()
    {
        checkPolygon();
    }
    void checkPolygon()
    {
        for (int i = 1; i < line.size() - 1; i++){
            if ((listOfEdges_[i - 1].scalar(listOfEdges_[i]) > 0
                 && listOfEdges_[i].scalar(listOfEdges_[i + 1]) < 0)
                || (listOfEdges_[i - 1].scalar(listOfEdges_[i]) < 0
                    && listOfEdges_[i].scalar(listOfEdges_[i + 1]) > 0))
            {
                throw std::invalid_argument("Your polygon is non-convex");
            }
        }
    }
    void create_list_of_edges()
    {
        listOfEdges_.resize(line.size());
        for (int i = 0; i < line.size(); i++){
            listOfEdges_[i] = VectorP(line.get_list()[(i + line.size()) % line.size()],
                                                    line.get_list()[(i + 1 + line.size()) % line.size()]);
        }
    }
    void findArea()
    {
        for (int i = 0; i < line.size() - 1; i++){
            area_ += line.get_list()[i].x() * line.get_list()[i + 1].y()
                    - line.get_list()[i + 1].x() * line.get_list()[i].y();
        }
        area_ += line.get_list()[line.size() - 1].x() * line.get_list()[0].y()
                - line.get_list()[0].x() * line.get_list()[line.size() - 1].y();
        area_ /= 2;
        if (area_ < 0){
            area_ *= -1;
        }
    }
public:

    explicit Polygon(std::vector<Point>& l)
    {
        line = ConnectedBrokenLine(l);
        create_list_of_edges();
        check();
        findArea();
    }
    Polygon(const Polygon &other) = default;
    Polygon& operator= (const Polygon &other) = default;
    double perimeter() const{
        return line.perimeter();
    }
    double area() const{
        return area_;
    }
};
class Triangle: public Polygon
{
protected:
    Triangle() = default;
    void check() override
    {
        checkPolygon();
        if (line.size() != 3){
            throw std::invalid_argument("Too much points for triangle");
        }
        if (listOfEdges_[0].length() >= listOfEdges_[1].length() + listOfEdges_[2].length() - 0.000000001 ||
            listOfEdges_[1].length() >= listOfEdges_[0].length() + listOfEdges_[2].length() - 0.000000001 ||
            listOfEdges_[2].length() >= listOfEdges_[1].length() + listOfEdges_[0].length() - 0.000000001)
        {
            throw std::invalid_argument("It is a line");
        }
    }
public:
    explicit Triangle(std::vector<Point>& l)
    {
        line = ConnectedBrokenLine(l);
        check();
        findArea();
    }
    Triangle(const Triangle &other) = default;
};
class Trapezoid: public Polygon
{
protected:
    Trapezoid() = default;
    void check() override {
        checkPolygon();
        if (line.size() != 4){
            throw std::invalid_argument("Invalid amount of points for trapezoid");
        }
        if  (!(((listOfEdges_[0].cos(listOfEdges_[2]) < -0.99999
            || listOfEdges_[0].cos(listOfEdges_[2]) > 0.99999)
            && -1 < listOfEdges_[1].cos(listOfEdges_[3])
            && listOfEdges_[1].cos(listOfEdges_[3]) < 1) ||
            ((listOfEdges_[1].cos(listOfEdges_[3]) < -0.99999
            || listOfEdges_[1].cos(listOfEdges_[3]) > 0.99999)
            && -1 < listOfEdges_[0].cos(listOfEdges_[2])
            && listOfEdges_[0].cos(listOfEdges_[2]) < 1)))
        {
            throw std::invalid_argument("It is not a trapezoid");
        }
    }
public:
    explicit Trapezoid(std::vector<Point> &l)
    {
        line = ConnectedBrokenLine(l);
        check();
        findArea();
    }
    Trapezoid(const Trapezoid &other) = default;
};
class RegularPolygon: public Polygon {
protected:
    RegularPolygon() = default;
    void check() override {
        checkPolygon();
        for (int i = 1; i < line.size() - 1; i++) {
            if (listOfEdges_[i - 1].length() <= listOfEdges_[i].length() - 0.000000001 ||
                listOfEdges_[i].length() <= listOfEdges_[i + 1].length() - 0.000000001 ||
                listOfEdges_[i - 1].length() >= listOfEdges_[i].length() + 0.000000001 ||
                listOfEdges_[i].length() >= listOfEdges_[i + 1].length() + 0.000000001) {
                throw std::invalid_argument("Can't create a regular polygon like this");
            }
        }
    }

public:
    explicit RegularPolygon(std::vector<Point> &l) {
        line = ConnectedBrokenLine(l);
        check();
        findArea();
    }
    RegularPolygon(const RegularPolygon &other) = default;
};
int main() {
    std::vector<Point> l;
    Point a1(0, 0);
    Point a2(0, 5);
    Point a3(5, 5);
    Point a4(5, 0);
    Point a5(4, 0);
    l.push_back(a1);
    l.push_back(a2);
    l.push_back(a3);
    Polygon p(l);
    Triangle t(l);
    l.push_back(a4);
    RegularPolygon rp(l);
    std::cout << "\n" << p.perimeter();
    std::cout << "\n" << p.area();
    std::cout << "\n" << t.perimeter();
    std::cout << "\n" << t.area();
    std::cout << "\n" << rp.perimeter();
    std::cout << "\n" << rp.area();
    l.pop_back();
    l.push_back(a5);
    Trapezoid tr(l);
    std::cout << "\n" << tr.perimeter();
    std::cout << "\n" << tr.area();
}