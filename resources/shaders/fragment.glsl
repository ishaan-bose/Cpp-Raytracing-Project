#version 430 core


float screenWidth = 1000.0;
float screenHeight = 1000.0;




/*
	I am following the convention that the forward direction is the positive z axis, positive y axis is up and positive x
	axis is right, therefore everything should follow this
*/

uniform vec3 camPos;

#define SPHERE_NUM 2
#define LINE_NUM 3
#define AMBIENCE 0.9
#define PI 3.14159
#define TWOPI 6.2832


uniform vec4 SpherePositions[SPHERE_NUM];
uniform vec3 SphereColors[SPHERE_NUM];
uniform vec4 LinePositionsMapped[LINE_NUM];

uniform sampler2D BackgroundTexture;
uniform sampler2D EarthTexture;



struct Ray
{
	vec3 origin;
	vec3 dir; //ray direction
};

struct hitInfo
{
	vec3 normal;
	vec3 hitPoint;
	float t;
	bool noHit;
};

vec3 sampleSkybox(vec3 dir) {
	float skyboxCeiling = 10.0; //dont ask me it was in the source code of NamePointer's Video
	return min(vec3(skyboxCeiling), pow(texture(BackgroundTexture, 2 * vec2(0.5 + atan(dir.x, dir.z)/(2*PI), 0.5 + asin(-dir.y)/PI)).xyz, vec3(1.0/2.2)));
	//i copied this from his video
}


hitInfo SphereRayIntersection(Ray ray, float sphereRadius, vec3 spherePosition) 
{
    float t = dot(spherePosition-ray.origin, ray.dir);
    vec3 P = ray.origin + ray.dir*t;
    float y = length(spherePosition-P);

    if(y > sphereRadius)
    {
        return hitInfo(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), -1.0, true);
    }

    float t1 = t - sqrt(sphereRadius*sphereRadius - y*y);
    vec3 hitPoint = ray.origin + ray.dir*t1;
    vec3 normal = normalize(hitPoint - spherePosition);

	hitInfo h;
	h.normal = normal;
	h.hitPoint = hitPoint;
	h.t = t1;
	h.noHit = false;
	return h;
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

	vec3 rayDir =  normalize(vec3(screenUV, focalLength));

	Ray camRay = Ray(camPos,rayDir );



	
	vec3 Color = sampleSkybox(camRay.dir);






	float OldT = 10000000.0;

	for(int i = 0; i<SPHERE_NUM; i++)
	{
		hitInfo h = SphereRayIntersection(camRay, SpherePositions[i].w, SpherePositions[i].xyz);
		
		if(!h.noHit && abs(h.t) < abs(OldT))
		{
			vec3 color;
			if(i == 0)
			{
				vec3 d = normalize(SpherePositions[i].xyz - h.hitPoint);
				color += (texture(EarthTexture, vec2(0.5 + atan(d.z, d.x)/TWOPI, 0.5 + asin(d.y)/TWOPI))).xyz;
				color *= dot(normalize(h.hitPoint - vec3(500.0, 0.0, -20.0) ) , h.normal); //raytraced part
			}
			else
			{
				color = SphereColors[i] * dot(normalize(h.hitPoint - vec3(500.0, 0.0, -20.0) ) , h.normal); //raytraced part
			}
			
			color += AMBIENCE * 1.0/(1+pow((length(color)-2.0),2)) * SphereColors[i]; //taking the inverse of the length of a color
			//ik its cursed to take length of a color, but i am reducing ambient light the more the normal light is there

			//plot y = 1/(1+(x+0.5)^2) in a graphing calculator, y is ambient adjustion (dw future me its a term i only made up),
			//x is the brightness before adjustion

			
			
				
			

			Color = color; //mind the capitalization
			OldT = h.t;
		}
	}

	for(int i = 0; i<LINE_NUM; i++)
	{
		if(isPointCloseToLine(LinePositionsMapped[i].xy, LinePositionsMapped[i].zw, screenUV))
		{
			Color = vec3(0.6, 0.8, 0.3);
		}
		else
		{
			continue;
		}
	}

    gl_FragColor = vec4(Color, 1.0);

}