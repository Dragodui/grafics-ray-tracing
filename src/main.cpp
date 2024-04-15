
#include <iostream>


#include "rt.h"

extern void draw_robot();
extern void draw_triangles();

///
int main (int argc, char * const argv[]) {

    std::cout << "ray tracing ... \n";

    CScene scene;
    scene.create(); // defines sample scene parameters
    if(scene.cam.width == 0) {
        std::cout << "WARNING: scene not defined" << std::endl;
        return -1;
    }

    CRayTrace rt;
    CRay ray;
    COutput results;


    /// computes primary ray matrix
     glm::mat3 ray_matrix = {
             {-1, 0, 250},
             {0,-1,200},
             {0,0,-536.436}
     };
     CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);
     std::cout << "Camera projection matrix:" << std::endl;
     PRINT_MAT3(ray_matrix);

     float fx = 0.5;
     float fy = 0.5;
     glm::vec3 f (fx,fy,1);
     float length = glm::length(ray_matrix * f);
     glm::vec3 dir = (ray_matrix * f) / length;
     std::cout << "Dir:" << std::endl;
     PRINT_VEC3("Vector",dir);

     CImage image(scene.cam.width, scene.cam.height);

//     int choose = 1;
//    /// computes ray direction for sample pixel positions
//    for (int j = 0; j < scene.cam.height; j++) {
//        for (int i = 0; i < scene.cam.width; i++) {
//            float fx = (float)i + 0.5f;
//            float fy = (float)j + 0.5f;
//
//            glm::vec3 f (fx,fy,1);
//            float length = glm::length(ray_matrix * f);
//            glm::vec3 dir = (ray_matrix * f) / length;
//
//            glm::vec3 rgb(0.0f, 0.0f, 0.0f);
//            switch (choose) {
//                case 1: // x
//                    rgb.x = (dir.x + 1.0f)/2.0f;
//                    image.setPixel(i,j,rgb);
//                    break;
//                case 2: // y
//                    rgb.y = (dir.y + 1.0f)/2.0f;
//                    image.setPixel(i,j,rgb);
//                    break;
//                case 3: // z
//                    rgb.z = (dir.z + 1.0f)/2.0f;
//                    image.setPixel(i,j,rgb);
//                    break;
//                default:
//                    std::cout << "incorrect choose" << std::endl;
//                    break;
//            }
//        }
//    }
//     image.save("rgb.png", true);
//
//     cv::imshow("image", image.getImage());
//     cv::waitKey();

     // zadanie 8
    ray.pos = glm::vec3(0,0,10);
    ray.dir = glm::vec3(0.3,0.3,-1.0);

    CSphere* kula = new CSphere({0, 0, 0}, 5);
    float t = kula->intersect(ray);
    std::cout << t << std::endl;

    //zadanie 9
    ray.pos = scene.cam.eyep;
    for (int j = 0; j < scene.cam.height; j++) {
        for (int i = 0; i < scene.cam.width; i++) {
            float fx = (float)i + 0.5f;
            float fy = (float)j + 0.5f;

            glm::vec3 f (fx,fy,1);
            float length = glm::length(ray_matrix * f);
            ray.dir = (ray_matrix * f) / length;
            results.col = {0,0,0};
            rt.rayTrace(scene, ray, results);

            if (results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
                results.col = {1,1,1};
            }
            image.setPixel(i,j, results.col);
        }
    }
    image.save("zadanie9.png", false);
    cv::imshow("zadanie9", image.getImage());
    cv::waitKey();
    /// creates raster image object
    // CImage image(scene.cam.width, scene.cam.height);

    /// main loop

            /// position of the image point
            /// ...

            /// primary ray
            /// ...

            /// background color
            // results.col = {0,0,0};
            /// secondary ray counter
            // results.tree = 0;
            /// ray energy
            // results.energy = 1.0f;
            
            /// rendering
            /// rt.rayTrace(scene, ray, results);

            /// handles pixel over-saturation
            // if(results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
            //    results.col = {1,1,1};
            //}

            /// writes pixel to output image
            // image.setPixel(i, j, results.rgb);


    /// writes image to disk file with gamma correction
    // image.save("output.png", true);

    // cv::imshow("image", image.getImage());
    // cv::waitKey();
    
    std::cout << std::endl << std::endl;
    return 0;
}


/// Draws two triangles
void draw_triangles() {

    CImage img(1000, 1000);
    
    glm::vec3 color1(0.9,0.1,0.1); // red
    glm::vec3 color2(0.1,0.9,0.1); // green
    
    // draw circle
    glm::vec3 pp(0.0,0.0,1.0);
    float radius = 0.1f;
    img.drawCircle(pp, radius, color1);
    
    // triangle vertices
    glm::vec3 pp0(0.4, 0.3, 1);
    glm::vec3 pp1(-0.4, 0.3, 1);
    glm::vec3 pp2(0.4, -0.3, 1);
    
    // draws triangle in 2D
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp1, pp2, color1);
    img.drawLine(pp2, pp0, color1);
    
    // translation
    float tX = 0.2f; // OX translation
    float tY = 0.1f; // OY translation
    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix
    PRINT_MAT3(mTrans);

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;

    // draws triangle after translation
    img.drawLine(pp0, pp1, color2);
    img.drawLine(pp1, pp2, color2);
    img.drawLine(pp2, pp0, color2);

    img.save("robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();

}

/// Draws robot.
void draw_robot() {
    CImage img(1000, 1000);

    glm::vec3 color1(0.9,0.1,0.1); // red
    glm::vec3 color2(0.1,0.9,0.1); // green

    // draw head
    glm::vec3 pp(0,0.3,1.0);
    float radius = 0.1f;
    img.drawCircle(pp, radius, color1);

    // body
    glm::vec3 pp0(0.1, 0.2, 1);
    glm::vec3 pp1(0.1, -0.2, 1);
    glm::vec3 pp2(-0.1, -0.2, 1);
    glm::vec3 pp3(-0.1, 0.2, 1);

    // draws body
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp1, pp2, color1);
    img.drawLine(pp2, pp3, color1);
    img.drawLine(pp3, pp0, color1);

    // left arm
    glm::vec3 l_arm0(0.1, 0.2, 1);
    glm::vec3 l_arm1(0.3, 0.2, 1);
    glm::vec3 l_arm2(0.3, 0.1, 1);
    glm::vec3 l_arm3(0.1, 0.1, 1);

    // draws left arm
    img.drawLine(l_arm0, l_arm1, color1);
    img.drawLine(l_arm1, l_arm2, color1);
    img.drawLine(l_arm2, l_arm3, color1);
    img.drawLine(l_arm3, l_arm0, color1);

    // right arm
    glm::vec3 r_arm0(-0.1, 0.2, 1);
    glm::vec3 r_arm1(-0.3, 0.2, 1);
    glm::vec3 r_arm2(-0.3, 0.1, 1);
    glm::vec3 r_arm3(-0.1, 0.1, 1);

    // draws right arm
    img.drawLine(r_arm0, r_arm1, color1);
    img.drawLine(r_arm1, r_arm2, color1);
    img.drawLine(r_arm2, r_arm3, color1);
    img.drawLine(r_arm3, r_arm0, color1);

    // right leg
    glm::vec3 r_leg0(-0.1, -0.2, 1);
    glm::vec3 r_leg1(-0.1, -0.5, 1);
    glm::vec3 r_leg2(0, -0.5, 1);
    glm::vec3 r_leg3(0, -0.2, 1);

    double angle = 5.5;

    glm::mat3x3 mRotate_right_leg {{cos(angle),sin(angle),0}, {-sin(angle),cos(angle),0}, {0,0,1}};

    r_leg0 = r_leg0*mRotate_right_leg;
    r_leg1 = r_leg1*mRotate_right_leg;
    r_leg2 = r_leg2*mRotate_right_leg;
    r_leg3 = r_leg3*mRotate_right_leg;

    // draws right leg
    img.drawLine(r_leg0, r_leg1, color1);
    img.drawLine(r_leg1, r_leg2, color1);
    img.drawLine(r_leg2, r_leg3, color1);
    img.drawLine(r_leg3, r_leg0, color1);

    // left leg
    glm::vec3 l_leg0(0.1, -0.2, 1);
    glm::vec3 l_leg1(0.1, -0.5, 1);
    glm::vec3 l_leg2(0, -0.5, 1);
    glm::vec3 l_leg3(0, -0.2, 1);

    glm::mat3x3 mRotate_left_leg {{cos(-angle),sin(-angle),0}, {-sin(-angle),cos(-angle),0}, {0,0,1}};

    l_leg0 = l_leg0*mRotate_left_leg;
    l_leg1 = l_leg1*mRotate_left_leg;
    l_leg2 = l_leg2*mRotate_left_leg;
    l_leg3 = l_leg3*mRotate_left_leg;

    // draws left leg
    img.drawLine(l_leg0, l_leg1, color1);
    img.drawLine(l_leg1, l_leg2, color1);
    img.drawLine(l_leg2, l_leg3, color1);
    img.drawLine(l_leg3, l_leg0, color1);

    // translation
    float tX = 0.2f; // OX translation
    float tY = 0.1f; // OY translation
    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix
    PRINT_MAT3(mTrans);

    img.save("robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();

}
