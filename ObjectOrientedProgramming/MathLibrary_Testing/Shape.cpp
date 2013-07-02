#include "Shape.h"
using namespace std;
using namespace ShapeTesting;


// ----------------------------------------------------------------------------


Shape::Shape(void)
{
}

Shape::~Shape(void)
{
}

void Shape::Print_Shape(void)
{
    cout << "This is where we print crap for the shape." << endl;
    cout << "This is the base class for shapes." << endl;
}

void Shape::Release(void)
{
    delete this;
}


// ----------------------------------------------------------------------------


Circle::Circle(void)
{
    area = 0.0;
    radius = 0;
}

Circle::~Circle(void)
{
}

int Circle::GetRadius(void)
{
    return radius;
}

void Circle::SetRadius(int iRadius)
{
    radius = iRadius;
}

double Circle::GetArea(void)
{
    return area;
}

void Circle::SetArea(double dArea)
{
    area = dArea;
}

void Circle::Print_Shape(void)
{
    const double pi = 3.14159265;
    SetArea(pi * pow(GetRadius(), 2));
    cout << "The area of this circle is " << setprecision(10) << GetArea() << ".\n";
    cout << "That's all folks." << endl;
}


// ----------------------------------------------------------------------------


Triangle::Triangle(void)
{
    base = 0;
    height = 0;
    area = 0.0;
}

Triangle::~Triangle(void)
{
}

int Triangle::GetBase(void)
{
    return base;
}

void Triangle::SetBase(int iBase)
{
    base = iBase;
}

int Triangle::GetHeight(void)
{
    return height;
}

void Triangle::SetHeight(int iHeight)
{
    height = iHeight;
}

double Triangle::GetArea(void)
{
    return area;
}

void Triangle::SetArea(double dArea)
{
    area = dArea;
}

void Triangle::Print_Shape(void)
{
    SetArea(pow(((base * height) / 2), 2));
    cout << "The base of the triangle is " << GetBase() << endl;
    cout << "The height of the triangle is " << GetHeight() << endl;
    cout << "The area of this triangle is " << GetArea() << endl;
    cout << "That's all folks!!" << endl;
}


// ----------------------------------------------------------------------------
