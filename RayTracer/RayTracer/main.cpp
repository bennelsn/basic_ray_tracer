//
//  main.cpp
//  RayTracer
//
//  Created by Ben Nelson on 10/28/17.
//  Copyright © 2017 Ben Nelson. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "Tools.h"

std::string FILEPATH = "/Users/BenNelson/Documents/CS_455/RayTracer/RayTracer/SceneFiles/";
std::string OUTPATH = "/Users/BenNelson/Documents/CS_455/RayTracer/RayTracer/Exports/Demo/";
int widthInPixels = 480;
int heightInPixels = 270;

int main()
{
   
    //Get the scene from the file
    string filename = "custom.rayTracing";
    Scene scene = Tools().parseSceneFile(FILEPATH, filename);
    
    //Start Timer **********
    std::clock_t start;
    double duration;
    start = std::clock();
    int startFrame = 1;
    int endFrame = 1;

    //Render the scene
    printf("Rendering...\n");
    string image = Tools().rayTrace(scene, widthInPixels, heightInPixels);
        
    //File export
    string nameOfFile = "image" + to_string(i) + ".rayTracing";
    Tools().outputFile(OUTPATH, nameOfFile, widthInPixels, heightInPixels, image);
    
    
    //End Timer ************
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    
    
    printf("Done.\n");
    printf("Render Time: ");
    std::cout <<  std::setprecision(3) << duration;
    if(duration > 1)
    {
        printf(" seconds");
    }
    else
    {
        printf(" second");
    }
    printf("\n\n");

    return 0;
}


