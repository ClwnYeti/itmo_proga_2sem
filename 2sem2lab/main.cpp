#include <iostream>
#include <unordered_map>


class Polynomial
{
private:
    std::unordered_map<int, double> allMembers_;
public:
    Polynomial() = default;
    Polynomial(const Polynomial &other) = default;
    ~Polynomial() = default;
    explicit Polynomial(std::unordered_map<int, double>& t)
    : allMembers_(t)
    {}
    Polynomial& operator= (const Polynomial &other) = default;
    bool operator== (const Polynomial &other) const
    {
        return allMembers_ == other.allMembers_;
    }
    bool operator!= (const Polynomial &other) const
    {
        return !(*this == other);
    }
    double& operator[] (int i)
    {
        return allMembers_[i];
    }
    Polynomial operator+ (const Polynomial& other) const
    {
        Polynomial new_ = *this;
        for (auto& i : other.allMembers_){
            new_[i.first] += i.second;
        }
        return new_;
    }
    Polynomial& operator+= (const Polynomial& other)
    {
        for (auto& i : other.allMembers_){
            allMembers_[i.first] += i.second;
        }
        return *this;
    }
    Polynomial operator- () const
    {
        Polynomial new_ = *this;
        for (auto& i : new_.allMembers_){
            i.second = -i.second;
        }
        return new_;
    }
    Polynomial& operator-= (const Polynomial& other)
    {
        return *this += -other;
    }
    Polynomial operator- (const Polynomial& other) const
    {
        return *this + (-other);
    }
    Polynomial operator/ (int a) const
    {
        Polynomial new_ = *this;
        for (auto& i : new_.allMembers_){
            i.second /= a;
        }
        return new_;
    }
    Polynomial& operator/= (int a)
    {
        for (auto& i : allMembers_){
            i.second /= a;
        }
        return *this;
    }
    Polynomial& operator*= (int a)
    {
        for (auto& i : allMembers_){
            i.second *= a;
        }
        return *this;
    }
    Polynomial operator* (int a) const
    {
        Polynomial new_ = *this;
        for (auto& i : new_.allMembers_){
            i.second *= a;
        }
        return new_;
    }
    Polynomial operator* (const Polynomial& a) const
    {
        Polynomial new_;
        for (auto& i : a.allMembers_){
            for (auto& j : allMembers_){
                new_[i.first + j.first] += i.second * j.second;
            }
        }
        return new_;
    }
    Polynomial& operator*= (const Polynomial& a)
    {
        *this = *this * a;
        return *this;
    }
    friend std::ostream& operator<< (std::ostream& out, const Polynomial&);
    friend std::istream& operator>> (std::istream& in, Polynomial&);
};


std::ostream& operator<< (std::ostream& out, const Polynomial& p)
{
    for (auto& i : p.allMembers_){
        if (i == *p.allMembers_.begin())
        {
            out << std::to_string(i.second) + " * x^" + std::to_string(i.first) + " ";
        } else {
            out << "+ " + std::to_string(i.second) + " * x^" + std::to_string(i.first) + " ";
        }
    }
    return out;
}
std::istream& operator>> (std::istream& in, Polynomial& p)
{
    int n;
    std::unordered_map<int, double> k;
    std::cout << "Enter a num of members:\n";
    in >> n;
    std::cout << "Enter degree and coefficient separated by a space:\n";
    int m;
    for (int i = 0; i < n; i++)
    {
        in >> m >> k[m];
    }
    p = Polynomial(k);
    return in;
}
int main()
{
    Polynomial a;
    std::cin >> a;
    std::cout << a;
    return 0;
}

