//
//  CScene.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"

#include<fstream>

/// \fn create(void)
/// \brief Adds components to the scene.
///
void CScene::create() {
    
    lightList.clear(); // clears vector with the light data
    objectList.clear(); // clears vector of pointers to objects

    // add camera, light sources, and objects
    cam.height = 400;
    cam.width = 500;
    cam.fov = 50;
    cam.eyep = {0,0,10};
    cam.lookp = {0,0,0};
    cam.up = {0,1,0};

    CSphere* kula1 = new CSphere({-2.5, 1.3, -3}, 1);
    CSphere* kula2 = new CSphere({0, 0, 0}, 1.6);
    objectList.push_back(kula1);
    objectList.push_back(kula2);

}

