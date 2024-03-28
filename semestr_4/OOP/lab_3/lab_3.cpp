#include <iostream>
#include <vector>
#include "Header.h"

void exception() {
    throw "Exception";
}

int main(){
    try {
        exception();
    }
    catch (...){
        std::cout << "Exception handled!" << std::endl;
    }
    SHAPES* e = NULL;
    COLLECTION shapeList(10);

    shapeList.add(new RHOMBUS(5.0, 5.0, 5.0));
    shapeList.add(new RHOMBUS(5.0, 5.0, 5.0));
    shapeList.add(new ELLIPSE(10.0, 10.0));
    shapeList.add(new PARALLELEPIPED(5.0, 10.0, 20.0));


    RHOMBUS rh1(5.0, 5.0, 5.0), rh2(5.0, 5.0, 5.0), rh3 = rh2, rh4(10.0, 10.0, 20.0);
    rh1 == rh2 ? std::cout << "rh1 & rh2 are equal" << std::endl : std::cout << "rh1 & rh2 are unequal" << std::endl;
    rh3 == rh4 ? std::cout << "rh3 & rh4 are equal" << std::endl : std::cout << "rh3 & rh4 are unequal" << std::endl;
    shapeList[0] == shapeList[2] ? std::cout << "shapeList[0] & shapeList[2] are equal" << std::endl : std::cout << "shapeList[0] & shapeList[2] are unequal" << std::endl;

    std::cout <<  "Total area: " << shapeList.totalArea() << std::endl;
    std::cout <<  "Total perimeter: " << shapeList.totalPerimeter() << std::endl;
}