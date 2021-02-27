#include <iostream>
#include <cmath>
#include <vector>
class VectorP
{
protected:
    double x_;
    double y_;
    double length_;
public:
    VectorP(double a = 0, double b = 0)
    : x_(a),
    y_(b)
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
class Point
{
protected:
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
    void point(){
        std::cout << "[" << x_ << "; " << y_ << "]\n";
    }
    double x(){
        return x_;
    };
    double y(){
        return y_;
    };
};
class BrokenLine
{
protected:
    std::vector<Point*> listOfPoints_;
    int numOfPoints_ = 0;
    double perimeter_ = 0;
    virtual void check(int l)
    {
        if (l < 2){
            throw std::invalid_argument("Can't create a broken line like this");
        }
    }
    virtual void findPerimeter()
    {
        for (int i = 1; i < numOfPoints_; i++){
            perimeter_ += listOfPoints_[i]->distance(*listOfPoints_[i - 1]);
        }
    }
public:
    BrokenLine(std::vector<Point*>* l = nullptr)
    {
        if (l == nullptr){
            listOfPoints_.resize(0);
            numOfPoints_ = 0;
        } else {
            int k = 0;
            numOfPoints_ = l->size();
            for (int i = 0; i < numOfPoints_; i++){
                if (i == 0 || *listOfPoints_[i - 1 - k] != *(*l)[i]) {
                    listOfPoints_.resize(listOfPoints_.size() + 1);
                    listOfPoints_[i - k] = (*l)[i];
                }
                else {
                    k++;
                }
            }
            numOfPoints_ -= k;
            check(numOfPoints_);
            findPerimeter();
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
        listOfPoints_.clear();
        numOfPoints_ = other.listOfPoints_.size();
        listOfPoints_.resize(numOfPoints_);
        for (int i = 0; i < numOfPoints_; i++) {
            listOfPoints_[i] = other.listOfPoints_[i];
        }
        return *this;
    }
    double perimeter() const
    {
        return perimeter_;
    }
};

class ConnectedBrokenLine: public BrokenLine
{
protected:
    void check(int l) override
    {
        if (l < 3){
            throw std::invalid_argument("Can't create a connected broken line like this");
        }
    }
    void findPerimeter() override
    {
        for (int i = 1; i < numOfPoints_; i++){
            perimeter_ += listOfPoints_[i]->distance(*listOfPoints_[i - 1]);
        }
        perimeter_ += listOfPoints_[0]->distance(*listOfPoints_[numOfPoints_ - 1]);
    }
public:
    ConnectedBrokenLine(std::vector<Point*>* l = nullptr) {
        if (l == nullptr) {
            listOfPoints_.resize(0);
            numOfPoints_ = 0;
        } else {
            int k = 0;
            numOfPoints_ = l->size();
            for (int i = 0; i < numOfPoints_; i++){
                if (i == 0 || *listOfPoints_[i - 1 - k] != *(*l)[i]) {
                    listOfPoints_.resize(listOfPoints_.size() + 1);
                    listOfPoints_[i - k] = (*l)[i];
                }
                else {
                    k++;
                }
            }
            numOfPoints_ -= k;
            if (*listOfPoints_[0] == *listOfPoints_[numOfPoints_ - 1]){
                listOfPoints_.pop_back();
                numOfPoints_ --;
            }
            check(numOfPoints_);
            findPerimeter();
        }
    }
    ConnectedBrokenLine(const ConnectedBrokenLine &other)
    {
        numOfPoints_ = other.listOfPoints_.size();
        for (int i = 0; i < numOfPoints_; i++) {
            listOfPoints_[i] = other.listOfPoints_[i];
        }
    }
};
class Polygon
{
protected:
    std::vector<Point*> listOfPoints_;
    std::vector<VectorP> listOfEdges_;
    int numOfPoints_ = 0;
    double perimeter_ = 0;
    double area_ = 0;
    virtual void check()
    {
        if (numOfPoints_ < 3){
            throw std::invalid_argument("Can't create a polygon like this");
        }
        listOfEdges_.resize(numOfPoints_);
        for (int i = 0; i < numOfPoints_; i++){
            listOfEdges_[i] = VectorP(listOfPoints_[(i + numOfPoints_) % numOfPoints_]->x()
                                      - listOfPoints_[(i + 1 + numOfPoints_) % numOfPoints_]->x(),
                                      listOfPoints_[(i + numOfPoints_) % numOfPoints_]->y()
                                      - listOfPoints_[(i + 1 + numOfPoints_) % numOfPoints_]->y());
        }
        for (int i = 1; i < numOfPoints_ - 1; i++){
            if ((listOfEdges_[i - 1].scalar(listOfEdges_[i]) > 0
                && listOfEdges_[i].scalar(listOfEdges_[i + 1]) < 0)
                || (listOfEdges_[i - 1].scalar(listOfEdges_[i]) < 0
                && listOfEdges_[i].scalar(listOfEdges_[i + 1]) > 0))
            {
                throw std::invalid_argument("Can't create a polygon like this");
            }

        }
    }
    void findPerimeter()
    {
        for (int i = 1; i < numOfPoints_; i++){
            perimeter_ += listOfPoints_[i]->distance(*listOfPoints_[i - 1]);
        }
        perimeter_ += listOfPoints_[0]->distance(*listOfPoints_[numOfPoints_ - 1]);
    }
    void findArea()
    {
        for (int i = 0; i < numOfPoints_ - 1; i++){
            area_ += listOfPoints_[i]->x() * listOfPoints_[i + 1]->y()
                    - listOfPoints_[i + 1]->x() * listOfPoints_[i]->y();
        }
        area_ += listOfPoints_[numOfPoints_ - 1]->x()*listOfPoints_[0]->y()
                - listOfPoints_[0]->x()*listOfPoints_[numOfPoints_ - 1]->y();
        area_ /= 2;
        if (area_ < 0){
            area_ *= -1;
        }
    }
public:
    Polygon(std::vector<Point*>* l = nullptr)
    {
        if (l == nullptr) {
            listOfPoints_.resize(0);
            numOfPoints_ = 0;
        } else {
            int k = 0;
            numOfPoints_ = l->size();
            for (int i = 0; i < numOfPoints_; i++){
                if (i == 0 || *listOfPoints_[i - 1 - k] != *(*l)[i]) {
                    listOfPoints_.resize(listOfPoints_.size() + 1);
                    listOfPoints_[i - k] = (*l)[i];
                }
                else {
                    k++;
                }
            }
            numOfPoints_ -= k;
            if (*listOfPoints_[0] == *listOfPoints_[numOfPoints_ - 1]){
                listOfPoints_.pop_back();
                numOfPoints_ --;
            }
            check();
            findPerimeter();
            findArea();
        }
    }
    Polygon(const Polygon &other)
    {
        numOfPoints_ = other.listOfPoints_.size();
        listOfPoints_.resize(numOfPoints_);
        listOfEdges_.resize(numOfPoints_);
        for (int i = 0; i < numOfPoints_; i++) {
            listOfPoints_[i] = other.listOfPoints_[i];
            listOfEdges_[i] = other.listOfEdges_[i];
        }
    }
    Polygon& operator= (const Polygon &other)
    {
        listOfPoints_.clear();
        listOfEdges_.clear();
        numOfPoints_ = other.listOfPoints_.size();
        listOfPoints_.resize(numOfPoints_);
        listOfEdges_.resize(numOfPoints_);
        for (int i = 0; i < numOfPoints_; i++) {
            listOfPoints_[i] = other.listOfPoints_[i];
            listOfEdges_[i] = other.listOfEdges_[i];
        }
        return *this;
    }
    double perimeter() const{
        return perimeter_;
    }
    double area() const{
        return area_;
    }
};
class Triangle: public Polygon
{
protected:
    void check() override
    {
        if (numOfPoints_ != 3){
            throw std::invalid_argument("Can't create a triangle like this");
        }
        listOfEdges_.resize(numOfPoints_);
        for (int i = 0; i < numOfPoints_; i++){
            listOfEdges_[i] = VectorP(listOfPoints_[(i + numOfPoints_) % numOfPoints_]->x()
                                      - listOfPoints_[(i + 1 + numOfPoints_) % numOfPoints_]->x(),
                                      listOfPoints_[(i + numOfPoints_) % numOfPoints_]->y()
                                      - listOfPoints_[(i + 1 + numOfPoints_) % numOfPoints_]->y());
        };
        if (listOfEdges_[0].length() >= listOfEdges_[1].length() + listOfEdges_[2].length() - 0.000000001 ||
            listOfEdges_[1].length() >= listOfEdges_[0].length() + listOfEdges_[2].length() - 0.000000001 ||
            listOfEdges_[2].length() >= listOfEdges_[1].length() + listOfEdges_[0].length() - 0.000000001)
        {
            throw std::invalid_argument("Can't create a triangle like this");
        }
    }
public:
    Triangle(std::vector<Point*>* l = nullptr)
    {
        if (l == nullptr) {
            listOfPoints_.resize(0);
            numOfPoints_ = 0;
        } else {
            int k = 0;
            numOfPoints_ = l->size();
            for (int i = 0; i < numOfPoints_; i++){
                if (i == 0 || *listOfPoints_[i - 1 - k] != *(*l)[i]) {
                    listOfPoints_.resize(listOfPoints_.size() + 1);
                    listOfPoints_[i - k] = (*l)[i];
                }
                else {
                    k++;
                }
            }
            numOfPoints_ -= k;
            if (*listOfPoints_[0] == *listOfPoints_[numOfPoints_ - 1]){
                listOfPoints_.pop_back();
                numOfPoints_ --;
            }
            check();
            findPerimeter();
            findArea();
        }
    }
    Triangle(const Triangle &other)
    {
        numOfPoints_ = other.listOfPoints_.size();
        listOfPoints_.resize(numOfPoints_);
        listOfEdges_.resize(numOfPoints_);
        for (int i = 0; i < numOfPoints_; i++) {
            listOfPoints_[i] = other.listOfPoints_[i];
            listOfEdges_[i] = other.listOfEdges_[i];
        }
    }
};
class Trapezoid: public Polygon
{
protected:
    void check() override {
        if (numOfPoints_ != 4) {
            throw std::invalid_argument("Can't create a trapezoid like this");
        }
        listOfEdges_.resize(numOfPoints_);
        for (int i = 0; i < numOfPoints_; i++){
            listOfEdges_[i] = VectorP(listOfPoints_[(i + numOfPoints_) % numOfPoints_]->x()
                                      - listOfPoints_[(i + 1 + numOfPoints_) % numOfPoints_]->x(),
                                      listOfPoints_[(i + numOfPoints_) % numOfPoints_]->y()
                                      - listOfPoints_[(i + 1 + numOfPoints_) % numOfPoints_]->y());
        };
        if  (!(((listOfEdges_[0].cos(listOfEdges_[2]) < -0.99999
            || listOfEdges_[0].cos(listOfEdges_[2]) > 0.99999)
            && -1 < listOfEdges_[1].cos(listOfEdges_[3])
            && listOfEdges_[1].cos(listOfEdges_[3]) < 1) ||
            ((listOfEdges_[1].cos(listOfEdges_[3]) < -0.99999
            || listOfEdges_[1].cos(listOfEdges_[3]) > 0.99999)
            && -1 < listOfEdges_[0].cos(listOfEdges_[2])
            && listOfEdges_[0].cos(listOfEdges_[2]) < 1)))
        {
            throw std::invalid_argument("Can't create a trapezoid like this");
        }
    }
public:
    Trapezoid(std::vector<Point*>* l = nullptr)
    {
        if (l == nullptr) {
            listOfPoints_.resize(0);
            numOfPoints_ = 0;
        } else {
            int k = 0;
            numOfPoints_ = l->size();
            for (int i = 0; i < numOfPoints_; i++){
                if (i == 0 || *listOfPoints_[i - 1 - k] != *(*l)[i]) {
                    listOfPoints_.resize(listOfPoints_.size() + 1);
                    listOfPoints_[i - k] = (*l)[i];
                }
                else {
                    k++;
                }
            }
            numOfPoints_ -= k;
            if (*listOfPoints_[0] == *listOfPoints_[numOfPoints_ - 1]){
                listOfPoints_.pop_back();
                numOfPoints_ --;
            }
            check();
            findPerimeter();
            findArea();
        }
    }
    Trapezoid(const Trapezoid &other)
    {
        numOfPoints_ = other.listOfPoints_.size();
        listOfPoints_.resize(numOfPoints_);
        listOfEdges_.resize(numOfPoints_);
        for (int i = 0; i < numOfPoints_; i++) {
            listOfPoints_[i] = other.listOfPoints_[i];
            listOfEdges_[i] = other.listOfEdges_[i];
        }
    }
};
class ReguralPolygon: public Polygon
{
protected:
    void check() override
    {
        if (numOfPoints_ < 3){
            throw std::invalid_argument("Can't create a regural polygon like this");
        }
        listOfEdges_.resize(numOfPoints_);
        for (int i = 0; i < numOfPoints_; i++){
            listOfEdges_[i] = VectorP(listOfPoints_[(i + numOfPoints_) % numOfPoints_]->x()
                                      - listOfPoints_[(i + 1 + numOfPoints_) % numOfPoints_]->x(),
                                      listOfPoints_[(i + numOfPoints_) % numOfPoints_]->y()
                                      - listOfPoints_[(i + 1 + numOfPoints_) % numOfPoints_]->y());
        };
        for (int i = 1; i < numOfPoints_ - 1; i++){
            if ((listOfEdges_[i - 1].scalar(listOfEdges_[i]) > 0
                && listOfEdges_[i].scalar(listOfEdges_[i + 1]) < 0)
                || (listOfEdges_[i - 1].scalar(listOfEdges_[i]) < 0
                && listOfEdges_[i].scalar(listOfEdges_[i + 1]) > 0)
                || listOfEdges_[i - 1].length() <= listOfEdges_[i].length() - 0.000000001
                || listOfEdges_[i].length() <= listOfEdges_[i + 1].length() - 0.000000001
                || listOfEdges_[i - 1].length() >= listOfEdges_[i].length() + 0.000000001
                || listOfEdges_[i].length() >= listOfEdges_[i + 1].length() + 0.000000001)
            {
                throw std::invalid_argument("Can't create a regural polygon like this");
            }
        }
    }
public:
    ReguralPolygon(std::vector<Point*>* l = nullptr)
    {
        if (l == nullptr) {
            listOfPoints_.resize(0);
            numOfPoints_ = 0;
        } else {
            int k = 0;
            numOfPoints_ = l->size();
            for (int i = 0; i < numOfPoints_; i++){
                if (i == 0 || *listOfPoints_[i - 1 - k] != *(*l)[i]) {
                    listOfPoints_.resize(listOfPoints_.size() + 1);
                    listOfPoints_[i - k] = (*l)[i];
                }
                else {
                    k++;
                }
            }
            numOfPoints_ -= k;
            if (*listOfPoints_[0] == *listOfPoints_[numOfPoints_ - 1]){
                listOfPoints_.pop_back();
                numOfPoints_--;
            }
            check();
            findPerimeter();
            findArea();
        }
    }
    ReguralPolygon(const ReguralPolygon &other)
    {
        numOfPoints_ = other.listOfPoints_.size();
        listOfPoints_.resize(numOfPoints_);
        listOfEdges_.resize(numOfPoints_);
        for (int i = 0; i < numOfPoints_; i++) {
            listOfPoints_[i] = other.listOfPoints_[i];
            listOfEdges_[i] = other.listOfEdges_[i];
        }
    }
};
int main() {
    std::vector<Point *> l;
    Point a1(0, 0);
    Point a2(0, 5);
    Point a3(5, 5);
    Point a4(5, 0);
    Point a5(4, 0);
    l.push_back(&a1);
    l.push_back(&a2);
    l.push_back(&a3);
    Polygon p(&l);
    Triangle t(&l);
    l.push_back(&a4);
    ReguralPolygon rp(&l);
    std::cout << "\n" << p.perimeter();
    std::cout << "\n" << p.area();
    std::cout << "\n" << t.perimeter();
    std::cout << "\n" << t.area();
    std::cout << "\n" << rp.perimeter();
    std::cout << "\n" << rp.area();
    l.pop_back();
    l.push_back(&a5);
    Trapezoid tr(&l);
    std::cout << "\n" << tr.perimeter();
    std::cout << "\n" << tr.area();
}