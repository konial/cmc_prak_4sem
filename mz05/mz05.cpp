#include <iostream>
#include <sstream>
#include <string>
#include <map>
#define _USE_MATH_DEFINES
#include <cmath>
#include <functional>
#include <vector>
#include <algorithm>
#include <memory>

class Figure
{
public:
    virtual double get_square() const = 0;
    virtual std::string to_string() const = 0;
    virtual ~Figure() {}
};

class Rectangle : public Figure
{
    double x;
    double y;
public:
    static Rectangle* make(const std::string &str) {
        Rectangle *rect = new Rectangle();
        std::istringstream stin(str);
        stin >> rect->x >> rect->y;
        return rect;
    }
    double get_square() const { return x * y; }
    std::string to_string() const {
        std::string str;
        std::ostringstream stout;
        stout << 'R' << ' ' << x << ' ' << y;
        return stout.str();
    }
};

class Square : public Figure
{
    double x;
public:
    static Square* make(const std::string &str) {
        Square *sqr = new Square();
        std::istringstream stin(str);
        stin >> sqr->x;
        return sqr;
    }
    double get_square() const { return x * x; }
    std::string to_string() const {
        std::string str;
        std::ostringstream stout;
        stout << 'S' << ' ' << x;
        return stout.str();
    }
};

class Circle : public Figure
{
    double r;
public:
    static Circle* make(const std::string &str) {
        Circle *crcl = new Circle();
        std::istringstream stin(str);
        stin >> crcl->r;
        return crcl;
    }
    double get_square() const { return M_PI * r * r; }
    std::string to_string() const {
        std::string str;
        std::ostringstream stout;
        stout << 'C' << ' ' << r;
        return stout.str();
    }
};

class FigureFactory
{
    FigureFactory() {}
    std::map< char, std::function<Figure*(std::string)> > map_pattern {
        { 'R', Rectangle::make },
        { 'S', Square::make },
        { 'C', Circle::make }
    };
public:
    static FigureFactory& factory_instance() {
        static FigureFactory factory;
        return factory;
    }
    Figure* build(std::string pattern) {
        std::istringstream stin(pattern);
        char key;
        stin >> key;
        getline(stin, pattern);

        return map_pattern[key](pattern);
    }
};

bool comp(const Figure *first, const Figure *second) {
    return first->get_square() < second->get_square();
}

int main()
{
    FigureFactory factory = FigureFactory::factory_instance();

    std::vector<Figure*> figures;
    std::string str;
    while (std::getline(std::cin, str)) {
        Figure *figure = factory.build(str);
        figures.push_back(figure);
    }

    std::stable_sort(figures.begin(), figures.end(), comp);

    for (auto it : figures) {
        std::cout << it->to_string() << std::endl;
    }

    for (auto it : figures) {
        delete it;
    }

    return 0;
}
