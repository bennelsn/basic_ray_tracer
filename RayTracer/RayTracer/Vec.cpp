//
//  Vec.cpp
//  RayTracer
//
//  Created by Ben Nelson on 10/28/17.
//  Copyright © 2017 Ben Nelson. All rights reserved.
//

#include "Vec.h"



//Constructor
Vec::Vec()
{
    this->a1 = 0;
    this->a2 = 0;
    this->a3 = 0;
};
Vec::Vec(double x, double y)
{
    this->a1 = x;
    this->a2 = y;
    this->a3 = 0;
};
Vec::Vec(double x, double y, double z)
{
    this->a1 = x;
    this->a2 = y;
    this->a3 = z;
};

//Functions
void Vec::setA1(double x)
{
    this->a1 = x;

}
void Vec::setA2(double y)
{
    this->a2 = y;

}
void Vec::setA3(double z)
{
    this->a3 = z;

}
double Vec::getA1()
{
    return this->a1;
}
double Vec::getA2()
{
    return this->a2;
}
double Vec::getA3()
{
    return this->a3;
}

void Vec::normalize()
{
    double a = pow(this->a1, 2);
    double b = pow(this->a2, 2);
    double c = pow(this->a3, 2);
    
    double n = sqrt(a + b + c);
    this->a1 = a1/n;
    this->a2 = a2/n;
    this->a3 = a3/n;
}

void Vec::multiplyByScalar(double s)
{
    this->a1 = a1*s;
    this->a2 = a2*s;
    this->a3 = a3*s;
}
