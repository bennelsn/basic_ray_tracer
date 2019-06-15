//
//  Tools.cpp
//  RayTracer
//
//  Created by Ben Nelson on 10/28/17.
//  Copyright © 2017 Ben Nelson. All rights reserved.
//


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include "Tools.h"

#define PI 3.14159265
#define NOFFSET 0.001
#define INFINITY -1
#define U 0
#define V 1
#define X "X"
#define Y "Y"
#define Z "Z"

Tools::Tools(){};
Tools::~Tools(){};


//Member Functions
Scene Tools::parseSceneFile(std::string filePath, std::string fileName)
{
    //Parse Scene File
    std::ifstream file;
    file.open(filePath+fileName);
    if (!file)
    {
        std::cout << "Unable to open file " + fileName + "\n";
        exit(1);   // call system to stop
    }
    else
    {
        std::cout << "Successful load of file: " + fileName + "\n";

    }
    
    Vec camLookAt;
    Vec camLookFrom;
    Vec camLookUp;
    double fov = 0.0;
    Vec directionToLight;
    Vec lightColor;
    Vec ambientLight;
    Vec bgColor;
    std::vector<Sphere> sphereList;
    std::vector<Triangle> triList;

    //Start Parsing
    while(!file.eof())
    {
        //Get each line of the file
        string currentLine = "";
        getline(file,currentLine);
        
        string token = currentLine.substr(0, currentLine.find(' '));
        
        if(token == "CameraLookAt")
        {
            camLookAt = extractVec3(currentLine);
        }
        else if(token == "CameraLookFrom")
        {
            camLookFrom = extractVec3(currentLine);

        }
        else if(token == "CameraLookUp")
        {
            camLookUp = extractVec3(currentLine);

        }
        else if(token == "FieldOfView")
        {
            std::stringstream ss(currentLine);
            string junk;
            ss >> junk;
            ss >> fov;

        }
        else if(token == "DirectionToLight")
        {
            string part1 = currentLine.substr(0, currentLine.find("LightColor"));
            string part2 = currentLine.substr(currentLine.find("LightColor"), currentLine.length());
            directionToLight = extractVec3(part1);
            lightColor = extractVec3(part2);
            
        }
        else if(token == "AmbientLight")
        {
            ambientLight = extractVec3(currentLine);
        }
        else if(token == "BackgroundColor")
        {
            bgColor = extractVec3(currentLine);
        }
        else if(token == "Sphere")
        {
            sphereList.push_back(extractSphere(currentLine));
        }
        else//Triangle
        {
            if(token == "Triangle"){
                triList.push_back(extractTriangle(currentLine));
            }
        }
        
        file.peek();
        
        //std::cout << currentLine + "\n";
    }

    return Scene(camLookAt,camLookFrom,camLookUp,fov,directionToLight,lightColor,ambientLight,bgColor,sphereList,triList);
    
};

void Tools::outputFile(string outPath, string fileName, int width, int height, string image)
{
    string file = fileName.substr(0, fileName.find("."));
    string type = ".ppm";
    ofstream output(outPath+file+type);
    string w = to_string(width);
    string h = to_string(height);
    
    std::string header = "P3\n #diffuse - Benji\n" +w +" "+ h+ "\n 255 \n";
    header += image;
    output << header;
    
}

Vec Tools::extractVec3(string line)
{
    std::stringstream ss(line);
    string token;
    Vec v1;
    
    //We don't need the first token
    ss >> token;
    
    double x = 0.0;
    ss >> x;
    v1.setA1(x);
  
    double y = 0.0;
    ss >> y;
    v1.setA2(y);

    double z = 0.0;
    ss >> z;
    v1.setA3(z);


    return v1;
    
};

Sphere Tools::extractSphere(string line)
{
    //Example:
    //Sphere Center .35 0 -.1 Radius .05 Material Diffuse 1 1 1 SpecularHighlight 1 1 1 PhongConstant 4
    //Sphere Center 0 .3 0 Radius .2 Material Reflective .75 .75 .75
    std::stringstream ss(line);
    string junk;
    Vec c;
    double r;
    Vec m;
    Vec s;
    double p;
    
    //Sphere
    ss >> junk;
    //Center
    ss >> junk;
    //X
    double x = 0.0;
    ss >> x;
    c.setA1(x);
    //Y
    double y = 0.0;
    ss >> y;
    c.setA2(y);
    //Z
    double z = 0.0;
    ss >> z;
    c.setA3(z);
    
    //Radius
    ss >> junk;
    //R value
    ss >> r;
    
    //Material
    ss >> junk;
    //Diffuse
    ss >> junk;
    
    if(junk == "Reflective")
    {
        //X
        ss >> x;
        m.setA1(x);
        //Y
        ss >> y;
        m.setA2(y);
        //Z
        ss >> z;
        m.setA3(z);
        
        
        Sphere sphere = Sphere(c,r,m,Vec(),0);
        sphere.setReflective(true);
        return sphere;
    }
    else
    {
        //X
        ss >> x;
        m.setA1(x);
        //Y
        ss >> y;
        m.setA2(y);
        //Z
        ss >> z;
        m.setA3(z);
        
        //SpecularHightlight
        ss >> junk;
        //X
        ss >> x;
        s.setA1(x);
        //Y
        ss >> y;
        s.setA2(y);
        //Z
        ss >> z;
        s.setA3(z);
        
        //Phong Constant
        ss >> junk;
        //R value
        ss >> p;
        
        
        return Sphere(c,r,m,s,p);
 
    }
};

Triangle Tools::extractTriangle(string line)
{
    //Example:
    //Triangle  -.2 .1 .1   -.2 -.5 .2   -.2 .1 -.3 Material Diffuse 1 1 0 SpecularHighlight 1 1 1 PhongConstant 4
    std::stringstream ss(line);
    string junk;
    Vec v1;
    Vec v2;
    Vec v3;

    Vec m;
    Vec s;
    double p;
    
    //Triangle
    ss >> junk;
    //X
    double x = 0.0;
    ss >> x;
    v1.setA1(x);
    //Y
    double y = 0.0;
    ss >> y;
    v1.setA2(y);
    //Z
    double z = 0.0;
    ss >> z;
    v1.setA3(z);
    
    //V2
    ss >> x;
    v2.setA1(x);
    //Y
    ss >> y;
    v2.setA2(y);
    //Z
    ss >> z;
    v2.setA3(z);
    
    //V3
    ss >> x;
    v3.setA1(x);
    //Y
    ss >> y;
    v3.setA2(y);
    //Z
    ss >> z;
    v3.setA3(z);
    
    //Material
    ss >> junk;
    //Diffuse
    ss >> junk;
    //X
    ss >> x;
    m.setA1(x);
    //Y
    ss >> y;
    m.setA2(y);
    //Z
    ss >> z;
    m.setA3(z);
    
    //SpecularHightlight
    ss >> junk;
    //X
    ss >> x;
    s.setA1(x);
    //Y
    ss >> y;
    s.setA2(y);
    //Z
    ss >> z;
    s.setA3(z);
    
    //Phong Constant
    ss >> junk;
    //p value
    ss >> p;
    
    return Triangle(v1,v2,v3,m,s,p);
};

string Tools::rayTrace(Scene scene, int xPixels, int yPixels)
{
    //Make array of pixels to store RGB values
    Vec pixels[xPixels][yPixels];
    Vec directionToLight = scene.getDirectionToLight();
    Vec lColor = scene.getLightColor();
    
    //Convert BG color to 0 - 255 range
    Vec bgColor = convertColor(scene.getBgColor());
    //Convert BG color to 0 - 255 range
    Vec ambient = scene.getAmbientLight();

    double fov = scene.getFOV();
    Vec lookFrom = scene.getCamLookFrom();
    //Vec lookAt = scene.getCamLookAt();
    
    //For now we assume the look at is (0,0,0) and the camera is z > 0, so D distance will be positive
    double distance = lookFrom.getA3();
    
    //Now know distance we need to calculate the ViewPort Image Plane
    //Assume aspect ratio is 1:1
    double UVmax = distance * tan( ((fov/2) * PI)/180.0 );
    double UVmin = -UVmax;
    int IJmin = 0;
    int IJmax = xPixels - 1;
    
    //For each pixel
    Vec rayO = lookFrom;
    Vec rayD = Vec();
    Vec rayI = Vec();
    vector<Sphere> sphereList = scene.getSphereList();
    vector<Triangle> triList = scene.getTriList();
    int sphereCount = (int) sphereList.size();
    int triCount = (int) triList.size();
    
    for(int j = yPixels-1; j > -1; j--)
    {
        for(int i = 0; i < xPixels; i++)
        {
            //make a primary ray, and shoot it out from the current pixel
            rayD = calculateRayDirection(lookFrom, UVmax,  UVmin,  IJmax, IJmin, i, j);
            //Sphere T Value
            double tSphere = 0.0;
            //Triangle T Value
            double tTri = 0.0;
            //Check Spheres
            bool intersected = false;
            double prevT = 0;
            for(int k = 0; k < sphereCount; k++){
                if(rayIntersectsWithSphere(tSphere, rayO,rayD,rayI,sphereList[k])){
                    
                    //If it has intersected, we need to send out a shadow ray
                    Vec currentColor = sphereList[k].getMaterial();
                    Vec objectSpec = sphereList[k].getSpecHighlight();
                    double phong = sphereList[k].getPhongConstant();
                    double radius = sphereList[k].getRadius();
                    Vec sNormal = calculateSphereNormal(rayI, sphereList[k].getCenter(), radius);
                    Vec offset = Vec((sNormal.getA1()*NOFFSET), (sNormal.getA2()*NOFFSET), (sNormal.getA3()*NOFFSET));
                    Vec sRayO = add(rayI, offset);
                    Vec sRayD = directionToLight;
                    Vec color = Vec();
                    
                    if(sphereList[k].isReflective()){
                        Vec reflectRayO = rayI;
                        Vec reflectRayD = calculateReflectDirection(rayD, sNormal);
                        Vec reflectColor = scene.getBgColor();
                        color = sendOutRefectionRay(reflectRayO, reflectRayD, sphereList, triList, ambient, lColor, directionToLight, lookFrom, reflectColor, currentColor, sNormal, k);
                    }
                    else{
                        color = sendOutShadowRay(sRayO, sRayD, sphereList, triList, ambient, currentColor, sNormal,lColor,lookFrom, objectSpec, phong);
                    }
                    color = convertColor(color);
                    pixels[i][j] = color;
                    intersected = true;
                }
                else{
                    if(!intersected){
                        pixels[i][j] = bgColor;
                    }
                }
            }
            prevT = 0;
            for(int k = 0; k < triCount; k++){
                if(rayIntersectsWithTriangle(tTri, rayO,rayD,rayI,triList[k]))
                {
                    //Make sure the closest Triangle is rendered on top
                    if(intersected){
                        if(prevT > tTri){
                            intersected = false;
                        }
                    }
                    
                    if(tTri < tSphere || !intersected) // The triangle is in front of the sphere is tTri is < tSphere or there is no sphere intersection
                    {
                        //If it has intersected, we need to send out a shadow ray
                        Vec currentColor = triList[k].getMatDiffuse();
                        Vec objectSpec = triList[k].getSpecHighlight();
                        double phong = triList[k].getPhongConstant();
                        Vec tNormal = calculateTriangleNormal(triList[k]);
                        Vec n = reverse(tNormal);
                        Vec offset = Vec((n.getA1()*NOFFSET), (n.getA2()*NOFFSET), (n.getA3()*NOFFSET));
                        Vec tRayO = add(rayI, offset);
                        Vec tRayD = directionToLight;
                        Vec color = sendOutShadowRay(tRayO, tRayD, sphereList, triList, ambient, currentColor, n, lColor, lookFrom, objectSpec, phong);
                        color = convertColor(color);
                        pixels[i][j] = color;
                    }
                    prevT = tTri;
                    intersected = true;
                }
                else{
                    if(!intersected){
                        pixels[i][j] = bgColor;
                    }
                }
            }

            intersected = false; 
        }
    }
    
    
    
    
    
    
    
    //Convert pixels for a ppm format image
    string pixelStr = "";
    for(int j = yPixels-1; j > -1; j--)
    {
        for(int i = 0; i < xPixels; i++)
        {
            Vec v = pixels[i][j];
            string r = to_string((int) v.getA1());
            string g = to_string((int) v.getA2());
            string b = to_string((int) v.getA3());
            pixelStr += r +" "+ g+" "+ b+ " ";
            
        }
    }
    
    return pixelStr;
};

Vec Tools::sendOutShadowRay(Vec rayO, Vec rayD, vector<Sphere> sphereList, vector<Triangle> triList, Vec ambientLight, Vec currentColor, Vec n, Vec lcolor, Vec camera, Vec objectSpecular, double phongE)
{
    //See if the shadow ray intersects with any spheres
    Vec rayI = Vec();
    int sCount = (int) sphereList.size();
    
    double sphT = 0;
    for(int i = 0; i < sCount; i++){
        if(rayIntersectsWithSphere(sphT, rayO, rayD, rayI, sphereList[i])){
            return multiply(ambientLight, currentColor);
        }
    }
    //See if the shadow ray intersects with any triangles
    int tCount = (int) triList.size();
    double triT = 0;
    for(int i = 0; i < tCount; i++){
        if(rayIntersectsWithTriangle(triT, rayO, rayD, rayI, triList[i])){
            return multiply(ambientLight, currentColor);
        }
    }
    
    Vec Ca = multiply(ambientLight, currentColor);
    Vec Cd = calculateDiffuse(currentColor, lcolor, n, rayD);
    
    //Calculate View direction
    Vec v = subtract(camera, rayO);
    v.normalize();
    
    Vec Cs = calculateSpecular(v, n, rayD, objectSpecular,phongE);
    
    Ca = clampColor(Ca);
    Cd = clampColor(Cd);
    Cs = clampColor(Cs);

    Vec finalColor = clampColor(add(Ca,Cd));
    finalColor = clampColor(add(finalColor, Cs));

    return finalColor;
};

Vec Tools::sendOutRefectionRay(Vec rayO, Vec rayD, vector<Sphere> sphereList, vector<Triangle> triList, Vec ambient, Vec lColor, Vec directionToLight, Vec lookFrom, Vec bgColor, Vec objectColor, Vec N, int currShapeI)
{
    //Now we know from where to shoot (rayO) and the direction to shoot (rayD)
    double t = 0;
    Vec rayI = Vec();
    double lowestT = INFINITY;
    Vec lowestRayI = rayI;
    int lowestIndex = 0;
    bool lowestIsSphere = false;
    bool lowestIsTri = false;
    
    
    int sphereCount = (int) sphereList.size();
    for(int i = 0; i < sphereCount; i++){
        if(i != currShapeI){
            if(rayIntersectsWithSphere(t, rayO, rayD, rayI, sphereList[i])){
                //If we intersect with a sphere, we need to record the T value, RayI intersection point and the i index.
                
                // If we have checked at least one sphere, compare the previous with the current
                if(i > 0){
                    if(t < lowestT){
                        lowestT = t;
                        lowestRayI = rayI;
                        lowestIndex = i;
                    }
                }
                else{
                    lowestT = t;
                    lowestRayI = rayI;
                    lowestIndex = i;
                    lowestIsSphere = true;
                }
            }
        }
    }
    //lowestIsSphere = false;
     
    rayO.normalize();
    rayD.normalize();
    
    //Now check the triangles
    int triCount = (int) triList.size();
    for(int i = 0; i < triCount; i++){
        if(rayIntersectsWithTriangle(t, rayO, rayD, rayI, triList[i])){
            if(!lowestIsSphere){
                //Then this intersected triangle automatically becomes the lowest
                lowestT = t;
                lowestRayI = rayI;
                lowestIndex = i;
                lowestIsTri = true;
                lowestIsSphere = false;
                
            }
            else{
                if(t < lowestT){
                    lowestT = t;
                    lowestRayI = rayI;
                    lowestIndex = i;
                    lowestIsTri = true;
                    lowestIsSphere = false;
                }
            }
        }
    }

    //Now at this point we should have the object the ray intersects with or it didn't intersect.
    if(!lowestIsSphere && !lowestIsTri){
        return multiply(bgColor, objectColor);
    }
    if(lowestIsTri){
        //Lowest T value is a triangle
        Triangle tri = triList[lowestIndex];
        double phong = tri.getPhongConstant();
        Vec objSpec = tri.getSpecHighlight();
        Vec objColor = tri.getMatDiffuse();
        Vec tNormal = calculateTriangleNormal(tri);
        Vec n = reverse(tNormal);
        Vec offset = Vec((n.getA1()*NOFFSET), (n.getA2()*NOFFSET), (n.getA3()*NOFFSET));
        Vec tRayO = add(rayI, offset);
        Vec tRayD = directionToLight;
    
        return sendOutShadowRay(tRayO, tRayD, sphereList, triList, ambient, objColor, n, lColor, lookFrom, objSpec, phong);
    }
    else{
        //Lowest T value is a sphere
        Sphere sphere = sphereList[lowestIndex];
        Vec objColor = sphere.getMaterial();
        Vec objSpec = sphere.getSpecHighlight();
        double phong = sphere.getPhongConstant();
        double radius = sphere.getRadius();
        Vec sNormal = calculateSphereNormal(rayI, sphere.getCenter(), radius);
        Vec offset = Vec((sNormal.getA1()*NOFFSET), (sNormal.getA2()*NOFFSET), (sNormal.getA3()*NOFFSET));
        Vec sRayO = add(rayI, offset);
        Vec sRayD = directionToLight;

        return sendOutShadowRay(sRayO, sRayD, sphereList, triList, ambient, objColor, sNormal,lColor,lookFrom, objSpec, phong);
        
    }
}

Vec Tools::calculateRayDirection(Vec lookFrom, double UVmax, double UVmin, double IJmax, double IJmin, int iPixelCoord, int jPixelCoord)
{
    double i = ((iPixelCoord - IJmin)*( (UVmax - UVmin)/ (IJmax - IJmin) )) + UVmin;
    double j = ((jPixelCoord - IJmin)*( (UVmax - UVmin)/ (IJmax - IJmin) )) + UVmin;
    double w = 0;
    
    
    Vec s = Vec(i,j,w);
    Vec rayDir = subtract(s,lookFrom);
    
    //Now we just need to normalize the direction
    rayDir.normalize();
    return rayDir;

    
};

Vec Tools::calculateSphereNormal(Vec rayI, Vec center, double radius)
{
    //Normal = (rayI - Sc)/r
    Vec v = subtract(rayI, center);
    v = Vec((v.getA1()/radius),(v.getA2()/radius),(v.getA3()/radius));
    v.normalize();
    return v;
};

Vec Tools::calculateTriangleNormal(Triangle tri)
{
    //First perform the ray/plane intersection with the plane in which the polygon lies
    //Pn is normal of the plane
    Vec v1 = subtract(tri.getV1(), tri.getV2());
    Vec v2 = subtract(tri.getV3(), tri.getV2());
    //compute cross product of v1 x v2
    return cross(v1,v2);
};

Vec Tools::calculateReflectDirection(Vec vDir, Vec N)
{
    //R = vDir - 2 N (vDir dot N)
    double dotResult = dot(vDir, N);
    Vec reflectDirection = multiplyByScalar(N, dotResult);
    reflectDirection = multiplyByScalar(reflectDirection, 2);
    reflectDirection = subtract(vDir, reflectDirection);
    reflectDirection.normalize();
   
    return reflectDirection;
};

Vec Tools::calculateDiffuse(Vec Od, Vec L ,Vec n, Vec l)
{   //Cd = Od * lightColor * max0(n dot l)
    //l = light direction
    //L = light color
    
    l.normalize();
    double dotResult = dot(n, l);
    if(dotResult < 0)
    {
        dotResult = 0;
    }
  
    Vec Cd = multiplyByScalar(L, dotResult);
    Cd = multiply(Od, Cd);
    
    return Cd;
};

Vec Tools::calculateSpecular(Vec cam, Vec n, Vec l, Vec objectSpecular, double phongE)
{
    /*
     Cs = Os * max0(V dot R)^P
     Os = objectSpecular
     V = cam
     R = 2n(n dot l) - l
     vec3 R = normalize( ((2*n) * dot(n,l)) - l);
     vec3 Cs = objectSpecular * pow(max(0, dot(V,R)),phongExp);
     */
    
    double dotResult = dot(n, l);
    if(dotResult < 0){
        dotResult = 0;
    }
    Vec r = multiplyByScalar(n, 2);
    r = multiplyByScalar(r, dotResult);
    r = subtract(r, l);
    r.normalize();

    
    dotResult = dot(cam, r);
    if(dotResult < 0)
    {
        dotResult = 0;
    }
    double scalar = pow(dotResult,phongE);
    Vec Cs = multiplyByScalar(objectSpecular, scalar);
    
    return Cs;
    
}

Vec Tools::add(Vec v1, Vec v2)
{
    return Vec(v1.getA1()+v2.getA1(), v1.getA2()+v2.getA2() , v1.getA3()+v2.getA3());
};

Vec Tools::subtract(Vec v1, Vec v2)
{
    return Vec(v1.getA1()-v2.getA1(), v1.getA2()-v2.getA2() , v1.getA3()-v2.getA3());
};

Vec Tools::multiply(Vec v1, Vec v2)
{
    double ax = v1.getA1();
    double ay = v1.getA2();
    double az = v1.getA3();
    
    double bx = v2.getA1();
    double by = v2.getA2();
    double bz = v2.getA3();
    
    return Vec((ax*bx),(ay*by),(az*bz));
};

Vec Tools::multiplyByScalar(Vec v1, double scalar)
{
    return Vec((v1.getA1()*scalar), (v1.getA2()*scalar), (v1.getA3()*scalar));
};

Vec Tools::reverse(Vec v1)
{
    return Vec( -v1.getA1(), -v1.getA2(), -v1.getA3() );
};

Vec Tools::cross(Vec v1, Vec v2)
{
    //Cross product of A (v1) x B (v2)
    //(AyBz - AzBy)x , (AzBx - AxBz)y , (AxBy-AyBx)z
    double x = (v1.getA2() * v2.getA3()) - (v1.getA3() * v2.getA2());
    double y = (v1.getA3() * v2.getA1()) - (v1.getA1() * v2.getA3());
    double z = (v1.getA1() * v2.getA2()) - (v1.getA2() * v2.getA1());
    
    Vec cross = Vec(x,y,z);
    cross.normalize();
    return cross;
};

double Tools::dot(Vec v1, Vec v2)
{
    double ax = v1.getA1();
    double ay = v1.getA2();
    double az = v1.getA3();
    
    double bx = v2.getA1();
    double by = v2.getA2();
    double bz = v2.getA3();
    
    return (ax*bx) + (ay*by) + (az*bz);
}

double Tools::dotProductOf(double a1[], double b1[])
{
    return (a1[U] * b1[U]) + (a1[V] * b1[V]);
};

Vec Tools::convertColor(Vec inColor)
{
    double r = inColor.getA1();
    double g = inColor.getA2();
    double b = inColor.getA3();
    
    r *= 255.0;
    g *= 255.0;
    b *= 255.0;
    
    return Vec((int) r, (int) g, (int) b);
};

Vec Tools::clampColor(Vec inColor)
{
    if(inColor.getA1()>1)
    {
        inColor.setA1(1);
    }
    if(inColor.getA2()>1)
    {
        inColor.setA2(1);
    }
    if(inColor.getA3()>1)
    {
        inColor.setA3(1);
    }
    
    if(inColor.getA1()<0)
    {
        inColor.setA1(0);
    }
    if(inColor.getA2()<0)
    {
        inColor.setA2(0);
    }
    if(inColor.getA3()<0)
    {
        inColor.setA3(0);
    }
    
    return inColor;
};

string Tools::determineProjectionAxis(Vec normal)
{
    double x = normal.getA1();
    double y = normal.getA2();
    double z = normal.getA3();

    //ABSOLUTE VALUE
    if(x < 0)
    {
        x = -1*x;
    }
    if(y < 0)
    {
        y = -1*y;
    }

    if(z < 0)
    {
        z = -1*z;
    }
    
    if(x > y && x > z)// X IS GREATEST
    {
        //Return x
        return X;
    }
    if(y > x && y > z) // Y IS GREATEST
    {
        //Return y
        return Y;
    }
    if(z > x && z > y) // Z IS GREATEST
    {
        //Return z
        return Z;
    }
    
    //If that fails, then choose the next biggest
    if(x > y)
    {
        return X;
    }
    if(x > z)
    {
        return X;
    }
    
    if(y > x)
    {
        return Y;
    }
    if(y > z)
    {
        return Y;
    }
    
    if(z > x)
    {
        return Z;
    }
    if(z > y)
    {
        return Z;
    }
    
    return X;

};

bool Tools::rayIntersectsWithSphere(double &t, Vec rayO,Vec rayD, Vec &rayI, Sphere sphere)
{
    double Xo = rayO.getA1();
    double Yo = rayO.getA2();
    double Zo = rayO.getA3();
    
    double Xd = rayD.getA1();
    double Yd = rayD.getA2();
    double Zd = rayD.getA3();
    
    double Xc = sphere.getCenter().getA1();
    double Yc = sphere.getCenter().getA2();
    double Zc = sphere.getCenter().getA3();
    
    double r = sphere.getRadius();
    
    //Calculate B and C of the quadratic
    double b = 2 * ( (Xd*Xo) - (Xd*Xc) + (Yd*Yo) - (Yd*Yc) + (Zd*Zo) - (Zd*Zc) );
    double c = ( pow(Xo,2) - (2*(Xo*Xc)) + pow(Xc,2) + pow(Yo,2) - (2*(Yo*Yc)) + pow(Yc,2) + pow(Zo,2) - (2*(Zo*Zc)) + pow(Zc,2) - pow(r,2) );
    
    double d = pow(b,2) - (4*c);
    
    if(d < 0)
    {
        //There is no intersection
        return false;
    }
    
    //Calculate smaller intersection parameter
    double t0 = (-b - sqrt(d))/2;
    if(t0 <= 0)
    {
        //Calculate larger intersection parameter
        double t1 = (-b + sqrt(d))/2;
        if(t1 <= 0)
        {
            //Point of intersection is behind ray
            return false;
        }
        else
        {
            t = t1;
        }
    }
    else
    {
        t = t0;
    }
    //Point of intersection p = rO + rD*t
    rayD.multiplyByScalar(t);
    rayI = add(rayO, rayD);
  
    return true;
};

bool Tools::rayIntersectsWithTriangle(double &t, Vec rayO,Vec rayD, Vec &rayI, Triangle tri)
{
    Vec normal = calculateTriangleNormal(tri);

    if(!rayIntersectsWithPlane(t,rayO, rayD, rayI,normal,tri)){
        return false;
    }
    
    //Next, determine whether the intersection point lies within the polygon
    //With the computed the normal of a triangle
    string projectionAxis = determineProjectionAxis(normal);
    if(!pointInTriangle(rayI, tri, projectionAxis)){
        return false;
    }
   
    return true;
};

bool Tools::rayIntersectsWithPlane(double &t, Vec rayO,Vec rayD, Vec &rayI, Vec &planeNormal, Triangle tri)
{
    // distance D is d = -(Ax + By + Cz) where Pn=(A,B,C) and (x,y,z) can be any point in the plane. In our case, any plane in the triangle will do.
    Vec xyz = tri.getV2();
    double x = xyz.getA1();
    double y = xyz.getA2();
    double z = xyz.getA3();
    
    double a = planeNormal.getA1();
    double b = planeNormal.getA2();
    double c = planeNormal.getA3();
    
    double d = -1* ((a*x) + (b*y) + (c*z));
    
    // t = -(Pn dot rayO + D) / (Pn dot rayD)
    
    double Vd = dot(planeNormal, rayD);
    
    /*
    if(Vd >= 0){
        return true; //and 1 sided plane then YES, it is selected
    }*/
    
    if(Vd == 0){
        return false; //ray is parallel to plane
    }
    
    //Compute Vo = -(Pn dot rayO + D)
    double Vo = -1* ((dot(planeNormal, rayO)) + d);

    //Compute t = Vo / Vd
    t = Vo/Vd;
    
    if(t < 0)
    {
        return false;
    }
    
    //if Vd > 0 reverse the plane's normal
    if(Vd > 0){
        planeNormal.setA1(-1 * planeNormal.getA1());
        planeNormal.setA2(-1 * planeNormal.getA2());
        planeNormal.setA3(-1 * planeNormal.getA3());
        
        if(planeNormal.getA1() == -0)
        {
            planeNormal.setA1(0);
        }
        if(planeNormal.getA2() == -0)
        {
             planeNormal.setA2(0);
        }
        if(planeNormal.getA3() == -0)
        {
             planeNormal.setA3(0);
        }
        
    }
    
    
    
    
    //r = (Xo + Xdt) , (Yo + Ydt) , (Zo + Zdt);
    double Xo = rayO.getA1();
    double Yo = rayO.getA2();
    double Zo = rayO.getA3();
    
    double Xdt = rayD.getA1() * t;
    double Ydt = rayD.getA2() * t;
    double Zdt = rayD.getA3() * t;
    rayI = Vec( (Xo + Xdt) , (Yo + Ydt) , (Zo + Zdt));
    
    return true;
};

bool Tools::pointInTriangle(Vec rayD, Triangle tri, string projectionAxis)
{
    //Essentially gut the projection Axis
    double q[2];
    double p1[2];
    double p2[2];
    double p3[2];

    if(projectionAxis == X)
    {
        q[U]= rayD.getA2();
        q[V]= rayD.getA3();
        
        p1[U] = tri.getV1().getA2();
        p1[V] = tri.getV1().getA3();
        p2[U] = tri.getV2().getA2();
        p2[V] = tri.getV2().getA3();
        p3[U] = tri.getV3().getA2();
        p3[V] = tri.getV3().getA3();
    }
    else if(projectionAxis == Y)
    {
        q[U]= rayD.getA1();
        q[V]= rayD.getA3();
        
        p1[U] = tri.getV1().getA1();
        p1[V] = tri.getV1().getA3();
        p2[U] = tri.getV2().getA1();
        p2[V] = tri.getV2().getA3();
        p3[U] = tri.getV3().getA1();
        p3[V] = tri.getV3().getA3();
    }
    else//(projectionAxis == Z)
    {
        q[U]= rayD.getA1();
        q[V]= rayD.getA2();
        
        p1[U] = tri.getV1().getA1();
        p1[V] = tri.getV1().getA2();
        p2[U] = tri.getV2().getA1();
        p2[V] = tri.getV2().getA2();
        p3[U] = tri.getV3().getA1();
        p3[V] = tri.getV3().getA2();

    }
    
     //(q - p1) dot (p2 - p1)ORTH  = result1
     //(q - p2) dot (p3 - p2)ORTH  = result2
     //(q - p3) dot (p1 - p3)ORTH  = result3
     //if results are ALL negative or ALL positve, then return true, else false;
    
    //(q - p1) dot (p2 - p1)ORTH  = result1________________________________
    double a1[2] = {(q[U] - p1[U]),(q[V] - p1[V])};
    double b1[2] = {(p2[U] - p1[U]),(p2[V] - p1[V])};
    double b1_ORTHO[2] = {-b1[V], b1[U]};
    
    double resultOne = dotProductOf(a1,b1_ORTHO);
    //_____________________________________________________________________
    
    //(q - p2) dot (p3 - p2)ORTH  = result2________________________________
    double a2[2] = {(q[U] - p2[U]),(q[V] - p2[V])};
    double b2[2] = {(p3[U]- p2[U]),(p3[V] - p2[V])};
    double b2_ORTHO[2] = {-b2[V], b2[U]};
    
    double resultTwo = dotProductOf(a2,b2_ORTHO);
    //_____________________________________________________________________
    
    //(q - p3) dot (p1 - p3)ORTH  = result3________________________________
    double a3[2] = {(q[U] - p3[U]),(q[V] - p3[V])};
    double b3[2] = {(p1[U] - p3[U]),(p1[V] - p3[V])};
    double b3_ORTHO[2] = {-b3[V], b3[U]};
    
    double resultThree = dotProductOf(a3,b3_ORTHO);
    //_____________________________________________________________________
    
    
    if(!allResultsArePosOrNeg(resultOne,resultTwo,resultThree)){
        return false;
    }
 
    return true;
};

bool Tools::allResultsArePosOrNeg(double resultOne, double resultTwo, double resultThree)
{
    if(resultOne == -0)
    {
        resultOne =0;
    }
    if(resultTwo == -0)
    {
        resultTwo =0;
    }
    if(resultTwo == -0)
    {
        resultTwo =0;
    }
    
    
    if( ((resultOne > 0) && (resultTwo > 0) && (resultThree > 0)) || ((resultOne < 0) && (resultTwo < 0) && (resultThree < 0)) )
    {
        return true;
    }
    else
    {
        return false;
    }
};


