//
//  Sphere.cpp
//  RayTracer
//
//  Created by Ben Nelson on 10/28/17.
//  Copyright © 2017 Ben Nelson. All rights reserved.
//

#include "Sphere.h"
//Constructor
Sphere::Sphere(Vec center, double radius)
{
    this->center=center;
    this->radius=radius;
    this->material = Vec();
    this->specHighlight = Vec();
    this->phongConstant = 0;
    this->reflective = false;
    
};
Sphere::Sphere(Vec center, double radius, Vec material, Vec specHighlight, double phongConstant)
{
    this->center=center;
    this->radius=radius;
    this->material = material;
    this->specHighlight = specHighlight;
    this->phongConstant = phongConstant;
    this->reflective = false;
    
};


//Functions
void Sphere::setCenter(Vec center)
{
    this->center = center;
};
void Sphere::setRadius(double radius)
{
    this->radius = radius;
}
void Sphere::setMaterial(Vec material)
{
    this->material = material;
};
void Sphere::setSpecHighlight(Vec specHighlight)
{
    this->specHighlight = specHighlight;
};
void Sphere::setPhongConstant(double phongConstant)
{
    this->phongConstant = phongConstant;
};
void Sphere::setReflective(bool reflective)
{
    this->reflective = reflective;
}


Vec Sphere::getCenter()
{
    return this->center;
};
double Sphere::getRadius()
{
    return this->radius;
};
Vec Sphere::getMaterial()
{
    return this->material;
};
Vec Sphere::getSpecHighlight()
{
    return this->specHighlight;
};
double Sphere::getPhongConstant()
{
    return this->phongConstant;
};
bool Sphere::isReflective()
{
    return this->reflective;
}
