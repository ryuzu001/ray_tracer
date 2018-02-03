#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
	// Hit h;
	vec3 u = ray.direction;
	// u = u.normalized();
	
	vec3 v = ray.endpoint - center;	// v = (e-c)
				
	float a = 1;									// u dot u
	float b = 2 * dot(u, v);								// 2 * u dot v
	float c = dot(v, v) - (radius * radius);	// v dot v - r^2
	
	double discr = b * b - 4 * a * c;
	
 	float t1 =  (-b - sqrt(discr)) / (2 * a);
	float t2 =  (-b + sqrt(discr)) / (2 * a);
	
	Hit hit1, hit2;
	hit1.object = this;
	hit2.object = this;
	
	// Case 1: det < 0 NO INTERSECTIONS --> Do nothing
	
	// Case 2: det = 0 ONE INTERSECTION --> barely graze sphere in one point (one hit)
	
	// Case 3: det > 0 TWO INTERSECTIONS --> Calculate t1 and t2
	
	if(discr > 0 ){
		
		/* CASE 3 */
		
		// 2 intersections: ray endpoint outside sphere
		
		// if(t1 > 0 || t2 > 0){
		// 	if(t1 < 0){ t1 = 0; }

		// 	h.object = this;
		// 	h.t = t1;
		// 	h.ray_exiting = false;
		// 	hits.push_back(h);
			
		// 	if(t2 < 0) { t2 = 0; }
			
		// 	h.object = this;
		// 	h.t = t2;
		// 	h.ray_exiting = true;
		// 	hits.push_back(h);
			
		// 	return true;
		// }

		if(t1 > 0){
			hit1.t = t1;
		}
		else{ hit1.t = 0; }
		
		hit1.ray_exiting = false;
		hits.push_back(hit1);

		hit2.t = t2;
		hit2.ray_exiting = true;
		hits.push_back(hit2);
		
		return true;

	}	
	else if(discr == 0){
		
		/* CASE 2  - one hit */
		
		hit1.t = t1;
		hit1.ray_exiting = true;
		hits.push_back(hit1);
		return true;
	}
    return false;

}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    normal = point - center;
    return normal.normalized();
}
