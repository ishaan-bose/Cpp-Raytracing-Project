#include "raylib.h"
#include "raymath.h"
#include "glad.h"
#include <string>
#include <iostream>
#include <fstream>

#define focal_length 1.0
#define number_of_lines 3
#define number_of_spheres 3

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
    float* screenWidth = new float(800.0f);
    float* screenHeight = new float(800.0f);
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
    camPos->x = 0.0f; camPos->y = 0.0f; camPos->z = 0.0f;


    /*
    ░██████╗░█████╗░███████╗███╗░░██╗███████╗
    ██╔════╝██╔══██╗██╔════╝████╗░██║██╔════╝
    ╚█████╗░██║░░╚═╝█████╗░░██╔██╗██║█████╗░░
    ░╚═══██╗██║░░██╗██╔══╝░░██║╚████║██╔══╝░░
    ██████╔╝╚█████╔╝███████╗██║░╚███║███████╗
    ╚═════╝░░╚════╝░╚══════╝╚═╝░░╚══╝╚══════╝
    */

    

    Vector4 SpherePositions[number_of_spheres] = {      
        {8.0f, 250.0f, -562.0f, 100.0f},
        {-10.5f, -5.0f, -20.0f, 0.3f},
        {0.0f, 0.0f, -20.0f, 9.0f}
    };  //will remove this list soon

    Vector3 SphereColors[number_of_spheres] = {
        {0.3f, 0.3f, 0.3f},
        {0.9f, 0.9f, 0.9f},
        {0.1f, 0.65f, 0.1f}
    };

    //I COPIED THIS FROM CHATGPT, BEWARE FUTURE ME, NIKA, MARIN

    /*
    GLuint ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Vector3)*number_of_spheres, &SpherePositions[0], GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo); // 1 is the binding point (binding = 1 in the shader)
    */

    /*
    * 
    █▀▀ ░▀░ █▀▀▀ █░░█ █▀▀█ █▀▀ 　 █▀▀█ █░░█ ▀▀█▀▀ 　 █░░░█ █░░█ █░░█ 　 █▀▀ █▀▀ █▀▀▄ █▀▀█ 　 █▀▀▄ █▀▀█ ▀▀█▀▀ 
    █▀▀ ▀█▀ █░▀█ █░░█ █▄▄▀ █▀▀ 　 █░░█ █░░█ ░░█░░ 　 █▄█▄█ █▀▀█ █▄▄█ 　 ▀▀█ ▀▀█ █▀▀▄ █░░█ 　 █░░█ █░░█ ░░█░░ 
    ▀░░ ▀▀▀ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ 　 ▀▀▀▀ ░▀▀▀ ░░▀░░ 　 ░▀░▀░ ▀░░▀ ▄▄▄█ 　 ▀▀▀ ▀▀▀ ▀▀▀░ ▀▀▀▀ 　 ▀░░▀ ▀▀▀▀ ░░▀░░ 
    
    █░░░█ █▀▀█ █▀▀█ █░█ ░▀░ █▀▀▄ █▀▀▀ 
    █▄█▄█ █░░█ █▄▄▀ █▀▄ ▀█▀ █░░█ █░▀█ 
    ░▀░▀░ ▀▀▀▀ ▀░▀▀ ▀░▀ ▀▀▀ ▀░░▀ ▀▀▀▀
    */
    


    //NOTE: here the line positions are 3 dimensions but it will be mapped onto 4 dimensions, keeping z as focal length
    //first two coords are x1 and y1, second two are x2 and y2
    Vector3 LinePositions[number_of_lines*2] = {
        {30.0f, 4.0f, 12.0f},
        {30.0f, 8.0f, 12.0f},
        {30.0f, 12.0f},
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
        LinePositionsMapped[i].w = p2.x * focal_length / p2.z;
    }
    

    while (!WindowShouldClose())
    {
        //tick += 0.001f;
        //*gradientValue = sinf(tick);


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
                    SetShaderValue(shader, GetShaderLocation(shader, "screenHeight"), screenHeight, SHADER_UNIFORM_FLOAT);
                    SetShaderValue(shader, GetShaderLocation(shader, "screenWidth"), camPos, SHADER_UNIFORM_VEC3);
                    SetShaderValue(shader, GetShaderLocation(shader, "camPos"), camPos, SHADER_UNIFORM_VEC3);
                    // Set the 3D vector array as a uniform in the shader
                    SetShaderValueV(shader, GetShaderLocation(shader, "LinePositionsMapped"), &LinePositionsMapped[0], SHADER_UNIFORM_VEC4, sizeof(LinePositionsMapped) / sizeof(Vector4));
                    SetShaderValueV(shader, GetShaderLocation(shader, "SpherePositions"), &SpherePositions[0], SHADER_UNIFORM_VEC4, sizeof(SpherePositions) / sizeof(Vector4));
                    SetShaderValueV(shader, GetShaderLocation(shader, "SphereColors"), &SphereColors[0], SHADER_UNIFORM_VEC3, sizeof(SpherePositions) / sizeof(Vector3));
            EndShaderMode();
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

    delete camPos;
    delete screenHeight;
    delete screenWidth;
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);

}
