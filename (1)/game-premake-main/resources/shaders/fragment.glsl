#version 430 core


float screenWidth = 800;
float screenHeight = 800;




/*
	I am following the convention that the forward direction is the positive z axis, positive y axis is up and positive x
	axis is right, therefore everything should follow this
*/

uniform vec3 camPos;

#define SPHERE_NUM 3
#define LINE_NUM 3
uniform vec4 SpherePositions[SPHERE_NUM];
uniform vec3 SphereColors[SPHERE_NUM];
uniform vec4 LinePositionsMapped[LINE_NUM];

layout(std430, binding = 1) buffer MySSBO
{
	vec3 data[];
} SSBOData;

struct Ray
{
	vec3 origin;
	vec3 dir; //ray direction
};


vec3 SphereRayIntersection(Ray ray, float sphereRadius, vec3 spherePosition, vec3 sphereColor, vec3 lightPos) 
{
    float t = dot(spherePosition-ray.origin, ray.dir);
    vec3 P = ray.origin + ray.dir*t;
    float y = length(spherePosition-P);

    if(y > sphereRadius)
    {
        return vec3(0.0, 0.0, 0.0);
    }

    float t1 = t - sqrt(sphereRadius*sphereRadius - y*y);
    vec3 hitPoint = ray.origin + ray.dir*t1;
    vec3 normal = normalize(hitPoint - spherePosition);
    vec3 reflectedvector = reflect(ray.dir, normal);
    return sphereColor * dot(normalize(lightPos-hitPoint), reflectedvector);
    
}


bool isPointCloseToLine(vec2 A, vec2 B, vec2 P)
{
    // Calculate the direction vector of the line segment AB
    vec2 AB = B - A;

    // Calculate the vector from A to P
    vec2 AP = P - A;

    // Project vector AP onto vector AB
    float t = dot(AP, AB) / dot(AB, AB);

    // Find the closest point on the line segment to P
    vec2 closestPoint = A + clamp(t, 0.0, 1.0) * AB;

    // Calculate the distance between P and the closest point on the line segment
    float distance = length(P - closestPoint);

    // Check if the distance is less than or equal to 0.05
    return distance <= 0.005;
}


void main()
{
	vec2 screenUV;
	screenUV.x = (gl_FragCoord.x/screenWidth)*2.0 - 1.0;
	screenUV.y = ((screenHeight-gl_FragCoord.y)/screenHeight)*2.0 - 1.0;

	vec3 camDir = vec3(0.0, 0.0, 1.0);
	float focalLength = 1.0f;

	Ray camRay = Ray(camPos, vec3(screenUV, focalLength));

	vec3 Color =  vec3(0.08, 0.08, 0.08);

	for(int i = 0; i<SPHERE_NUM; i++)
	{
		Color = SphereRayIntersection(camRay, SpherePositions[i].w, SpherePosition[i].xyz, SphereColors[i], vec3(5000.0, 5000.0, -20.0) );
	}

	for(int i = 0; i<LINE_NUM; i++)
	{
		if(isPointCloseToLine(LinePositionsMapped[i].xy, LinePositionsMapped[i].zw, screenUV))
		{
			Color = SphereColors[i];
		}
		else
		{
			continue;
		}
	}



    gl_FragColor = vec4(Color, 1.0);



}