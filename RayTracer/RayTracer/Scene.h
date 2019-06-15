//
//  Scene.hpp
//  RayTracer
//
//  Created by Ben Nelson on 10/28/17.
//  Copyright © 2017 Ben Nelson. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <vector>
#include "Vec.h"
#include "Sphere.h"
#include "Triangle.h"

class Scene
{
private:
    Vec camLookAt;
    Vec camLookFrom;
    Vec camLookUp;
    double fov;
    Vec directionToLight;
    Vec lightColor;
    Vec ambientLight;
    Vec bgColor;
    std::vector<Sphere> sphereList;
    std::vector<Triangle> triList;
    
    
public:
    //Constructor
    Scene(Vec camLookAt, Vec camLookFrom, Vec camLookUp, double fov, Vec directionToLight, Vec lightColor, Vec ambientLight, Vec bgColor, std::vector<Sphere> sphereList, std::vector<Triangle> triList);
    
    //Functions
    Vec getCamLookAt();
    Vec getCamLookFrom();
    Vec getCamLookUp();
    double getFOV();
    Vec getDirectionToLight();
    Vec getLightColor();
    Vec getAmbientLight();
    Vec getBgColor();
    std::vector<Sphere>  getSphereList();
    std::vector<Triangle>  getTriList();
    
    void setCamLookFrom(Vec newLookFrom);
    void setDirectionToLight(Vec newDirection);
    void setSphereCenter(int index, Vec newCenter);
    
};

