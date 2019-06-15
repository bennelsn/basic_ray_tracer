//
//  Tools.hpp
//  RayTracer
//
//  Created by Ben Nelson on 10/28/17.
//  Copyright © 2017 Ben Nelson. All rights reserved.
//
#pragma once
#include <stdio.h>
#include "Scene.h"

using namespace std;

class Tools
{
    
private:
public:
    //Constructors
    Tools();
    
    //Destructor
    ~Tools();
    
    //Functions
    Scene parseSceneFile(string filePath, string fileName);
    void outputFile(string outPath, string fileName, int width, int height, string image);
    Vec extractVec3(string line);
    Sphere extractSphere(string line);
    Triangle extractTriangle(string line);
    string rayTrace(Scene scene, int xPixels, int yPixels);
    
    Vec sendOutShadowRay(Vec rayO, Vec rayD, vector<Sphere> sphereList, vector<Triangle> triList, Vec ambientLight, Vec currentColor, Vec n, Vec lcolor, Vec camera, Vec objectSpecular, double phongE);
    Vec sendOutRefectionRay(Vec rayO, Vec rayD, vector<Sphere> sphereList, vector<Triangle> triList, Vec ambient, Vec lColor, Vec directionToLight, Vec lookFrom, Vec bgColor, Vec objectColor, Vec N, int currShapeI);
    Vec calculateRayDirection(Vec lookFrom, double UVmax, double UVmin, double IJmax, double IJmin, int xPixel, int yPixel);
    Vec calculateSphereNormal(Vec rayI, Vec center, double radius);
    Vec calculateTriangleNormal(Triangle tri);
    Vec calculateReflectDirection(Vec vDir, Vec N);
    Vec calculateDiffuse(Vec Od, Vec L ,Vec n, Vec l);
    Vec calculateSpecular(Vec cam, Vec n, Vec l, Vec objectSpecular, double phongE);
    Vec add(Vec v1, Vec v2);
    Vec subtract(Vec v1, Vec v2);
    Vec multiply(Vec v1, Vec v2);
    Vec multiplyByScalar(Vec v1, double scalar);
    Vec reverse(Vec v1);
    Vec cross(Vec v1, Vec v2);
    double dot(Vec v1, Vec v2);
    double dotProductOf(double a1[], double b1[]);
    Vec convertColor(Vec inColor);
    Vec clampColor(Vec inColor);
    string determineProjectionAxis(Vec normal);
    bool rayIntersectsWithSphere(double &t,Vec rayO,Vec rayD, Vec &rayI, Sphere sphere);
    bool rayIntersectsWithTriangle(double &t,Vec rayO,Vec rayD, Vec &rayI, Triangle tri);
    bool rayIntersectsWithPlane(double &t, Vec rayO,Vec rayD, Vec &rayI, Vec &planeNormal, Triangle tri);
    bool pointInTriangle(Vec rayD, Triangle tri, string projectionAxis);
    bool allResultsArePosOrNeg(double resultOne, double resultTwo, double resultThree);


    
    
    
};

