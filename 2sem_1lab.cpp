#include <iostream>
#include <math.h>
class Point
{
private:
    int x = 0;
    int y = 0;
public:
    Point(int a, int b){
    x = a;
    y = b;
    }
    void copy(Point other){
        x = other.x;
        y = other.y;
    }
    void assignment(Point other){
        *this = other;
    }
    float distanse(Point other){
        return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
    };
};
class BrokenLine
{
private:
    Point* listOfPoints;
    int numOfPoints = 0;
public:
    BrokenLine(Point* list, int num){
        listOfPoints = list;
        numOfPoints = num;
    }
    void copy(BrokenLine other){
        listOfPoints = other.listOfPoints;
        numOfPoints = other.numOfPoints;
    }
    void assignment(BrokenLine other){
        *this = other;
    }
    float perimetr() const{
        float x = 0;
        for (int i = 1; i < this->numOfPoints; i++){
            x += this->listOfPoints[i - 1].distanse(this->listOfPoints[i]);
        }
        return x;
    };
};
int main() {

}
