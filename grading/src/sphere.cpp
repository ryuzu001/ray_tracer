#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
	vec3 u =  ray.direction;
	u = u.normalized();
	
	vec3 v = ray.endpoint - this->center;	// v = (e-c)
				
	float a = dot(u, u);									// u dot u
	float b = 2.00 * dot(u, v);								// 2 * u dot v
	float c = dot(v, v) - (this->radius * this->radius);	// v dot v - r^2
	
	float determinant = b * b - 4 * a * c;
	
	// Case 1: det < 0 NO INTERSECTIONS --> Do nothing
	
	// Case 2: det = 0 ONE INTERSECTION --> Do nothing
	
	// Case 3: det > 0 TWO INTERSECTIONS --> Calculate t1 and t2
	
	if(determinant > 0 ){
		float t1 =  (-b - sqrt(determinant)) / (2 * a);
		float t2 =  (-b + sqrt(determinant)) / (2 * a);
		
		// 2 intersections: ray endpoint outside sphere
		if(t1 > 0){
			Hit hit1;
			
			hit1.object = this;
			hit1.t = t1;
			hits.push_back(hit1);
		}
		
		Hit hit2;
		
		hit2.object = this;
		hit2.t = t2;
		hits.push_back(hit2);
		return true; 
		
	}		
   return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    return normal;
}
