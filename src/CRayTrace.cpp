//
//  CRayTrace.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"


/// \fn compPrimaryRayMatrix(CCamera cam, glm::mat3& m)
/// \brief Computation of the projection matrix.
/// \param cam Camera parameters.
/// \param m Output projection matrix.
///
bool CRayTrace::compPrimaryRayMatrix(const CCamera& cam, glm::mat3& m) {
    glm::vec3 u,v,o;
    glm::vec3 look = cam.lookp - cam.eyep;

    u = (glm::cross(cam.up, look))/(glm::length(glm::cross(cam.up, look)));
    v = (glm::cross(u, look))/(glm::length(glm::cross(u, look)));

    glm::vec3 u1,v1;
    for (int i = 0; i < 3; i++) {
        u1[i] = u[i] * double(cam.width)/2.0;
        v1[i] = v[i] * double(cam.height)/2.0;
    }
    o = (look/glm::length(look)) * ((cam.width)/(2*tan((3.14f / 180.0f * cam.fov/2)))) - (u1 + v1);

    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            switch(i)
            {
                case 0:
                    m[i][j] = u[j];
                    break;
                case 1:
                    m[i][j] = v[j];
                    break;
                case 2:
                    m[i][j] = o[j];
                    break;
                default:
                    break;
            }
        }
    }
    return true;
}


/// \fn rayTrace(CScene scene, CRay& ray, COutput& out)
/// \brief Traces single ray.
/// \param scene Object with all scene components including a camera.
/// \param ray Ray parameter (primary and secondary rays).
/// \param out Object with output color and parameters used in recursion.
///
bool CRayTrace::rayTrace(const CScene& scene, CRay& ray, COutput& res) {
    CObject* obj;
    float tmin = 99999.0f;
    float EPS = 0.0001f;
    bool is_intersection = false;
    for (auto i : scene.objectList) {
        float t = i->intersect(ray);
        if (t > EPS && t < tmin) {
            tmin = t;
            is_intersection = true;
        }
    }
    if (is_intersection) {
        res.col = {0,0.5,0};
    }
    else {
        res.col = {0,0,0};
    }
    /// looks for the closest object along the ray path
    /// returns false if there are no intersection

    /// computes 3D position of the intersection point

    /// computes normal vector at intersection point

    /// for each light source defined in the scene

        /// computes if the intersection point is in the shadows

        /// computes diffuse color component

        /// computes specular color component

    /// adds texture for textured spheres

    /// computes ambient color component

    /// if the surface is reflective

        /// if out.tree >= MAX_RAY_TREE return from function

        /// computes the secondary ray parameters (reflected ray)

        /// recursion
        //   rayTrace(scene, secondary_ray, out);


    return true;
}


/// \fn reflectedRay(CRay ray, glm::vec3 n, glm::vec3 pos)
/// \brief Computes parameters of the ray reflected at the surface point with given normal vector.
/// \param ray Input ray.
/// \param n Surface normal vector.
/// \param pos Position of reflection point.
/// \return Reflected ray.
///
CRay CRayTrace::reflectedRay(const CRay& ray, const glm::vec3& n, const glm::vec3& pos) {
    CRay reflected_ray;
    
    return reflected_ray;
}

