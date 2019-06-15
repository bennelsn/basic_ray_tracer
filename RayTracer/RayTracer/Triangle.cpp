//
//  Triangle.cpp
//  RayTracer
//
//  Created by Ben Nelson on 10/28/17.
//  Copyright © 2017 Ben Nelson. All rights reserved.
//

#include "Triangle.h"

//Constructor
Triangle::Triangle(Vec v1, Vec v2, Vec v3)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->matDiffuse = Vec();
    this->specHighlight = Vec();
    this->phongConstant = 0;
};
Triangle::Triangle(Vec v1, Vec v2, Vec v3, Vec matDiffuse, Vec specHighlight, double phongConstant)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->matDiffuse = matDiffuse;
    this->specHighlight = specHighlight;
    this->phongConstant = phongConstant;
};


//Functions
void Triangle::setV1(Vec v1)
{
    this->v1 = v1;
};
void Triangle::setV2(Vec v2)
{
    this->v2 = v2;
};
void Triangle::setV3(Vec v3)
{
    this->v3 = v3;
};
void Triangle::setMatDiffuse(Vec matDiffuse)
{
    this->matDiffuse = matDiffuse;
};
void Triangle::setSpecHighlight(Vec specHighlight)
{
    this->specHighlight = specHighlight;
};
void Triangle::setPhongConstant(double phongConstant)
{
    this->phongConstant = phongConstant;
};

Vec Triangle::getV1()
{
    return this->v1;
};

Vec Triangle::getV2()
{
    return this->v2;
};

Vec Triangle::getV3()
{
    return this->v3;
};

Vec Triangle::getMatDiffuse()
{
    return this->matDiffuse;
};
Vec Triangle::getSpecHighlight()
{
    return this->specHighlight;
};
double Triangle::getPhongConstant()
{
    return this->phongConstant;
};
