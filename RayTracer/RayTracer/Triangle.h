//
//  Triangle.hpp
//  RayTracer
//
//  Created by Ben Nelson on 10/28/17.
//  Copyright © 2017 Ben Nelson. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "Vec.h"
class Triangle
{
private:
    Vec v1;
    Vec v2;
    Vec v3;
    Vec matDiffuse;
    Vec specHighlight;
    double phongConstant;
    
public:
    //Constructor
    Triangle(Vec v1, Vec v2, Vec v3);
    Triangle(Vec v1, Vec v2, Vec v3, Vec matDiffuse, Vec specHighlight, double phongConstant);
    
    //Functions
    void setV1(Vec v1);
    void setV2(Vec v2);
    void setV3(Vec v3);

    void setMatDiffuse(Vec matDiffuse);
    void setSpecHighlight(Vec specHighlight);
    void setPhongConstant(double phongConstant);
    
    Vec getV1();
    Vec getV2();
    Vec getV3();
    Vec getMatDiffuse();
    Vec getSpecHighlight();
    double getPhongConstant();

    
};

