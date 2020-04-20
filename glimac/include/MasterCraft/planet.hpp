// #pragma once
// #include <iostream>
// #include <glimac/common.hpp>
// #include <glimac/Sphere.hpp>
// #include <glimac/Program.hpp>
// #include <glimac/Image.hpp>
// #include <glm/glm.hpp>
// #include "shared.hpp"

// using namespace std;
// using namespace glimac;
// using namespace glm;

// class planet{
// // public:


// //   vec2 speed; //Around it self and arround rotation point
// //   vec2 rotations;
// //   vec3 _elipseCoefs;
// //   vec3 translation;
// //   //Ball related positions
// //   vec4 _ballCoords;
// //   //Galaxy related positions
// //   vec4 _pathCoords;

// //   //Path related path not working at end
// //   GLuint pvbo; 
// //   GLuint pvao;
// //   vector<vec3> path;
// //   vector<vec3> generatePath();
// //   void initPaths();
// //   void drawPaths();

//   public:
//     //Methods
//     planet(int Radius = 5,vec4 pathCoords = vec4(0,0,0,0),vec3 elipseCoefs = vec3(1,1,1), vec2 rotationSpeed = vec2(0,0));
//     planet::planet(int _Radius):Radius(_Radius);
//     ~planet(){
//       glDeleteBuffers(1,&vbo);
//       glDeleteVertexArrays(1,&vao);
//       glDeleteTextures(1,&texture);
//     };

//     /** assign Shader **/
//     void assignShader(Program &shader);

//     /** Load specific texture of one face of Block **/
//     void loadTexture(const std::string fullPathTexture);
    
//     //Position Coordinate in Space 3D
//     void setPosX(int _posX);
//     void setPosY(int _posY);
//     void setPosZ(int _posZ);

//     //void DrawBlock(const glm::mat4 &ProjMatrix);    //int all texture
//     void drawPlanet(const glm::mat4 &ProjMatrix, const glm::mat4 &CamView);
//     void update(float delta);
    


//   private:
//     // Functions
//     void initVBO();
//     void initVAO();

//     // Attributs
//     Sphere sun;
//     int Radius;    
//     //OpenGLrelated
//     GLuint vbo;
//     GLuint vao;
//     GLuint texture;
//     glm::mat4 ModelMatrix;

//     Program *shaderProg;
//     GLint uTime; // Not used
//     GLint uSampler; //Not used part of the app.cpp 

//     GLint uTexture;
//     Program *shaderProg;

//     GLint uMVMatrix;
//     GLint uMVPMatrix;
//     GLint uNormalMatrix ;



//     int posX = 0, posY = 0, posZ = 0;
// };
