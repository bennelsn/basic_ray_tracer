//
//  Vec.hpp
//  RayTracer
//
//  Created by Ben Nelson on 10/28/17.
//  Copyright © 2017 Ben Nelson. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <math.h>

class Vec
{
private:
    double a1;
    double a2;
    double a3;
    
public:
    //Constructor
    Vec();
    Vec(double x, double y);
    Vec(double x, double y, double z);
    
    //Functions
    void setA1(double x);
    void setA2(double y);
    void setA3(double z);
    double getA1();
    double getA2();
    double getA3();
    
    void normalize();
    void multiplyByScalar(double s);

    
    
};
