//
//  Sphere.hpp
//  RayTracer
//
//  Created by Ben Nelson on 10/28/17.
//  Copyright © 2017 Ben Nelson. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "Vec.h"
class Sphere
{
private:
    Vec center;
    double radius;
    Vec material;
    Vec specHighlight;
    double phongConstant;
    bool reflective;
    
public:
    //Constructor
    Sphere(Vec center, double radius);
    Sphere(Vec center, double radius, Vec material, Vec specHighlight, double phongConstant);

    
    //Functions
    void setCenter(Vec center);
    void setRadius(double radius);
    void setMaterial(Vec material);
    void setSpecHighlight(Vec specHighlight);
    void setPhongConstant(double phongConstant);
    void setReflective(bool reflective);
    
    Vec getCenter();
    double getRadius();
    Vec getMaterial();
    Vec getSpecHighlight();
    double getPhongConstant();
    bool isReflective();

    
};

