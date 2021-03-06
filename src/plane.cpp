#include "plane.h"
#include "ray.h"
#include <cfloat>

#include<iostream>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // compute t
    float t = (dot(normal, (x1 - ray.endpoint))) / dot(normal, ray.direction);

    if(t > 0){
        // hit
        Hit temp;
        temp.object = this;
        temp.t = t;
        hits.push_back(temp);
        return true;
    }
    return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
