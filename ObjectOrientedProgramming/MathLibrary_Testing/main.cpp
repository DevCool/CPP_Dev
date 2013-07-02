#include "Shape.h"
using namespace std;
using namespace ShapeTesting;

int main()
{
    Circle* testCircle = new Circle();
    testCircle->SetRadius(50);
    testCircle->Print_Shape();
    testCircle->Release();
    Triangle* testTriangle = new Triangle();
    testTriangle->SetBase(15);
    testTriangle->SetHeight(4);
    testTriangle->Print_Shape();
    testTriangle->Release();
    return 0;
}
