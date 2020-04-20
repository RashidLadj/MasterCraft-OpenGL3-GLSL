#ifndef MASTERCRAFT_APPLICATION
#define MASTERCRAFT_APPLICATION

#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

#include "MasterCraft/BlockMineCraft.hpp"
#include "glimac/FilePath.hpp"
#include "MasterCraft/masterCraft.hpp"

#include "MasterCraft/planet.hpp"



#include "glimac/FreeflyCamera.hpp"

using namespace glimac;
using namespace std;
using namespace glm;
using namespace mapCraft;

extern FilePath *applicationPath;


class Application{
  public:
    Application(SDLWindowManager &_window);
    ~Application() {
      delete window;
    };
    bool init(); //Init the world and opengl related functionalities
    void handleEvent(SDL_Event e, bool &boolean);
    void update(float delta); //Update the physics
    void draw(); //Draw the world
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

  private:
    SDLWindowManager *window;

    game::BlockMineCraft SkyBox;

    //Shaders generic
    Program m_Program;

    GLint uTexture; //??
    GLint uColor;
    FreeflyCamera cam;

    // GLint uLightDir;
    // GLint uSpecular,uAmbient,uRotationUV;

    mat4 ProjMatrix;
    mat4 MV;
    mat4 Normal;

    bool leftClickIsPressed = false;
    float Angle = 0;
    float pas = 1.f;
    int x = 0;
    int y = 0;

    bool q = false;
    bool d = false;
    bool z = false;
    bool s = false;
    bool spaceBar = false;

   // mapSimplex testSimplex;

    game::masterCraft masterGame;
    glm::vec3 posCamera;
    glm::vec3 oldChunk;

    // Modifiable avec la touche E
    bool drawAllMap = false;

};

#endif