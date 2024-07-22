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
    cam.eyep = {0,-4,10};
    cam.lookp = {0,0,0};
    cam.up = {0,1,0};

//    CSphere* kula1 = new CSphere({-2.5, 1.3, -3}, 1);
//    CSphere* kula2 = new CSphere({0, 0, 0}, 1.6);
//    CTriangle* trojkat1 = new CTriangle({3,3,-5}, {-3,3,-10}, {-3,-3,-8});
//    objectList.push_back(kula1);
//    objectList.push_back(kula2);
//    objectList.push_back(trojkat1);
//    CLight light1(glm::vec3(-3,-2,8));
//    light1.color = glm::vec3(0.6,0.6,0.6);
//    lightList.push_back(light1);
//    CSphere* kula_zad12 = new CSphere({0,0,0}, 1.6);
//    kula_zad12->matAmbient = {0.1,0,0};
//    kula_zad12->matDiffuse = {0.6,0,0};
//    kula_zad12->matSpecular = {0.7,0.7,0.7};
//    kula_zad12->matShininess = 30;
//    kula_zad12->reflectance = 0;
////    kula_zad12->isTexture = true;
////    kula_zad12->texture = CImage::createTexture(400,400);
////    objectList.push_back(kula_zad12);
////zad 14
//    CLight light2(glm::vec3(-3,-2,8));
//    light2.color = glm::vec3(0.6,0.6,0.6);
//    lightList.push_back(light2);
//    CSphere* kula14_1 = new CSphere({-1,0,3}, 0.4);
//    kula14_1->matAmbient = {0,0.1,0};
//    kula14_1->matDiffuse = {0,0.6,0};
//    kula14_1->matSpecular = {0.7,0.7,0.7};
//    kula14_1->matShininess = 30;
//    kula14_1->reflectance = 0;
////    kula14_1->isTexture = true;
////    kula14_1->texture = CImage::createTexture(400,400);
//    objectList.push_back(kula14_1);
//
//    CSphere* kula14_2 = new CSphere({0,0,0}, 1.6);
//    kula14_2->matAmbient = {0.1,0,0};
//    kula14_2->matDiffuse = {0.6,0,0};
//    kula14_2->matSpecular = {0.7,0.7,0.7};
//    kula14_2->matShininess = 30;
//    kula14_2->reflectance = 0;
////    kula14_2->isTexture = true;
////    kula14_2->texture = CImage::createTexture(400,400);
//    objectList.push_back(kula14_2);
//
//    CSphere* kula14_3 = new CSphere({-3,-2,-2}, 0.6);
//    kula14_3->matAmbient = {0,0,0.1};
//    kula14_3->matDiffuse = {0,0,0.6};
//    kula14_3->matSpecular = {0.7,0.7,0.7};
//    kula14_3->matShininess = 30;
//    kula14_3->reflectance = 0;
////    kula14_3->isTexture = true;
////    kula14_3->texture = CImage::createTexture(400,400);
//    objectList.push_back(kula14_3);
//
//    CTriangle* trojkat14_1 = new CTriangle(
//            {5,5,-5},
//            {-5,5,-5},
//            {-5,-5,-5}
//    );
//    trojkat14_1->matAmbient = {0.1,0.1,0.1};
//    trojkat14_1->matDiffuse = {0.4,0.4,0.4};
//    trojkat14_1->matSpecular = {0,0,0};
//    trojkat14_1->matShininess = 0;
//    trojkat14_1->reflectance = 0;
//    objectList.push_back(trojkat14_1);
//
//    CTriangle* trojkat14_2 = new CTriangle(
//            {5,5,-5},
//            {-5,-5,-5},
//            {5,-5,-5}
//    );
//    trojkat14_2->matAmbient = {0.1,0.1,0.1};
//    trojkat14_2->matDiffuse = {0.4,0.4,0.4};
//    trojkat14_2->matSpecular = {0,0,0};
//    trojkat14_2->matShininess = 0;
//    trojkat14_2->reflectance = 0;
//    objectList.push_back(trojkat14_2);
// zadanie 15
    CSphere* sphere1 = new CSphere({ -1, 0, 3 }, 0.4);
    sphere1->matAmbient = {0, 0.1, 0};
    sphere1->matDiffuse = {0, 0.6, 0};
    sphere1->matSpecular = {0.7, 0.7, 0.7};
    sphere1->matShininess = 30;
    sphere1->reflectance = 0;
//    sphere1->isTexture = true;
    sphere1->texture = CImage::createTexture(400, 400);
    CSphere* sphere2 = new CSphere({ 0, 0, 0 }, 1.6);
    sphere2->matAmbient = {0.1, 0, 0};
    sphere2->matDiffuse = {0.6, 0, 0};
    sphere2->matSpecular = {0.7, 0.7, 0.7};
    sphere2->matShininess = 30;
    sphere2->reflectance = 0;
    CSphere* sphere3 = new CSphere({ -3, -2, -2 }, 0.6);
    sphere3->matAmbient = {0, 0, 0.1};
    sphere3->matDiffuse = {0, 0, 0.6};
    sphere3->matSpecular = {0.7, 0.7, 0.7};
    sphere3->matShininess = 30;
    sphere3->reflectance = 0;
    CTriangle* triangle1 = new CTriangle({5, 5, -5}, {-5, 5, -5}, {-5, -5, -5});
    triangle1->matAmbient = {0.1, 0.1, 0.1};
    triangle1->matDiffuse = {0.4, 0.4, 0.4};
    triangle1->matSpecular = {0, 0, 0};
    triangle1->matShininess = 0;
    triangle1->reflectance = 1;
    CTriangle* triangle2 = new CTriangle({5, 5, -5}, {-5, -5, -5}, {5, -5, -5});
    triangle2->matAmbient = {0.1, 0.1, 0.1};
    triangle2->matDiffuse = {0.4, 0.4, 0.4};
    triangle2->matSpecular = {0, 0, 0};
    triangle2->matShininess = 0;
    triangle2->reflectance = 1;
    objectList.push_back(triangle2);
    CLight light1(glm::vec3(-3, -2, 8));
    light1.color = {0.6, 0.6, 0.6};
    CLight light2(glm::vec3(5, -2, 8));
    light2.color = {0.3, 0.3, 0.3};
    objectList.push_back(sphere1);
    objectList.push_back(sphere2);
    objectList.push_back(sphere3);
    objectList.push_back(triangle1);
    objectList.push_back(triangle2);
    lightList.push_back(light1);
    lightList.push_back(light2);

}

