#include "raylib.h"
#include "raymath.h"
#include "glad.h"
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include "GameObject.hpp"

#define focal_length 1.0
#define number_of_lines 3
#define number_of_spheres 2
#define G 6.6743 //ignoring the 10^-11 for now, i will factor it in at the end
#define gravitationalMultiplier 10.0f

/*
* NOTE: THE UNITS I AM USING: 1 UNIT OF DISTANCE IN THIS PROGRAM = 100 km, lets call this custom unit one IB_D for IB_distance
* 1 UNIT OF MASS IS DEPENDENT ON THE BOOL BIGMASS, IF MASS IS BIGMASS, THEN 1 UNIT = 10^20 kg
* 1 UNIT OF MASS IF MASS ISNT BIGMASS, THEN 1 UNIT = 1 KG
*/

/*
static bool threadExit = false;


void Simulation(double dt = 0.1)
{
    if(threadExit)
        return;

    SimulationTime = SimulationTime + dt;
    satellite.setPosition(Vector3((float)sin(SimulationTime) * 12.0f, 0.0f, -20.0f));
}
*/

// gravity for small object towards big object, assumption: big object is negligibly affected by gravity
Vector3 GravitationalForce (/*the big mass, example: a planet or a star*/const IB::SimulationObject BigThing,
    /*smol mass such as a satellite*/const IB::SimulationObject LittleThing)
{
    
    float distanceSquared = (BigThing.getPosition() - LittleThing.getPosition()) * (BigThing.getPosition() - LittleThing.getPosition());
    //here doing the dot product (the * sign) is OKAY since doing it for itself means that it will give distance squared,
    // but dont do it blindly, also, yes i am recomputing the subtracted vector, No I do not care

    float Magnitude = gravitationalMultiplier * 0.1f * BigThing.getMass() * LittleThing.getMass() * G / distanceSquared;
    //multiplying by 0.1 because 10^20 * 10^-11 * (10^5)^-2 = 10^(20-11-10) = 10^-1

    return Vector3Normalize(BigThing.getPosition() - LittleThing.getPosition()) * Magnitude;

    /*NOTE: I CAN DIRECTLY DO SOME VECTOR STUFF AND CAN AVOID USING DISTANCESQUARED ENTIRELY 
    *BUT I WANT TO KEEP THECODE UNDERSTANDABLE 
    */

}

int main()
{
    /*
    █▀▀█ █▀▀█ █▀▀ █▀▀▄ 　 ▀█░█▀ █▀▀ █▀▀█ ▀▀█▀▀ █▀▀ █░█ 　 █▀▀█ █▀▀▄ █▀▀▄ 　 █▀▀ █▀▀█ █▀▀█ █▀▀▀ █▀▄▀█ █▀▀ █▀▀▄ ▀▀█▀▀ 
    █░░█ █░░█ █▀▀ █░░█ 　 ░█▄█░ █▀▀ █▄▄▀ ░░█░░ █▀▀ ▄▀▄ 　 █▄▄█ █░░█ █░░█ 　 █▀▀ █▄▄▀ █▄▄█ █░▀█ █░▀░█ █▀▀ █░░█ ░░█░░ 
    ▀▀▀▀ █▀▀▀ ▀▀▀ ▀░░▀ 　 ░░▀░░ ▀▀▀ ▀░▀▀ ░░▀░░ ▀▀▀ ▀░▀ 　 ▀░░▀ ▀░░▀ ▀▀▀░ 　 ▀░░ ▀░▀▀ ▀░░▀ ▀▀▀▀ ▀░░░▀ ▀▀▀ ▀░░▀ ░░▀░░ 

    █▀▀ █░░█ █▀▀█ █▀▀▄ █▀▀ █▀▀█ 
    ▀▀█ █▀▀█ █▄▄█ █░░█ █▀▀ █▄▄▀ 
    ▀▀▀ ▀░░▀ ▀░░▀ ▀▀▀░ ▀▀▀ ▀░▀▀

    */
    std::ifstream vs("resources/shaders/vertex.glsl"); //vs = vertex shader

    std::string vertexShaderString;

    if (vs.is_open())
    {
        std::string content((std::istreambuf_iterator<char>(vs)), std::istreambuf_iterator<char>()); //i copied this from chatgpt idk wtf this means
        vs.close();
        std::cout << "vertex shader is:\n\n\n\n" << content << "\n\n\n\n";
        vertexShaderString = content;
    }
    else {
        std::cout << "Failed to open vertex shader file" << std::endl;
    }


    std::ifstream fs("resources/shaders/fragment.glsl"); //fs = fragment shader

    std::string fragmentShaderString;

    if (fs.is_open())
    {
        std::string content((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>()); //i copied this from chatgpt idk wtf this means
        fs.close();
        std::cout << "fragment shader is:\n\n\n\n" << content << "\n\n\n\n";
        fragmentShaderString = content;
    }
    else {
        std::cout << "Failed to open fragment shader file" << std::endl;
    }









    /*
    ░██╗░░░░░░░██╗██╗███╗░░██╗██████╗░░█████╗░░██╗░░░░░░░██╗  ░██████╗████████╗██╗░░░██╗███████╗███████╗
    ░██║░░██╗░░██║██║████╗░██║██╔══██╗██╔══██╗░██║░░██╗░░██║  ██╔════╝╚══██╔══╝██║░░░██║██╔════╝██╔════╝
    ░╚██╗████╗██╔╝██║██╔██╗██║██║░░██║██║░░██║░╚██╗████╗██╔╝  ╚█████╗░░░░██║░░░██║░░░██║█████╗░░█████╗░░
    ░░████╔═████║░██║██║╚████║██║░░██║██║░░██║░░████╔═████║░  ░╚═══██╗░░░██║░░░██║░░░██║██╔══╝░░██╔══╝░░
    ░░╚██╔╝░╚██╔╝░██║██║░╚███║██████╔╝╚█████╔╝░░╚██╔╝░╚██╔╝░  ██████╔╝░░░██║░░░╚██████╔╝██║░░░░░██║░░░░░
    ░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░░╚════╝░░░░╚═╝░░░╚═╝░░  ╚═════╝░░░░╚═╝░░░░╚═════╝░╚═╝░░░░░╚═╝░░░░░
    */
    float* screenWidth = new float(1000.0f);
    float* screenHeight = new float(1000.0f);
    //this function looks cursed... because it is, essentially typecasting a dereferenced float pointer
    InitWindow(((int)(*screenWidth)),((int)(*screenHeight)), "Raytracing");

    Shader shader = LoadShaderFromMemory(0, fragmentShaderString.c_str());







    /*
    
    ░█████╗░░█████╗░███╗░░░███╗███████╗██████╗░░█████╗░  ░██████╗████████╗██╗░░░██╗███████╗███████╗
    ██╔══██╗██╔══██╗████╗░████║██╔════╝██╔══██╗██╔══██╗  ██╔════╝╚══██╔══╝██║░░░██║██╔════╝██╔════╝
    ██║░░╚═╝███████║██╔████╔██║█████╗░░██████╔╝███████║  ╚█████╗░░░░██║░░░██║░░░██║█████╗░░█████╗░░
    ██║░░██╗██╔══██║██║╚██╔╝██║██╔══╝░░██╔══██╗██╔══██║  ░╚═══██╗░░░██║░░░██║░░░██║██╔══╝░░██╔══╝░░
    ╚█████╔╝██║░░██║██║░╚═╝░██║███████╗██║░░██║██║░░██║  ██████╔╝░░░██║░░░╚██████╔╝██║░░░░░██║░░░░░
    ░╚════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝  ╚═════╝░░░░╚═╝░░░░╚═════╝░╚═╝░░░░░╚═╝░░░░░
    */

    Vector3* camPos = new Vector3; //camera position
    camPos->x = 0.5f; camPos->y = 0.0f; camPos->z = 0.0f;




    /*
    ░██████╗░█████╗░███████╗███╗░░██╗███████╗
    ██╔════╝██╔══██╗██╔════╝████╗░██║██╔════╝
    ╚█████╗░██║░░╚═╝█████╗░░██╔██╗██║█████╗░░
    ░╚═══██╗██║░░██╗██╔══╝░░██║╚████║██╔══╝░░
    ██████╔╝╚█████╔╝███████╗██║░╚███║███████╗
    ╚═════╝░░╚════╝░╚══════╝╚═╝░░╚══╝╚══════╝
    */

    Texture2D Background = LoadTexture("resources/Textures/8k_stars_milky_way.png");
    Texture2D EarthTexture = LoadTexture("resources/Textures/2k_earth_daymap.png");
    

    Vector4 SpherePositions[number_of_spheres] = {      
        {0.0f, 0.0f, -140.0f, 63.7f},
        {0.0f, 11.0f, -140.0f, 5.0f},
    };  //will remove this list soon

    Vector3 SphereColors[number_of_spheres] = {
        {0.25f, 0.3f, 0.7f},
        {0.9f, 0.8f, 0.6f},
    };

    


    //NOTE: here the line positions are 3 dimensions but it will be mapped onto 4 dimensions, keeping z as focal length
    //first two coords are x1 and y1, second two are x2 and y2
    Vector3 LinePositions[number_of_lines*2] = {
        {30.0f, 4.0f, 12.0f},
        {30.0f, 8.0f, 12.0f},
        {30.0f, 13.0f, 12.0f},
        {30.0f, 19.0f, 12.0f},
        {30.0f, 18.0f, 12.0f},
        {30.0f, 9.0f, 12.0f}
    };

    //NOTE: here the line positions are 4 dimensional since first two coordinates are P1, second two are P2,
    //the lines lie in the plane (z = focal length) for easy calculations
    Vector4 LinePositionsMapped[number_of_lines];

    for(int i = 0; i < number_of_lines; i++)
    {
        Vector3 p1 = LinePositions[i*2];
        Vector3 p2 = LinePositions[i*2+1];
        LinePositionsMapped[i].x = p1.x*focal_length/p1.z;
        LinePositionsMapped[i].y = p1.y * focal_length / p1.z;
        LinePositionsMapped[i].z = p2.x * focal_length / p2.z;
        LinePositionsMapped[i].w = p2.y * focal_length / p2.z;
    }
    

    /*
    ░██████╗░░█████╗░███╗░░░███╗███████╗  ██╗░░░░░░█████╗░░█████╗░██████╗░
    ██╔════╝░██╔══██╗████╗░████║██╔════╝  ██║░░░░░██╔══██╗██╔══██╗██╔══██╗
    ██║░░██╗░███████║██╔████╔██║█████╗░░  ██║░░░░░██║░░██║██║░░██║██████╔╝
    ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░  ██║░░░░░██║░░██║██║░░██║██╔═══╝░
    ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗  ███████╗╚█████╔╝╚█████╔╝██║░░░░░
    ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝  ╚══════╝░╚════╝░░╚════╝░╚═╝░░░░░
    */
    
    //std::jthread PhysicsThread(Simulation, 0.0001);
    IB::SimulationObject satellite(5.0, false , Vector3(-200.0f, -90.0f, -300.0f), Vector3(0.0f, 50.0f, 0.0f));
    IB::SimulationObject Earth(59721.9, true ,Vector3(-60.0f, 0.0f, -300.0f), Vector3(9.0f, 0.0f, 0.0f));
    double SimulationTime = 0.0;
    bool PauseSimulation = true;

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        if (IsKeyPressed(KEY_D))
            camPos->x -= 1.0f;
        else if (IsKeyPressed(KEY_A))
            camPos->x += 1.0f;
        else if (IsKeyPressed(KEY_P))
            PauseSimulation = !PauseSimulation; //toggling

        if(!PauseSimulation)
        {
            SimulationTime = SimulationTime + deltaTime;
            satellite.applyForceSmallMass(GravitationalForce(Earth, satellite), deltaTime);
            Earth.applyForceBigMass(Vector3(0.0f, 0.0f, 0.0f), deltaTime); //no actual force is being applied
            // but just to make the velocity acutally take effect


            SpherePositions[0].x = Earth.getPosition().x;
            SpherePositions[0].y = Earth.getPosition().y;
            SpherePositions[0].z = Earth.getPosition().z;

            SpherePositions[1].x = satellite.getPosition().x;
            SpherePositions[1].y = satellite.getPosition().y;
            SpherePositions[1].z = satellite.getPosition().z;

            

            LinePositions[0] = satellite.getPosition();
            LinePositions[1] = satellite.getPosition() + satellite.getVelocity();
        }

        for (int i = 0; i < number_of_lines; i++)
        {
            Vector3 p1 = LinePositions[i * 2];
            Vector3 p2 = LinePositions[i * 2 + 1];
            LinePositionsMapped[i].x = p1.x * focal_length / p1.z;
            LinePositionsMapped[i].y = p1.y * focal_length / p1.z;
            LinePositionsMapped[i].z = p2.x * focal_length / p2.z;
            LinePositionsMapped[i].w = p2.y * focal_length / p2.z;
        }
        

        /*
        ██████╗░███████╗███╗░░██╗██████╗░███████╗██████╗░██╗███╗░░██╗░██████╗░
        ██╔══██╗██╔════╝████╗░██║██╔══██╗██╔════╝██╔══██╗██║████╗░██║██╔════╝░  
        ██████╔╝█████╗░░██╔██╗██║██║░░██║█████╗░░██████╔╝██║██╔██╗██║██║░░██╗░
        ██╔══██╗██╔══╝░░██║╚████║██║░░██║██╔══╝░░██╔══██╗██║██║╚████║██║░░╚██╗
        ██║░░██║███████╗██║░╚███║██████╔╝███████╗██║░░██║██║██║░╚███║╚██████╔╝
        ╚═╝░░╚═╝╚══════╝╚═╝░░╚══╝╚═════╝░╚══════╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░╚═════╝░
        */
        BeginDrawing();
            BeginShaderMode(shader);
                DrawRectangle(0, 0, *screenWidth, *screenHeight, ORANGE);
                    SetShaderValueTexture(shader, GetShaderLocation(shader, "BackgroundTexture"), Background);
                    SetShaderValueTexture(shader, GetShaderLocation(shader, "EarthTexture"), EarthTexture);
                    SetShaderValue(shader, GetShaderLocation(shader, "screenHeight"), screenHeight, SHADER_UNIFORM_FLOAT);
                    SetShaderValue(shader, GetShaderLocation(shader, "screenWidth"), camPos, SHADER_UNIFORM_VEC3);
                    SetShaderValue(shader, GetShaderLocation(shader, "camPos"), camPos, SHADER_UNIFORM_VEC3);
                    // Set the 3D vector array as a uniform in the shader
                    SetShaderValueV(shader, GetShaderLocation(shader, "LinePositionsMapped"), &LinePositionsMapped[0], SHADER_UNIFORM_VEC4, sizeof(LinePositionsMapped) / sizeof(Vector4));
                    SetShaderValueV(shader, GetShaderLocation(shader, "SpherePositions"), &SpherePositions[0], SHADER_UNIFORM_VEC4, sizeof(SpherePositions) / sizeof(Vector4));
                    SetShaderValueV(shader, GetShaderLocation(shader, "SphereColors"), &SphereColors[0], SHADER_UNIFORM_VEC3, sizeof(SphereColors) / sizeof(Vector3));
                    
            EndShaderMode();
            DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 30, DARKPURPLE);

            if (PauseSimulation) {
                DrawText("Simulation Paused", 650, 0, 30, RED);
            }

            DrawText(TextFormat("speed of satellite: %f", Vector3Length(satellite.getVelocity())), 0, 60, 30, GREEN);
            DrawText(TextFormat("distance from planet: %f", Vector3Distance( satellite.getPosition(), Earth.getPosition())), 0, 90, 30, ORANGE);
        EndDrawing();
    }

    /*
        ░█████╗░██╗░░░░░███████╗░█████╗░███╗░░██╗██╗███╗░░██╗░██████╗░
        ██╔══██╗██║░░░░░██╔════╝██╔══██╗████╗░██║██║████╗░██║██╔════╝░
        ██║░░╚═╝██║░░░░░█████╗░░███████║██╔██╗██║██║██╔██╗██║██║░░██╗░
        ██║░░██╗██║░░░░░██╔══╝░░██╔══██║██║╚████║██║██║╚████║██║░░╚██╗
        ╚█████╔╝███████╗███████╗██║░░██║██║░╚███║██║██║░╚███║╚██████╔╝
        ░╚════╝░╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚══╝╚═╝╚═╝░░╚══╝░╚═════╝░
    */
    //threadExit = true;  //VERY IMPORTANT TO EXIT PHYSICS SIM
    delete camPos;
    delete screenHeight;
    delete screenWidth;
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
    UnloadTexture(EarthTexture);
    UnloadTexture(Background);
    UnloadShader(shader);

}
