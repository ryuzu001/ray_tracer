#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    
    // vec3 v = ray.endpoint - center;
    // vec3 u = ray.direction;
    
    // float a = 1;
    // float b = 2 * dot(u, v);
    // float c = dot(v, v) - (radius * radius);
    
    // float determinant = 4 * (dot(u,v)) - 4 * (dot(v, v) - (radius * radius));
    
    // if(determinant == 0){
    //     return true;
    // }
    // if (determinant > 0){
    //     float t1 = ((-1 * b) - sqrt(determinant)) / (2 * a * c);
    //     float t2 = ((-1 * b) + sqrt(determinant)) / (2 * a * c);
    //     if(t1>0){
    //         Hit hit_t1;
    //         hit_t1.t=t1;
    //         Hit hit_t2;
    //         hit_t2.t=t2;
    //         hits.push_back(hit_t1);
    //         hits.push_back(hit_t2);
    //     }
    //     return true;
    // }
    
    // return false;
    
    
    
    
    Hit temp; 
   
	vec3 rayDirection =  ray.direction;
	rayDirection = rayDirection.normalized();
	
	vec3 CP_SP = ray.endpoint - this->center;
	float dotCPSP = dot(CP_SP, CP_SP);			
				
				
	float a = dot(rayDirection, rayDirection);
	
	float b = 2.00 * dot(rayDirection , CP_SP);
	float c = dotCPSP - (this->radius * this->radius);
	
	float determinant = b * b - 4 * a * c;
	
	if(sqrt(determinant) > 0 )
	{
		float tplus  =  (-b + sqrt(determinant)) / (2 * a);
		float tminus =  (-b - sqrt(determinant)) / (2 * a);
		if(tplus > 0 || tminus > 0)
		{
		   if(tminus < 0)
		   {
			   tminus = 0;
		   }
		   //first hit point
		   temp.object = this;
		   temp.t = tminus;
		   temp.ray_exiting = false;
		   hits.push_back(temp);
		   
		   
		   //second hit point
		   if(tplus < 0)
		   {
			   tplus = 0;
		   }
		   temp.object = this;
		   temp.t = tplus;
		   temp.ray_exiting = true;
		   hits.push_back(temp);
//std::cerr << tminus << ' ' << tplus << '\n';
		   return true; 
		}
		
	}		
     
   return false;
// }
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    return normal;
}
