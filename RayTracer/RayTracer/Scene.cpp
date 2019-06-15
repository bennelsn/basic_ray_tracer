//
//  Scene.cpp
//  RayTracer
//
//  Created by Ben Nelson on 10/28/17.
//  Copyright © 2017 Ben Nelson. All rights reserved.
//

#include "Scene.h"

//Constructor
Scene::Scene(Vec camLookAt, Vec camLookFrom, Vec camLookUp, double fov, Vec directionToLight, Vec lightColor, Vec ambientLight, Vec bgColor, std::vector<Sphere> sphereList, std::vector<Triangle> triList)
{
    this->camLookAt = camLookAt;
    this->camLookFrom = camLookFrom;
    this->camLookUp = camLookUp;
    this->fov = fov;
    this->directionToLight = directionToLight;
    this->lightColor = lightColor;
    this->ambientLight = ambientLight;
    this->bgColor = bgColor;
    this->sphereList = sphereList;
    this->triList = triList;
    
}

//Functions
Vec Scene::getCamLookAt()
{
    return this->camLookAt;
}
Vec Scene::getCamLookFrom()
{
    return this->camLookFrom;
}
Vec Scene::getCamLookUp()
{
    return this->camLookUp;
}
double Scene::getFOV()
{
    return this->fov;
}
Vec Scene::getDirectionToLight()
{
    return this->directionToLight;
}
Vec Scene::getLightColor()
{
    return this->lightColor;
}
Vec Scene::getAmbientLight()
{
    return this->ambientLight;
}
Vec Scene::getBgColor()
{
    return this->bgColor;
}
std::vector<Sphere>  Scene::getSphereList()
{
    return this->sphereList;
}
std::vector<Triangle>  Scene::getTriList()
{
    return this->triList;
}

void Scene::setCamLookFrom(Vec newLookFrom)
{
    this->camLookFrom = newLookFrom;
}

void Scene::setDirectionToLight(Vec newDirection)
{
    this->directionToLight = newDirection;
}
void Scene::setSphereCenter(int index, Vec newCenter)
{
    this->sphereList[index].setCenter(newCenter);
}
