#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <iomanip>
#include <cmath>

namespace ShapeTesting
{
    class Shape
    {
    public:
        Shape(void);
        virtual ~Shape(void);
        virtual void Print_Shape(void);
        void Release(void);
    };
    class Circle : public Shape
    {
    public:
        Circle(void);
        virtual ~Circle(void);
        int GetRadius(void);
        void SetRadius(int iRadius);
        double GetArea(void);
        void SetArea(double dArea);
        void Print_Shape(void) override;
    private:
        double area;
        int radius;
    };
    class Triangle : public Shape
    {
    public:
        Triangle(void);
        virtual ~Triangle(void);
        int GetBase(void);
        void SetBase(int iBase);
        int GetHeight(void);
        void SetHeight(int iHeight);
        double GetArea(void);
        void SetArea(double dArea);
        void Print_Shape(void);
    private:
        int base,height;
        double area;
    };
}

#endif // SHAPE_H
