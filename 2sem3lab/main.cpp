#include <iostream>
#include "pugixml.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <cmath>
#include <Windows.h>

class Vertex
{
private:
    double x_ = 0;
    double y_ = 0;
public:
    double value_ = 10000000000;
    Vertex() = default;
    Vertex(double a, double b):
            x_(a),
            y_(b)
    {
        value_ = 10000000000;
    }
    Vertex(const Vertex& other) = default;
    Vertex& operator= (const Vertex& other) = default;
    double dist(const Vertex& other) const
    {
        return sqrt((x_ - other.x_) * (x_ - other.x_) + (y_ - other.y_) * (y_ - other.y_));
    }
    double x() const
    {
        return x_;
    }
    double y() const
    {
        return y_;
    }
};
std::unordered_map <std::string, int> streets;
std::unordered_map<std::string, std::unordered_map <std::string, std::vector<Vertex>>> routes;
std::unordered_map<std::string, std::unordered_map <std::string, std::pair<int, double>>> routesEnd;
std::vector<std::string> split(std::string item, const std::string& kk, int n)
{
    std::vector<std::string> str;
    int start = 0;
    std::string s;
    for (int i = 0; i < item.size(); i++)
    {
        for (char j : kk){
            if (item[i] == j) {
                str.push_back(item.substr(start, i - start));
                start = i + n;
            }
        }
    }
    if (start < item.size()){
        str.push_back(item.substr(start, item.size() - start));
    }
    return str;
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    pugi::xml_document document;
    std::vector<std::string> stt;
    document.load_file("data.xml");
    pugi::xml_node data = document.child("dataset");
    std::string r;
    for (pugi::xml_node i = data.first_child(); i; i = i.next_sibling())
    {
        stt = split(i.child_value("coordinates"), ",", 1);
        char * ptr;
        Vertex t(std::strtod(stt[0].c_str(), &ptr), std::strtod(stt[1].c_str(), &ptr));
        stt = split(i.child_value("routes"), ",.", 1);
        r = i.child_value("type_of_vehicle");
        for(auto & j : stt)
        {
            routes[r][j].push_back(t);
            routesEnd[r][j] = std::pair<int, double>(0, 0);
        }
        stt = split(i.child_value("location"), ",", 2);
        for(auto & j : stt)
        {
            if (!j.empty()){
                streets[j]++;
            }
        }
    }
    for (const auto& i: routes) {
        for (auto& f: routes[i.first])
        {
            routesEnd[i.first][f.first].first = f.second.size();
            Vertex v;
            int vmi = 0;
            f.second[vmi].value_ = 0;
            double dist = 0;
            double distEnd = 0;
            while (!f.second.empty()) {
                v = f.second[vmi];
                distEnd += f.second[vmi].value_;
                std::swap(f.second[vmi], f.second[f.second.size() - 1]);
                f.second.pop_back();
                vmi = 0;
                for (int j = 0; j < f.second.size(); j++) {
                    dist = f.second[j].dist(v);
                    f.second[j].value_ = dist;
                    if (f.second[vmi].value_ > f.second[j].value_) {
                        vmi = j;
                    }
                }
            }
            routesEnd[i.first][f.first].second = distEnd;
        }
    }
    std::string strMax;
    int numOfStrMax = 0;
    std::unordered_map <std::string, std::pair<std::string, double>> coord;
    std::unordered_map <std::string, std::pair<std::string, int>> rout;
    for (const auto& i: streets)
    {
        {
            if (numOfStrMax < i.second)
            {
                numOfStrMax = i.second;
                strMax = i.first;
            }
        }
    }
    std::cout << strMax << " -> " << numOfStrMax << "\n";
    for (const auto& i: routesEnd)
    {
        for (auto& f: routesEnd[i.first])
        {
            if (rout[i.first].second < f.second.first) {
                rout[i.first].first = f.first;
                rout[i.first].second = f.second.first;
            }
            if (coord[i.first].second < f.second.second) {
                coord[i.first].first = f.first;
                coord[i.first].second = f.second.second;
            }
        }
    }
    for (const auto& i: routesEnd) {
        std::cout << i.first << "\n";
        std::cout << rout[i.first].first << " -> " << rout[i.first].second << "\n";
        std::cout << coord[i.first].first << "\n";
    }
    return 0;
}