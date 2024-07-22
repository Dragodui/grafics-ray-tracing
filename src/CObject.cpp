//
//  CObject.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"
#include "CObject.hpp"
#include "math.h"
#include <iostream>


/// \fn intersect(CRay ray)
/// \brief Computes intersection between ray and sphere.
/// \param ray Ray parameters.
/// \return Distance from camera position to the closest intersection point, or negative value.
///
float CSphere::intersect(const CRay& ray) {
    glm::vec3 v = ray.pos - pos;
    float A = glm::dot(ray.dir,ray.dir);
    float B = 2.0f*glm::dot(v,ray.dir);
    float C = glm::dot(v,v)-r*r;

    float delta = B*B - 4.0f*A*C;
    if (delta > 0) {
        float t1 = (-B + sqrt(delta))/(2.0f*A);
        float t2 = (-B - sqrt(delta))/(2.0f*A);
        return std::min(t1,t2);
    }
    else if (delta == 0) {
        return -B/(2.0f*A);
    }

    return -1;
}


/// Normal vector to the sphere surface
/// \fn normal(glm::vec3 hit_pos)
/// \brief Surface normal vector at the intersection point.
/// \param hit_pos Intersection point.
/// \return Normal vector parameters.
///
glm::vec3 CSphere::normal(const glm::vec3& hit_pos) {
    glm::vec3 n;
    n = glm::normalize(hit_pos-pos);
    
    return n;
}

/// Computes texture mapping coordinates (u,v).
/// \param normal_vec Normalized normal vector at intersection point.
/// \return (u,v) texture coordinates in <0,1> range.
glm::vec2 CSphere::textureMapping(const glm::vec3& normal_vec) {
    glm::vec2 uv = {0,0};
    float theta = std::atan2(normal_vec.z, normal_vec.x);
    float phi = std::acos(normal_vec.y);
    uv.x = theta / (2.0f * M_PI) + 0.5f;
    uv.y = phi / M_PI;
    return uv;
}



/// \fn intersect(CRay ray)
/// \brief Computes intersection between triangle and sphere.
/// \param ray Ray parameters.
/// \return Distance from camera position to the closest intersection point, or negative value.
///
float CTriangle::intersect(const CRay& ray) {
    float t = -1;

    glm::vec3 baryPosition = {};
    glm::vec3 planeNormal = CTriangle::normal(v0);

    if(glm::intersectRayTriangle(ray.pos, ray.dir, v0, v1, v2, baryPosition)){
        glm::intersectRayPlane(ray.pos, ray.dir, v0, planeNormal, t);
    }



    return t;
}

glm::vec3 CTriangle::normal(const glm::vec3& hit_pos) {
    glm::vec3 n;

    glm::vec3 u = v1 - v0;
    glm::vec3 v = v2 - v0;

    n = glm::normalize(glm::cross(u,v));

    return n;
}



