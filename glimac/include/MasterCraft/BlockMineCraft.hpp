#ifndef MASTERCRAFT_BLOCMASTERCRAFT
#define MASTERCRAFT_BLOCMASTERCRAFT

#include <iostream>
#include <glimac/common.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glm/glm.hpp>

#include "MasterCraft/DefaultValue.hpp"

#include <string>

using namespace std;
using namespace glimac;
using namespace glm;

namespace game{

const GLuint VERTEX_ATTR_POSITION = 0;    // 0 représente l'attribut position 
const GLuint VERTEX_ATTR_NORMAL = 1;    // 1 représente la Normale
const GLuint VERTEX_ATTR_TEXTURE = 2;    // 2 représente l'attribut Texture


const int faceNumber = 6;               //Nombre de face d'un cube

    class BlockMineCraft{
        public:
            //Methods
            BlockMineCraft();
            ~BlockMineCraft(){};

            void assignShader(Program &shader);

            //void updateColor(glm::vec3 color);

            //void updateColorFace(int face, glm::vec3 color);

            /** Load all textures of Block **/
            void loadTexture(const std::string pathFile, const std::string nameFile);
            
            /** Load specific texture of one face of Block **/
            void loadTexture(const std::string pathFile, const std::string nameFile, const int face);

            //Position Coordinate in Space 3D
            void setPosX(int _posX);
            void setPosY(int _posY);
            void setPosZ(int _posZ);
    

            //void DrawBlock(const glm::mat4 &ProjMatrix);    //int all texture
            void DrawBlock(const glm::mat4 &ProjMatrix, const glm::mat4 &CamView, const int BlockOrSkyBox);

        private:
            // Functions
            void initVBO();
            void initVAO();

            // Attributs
            Cube cube;    
            GLuint vbo;
            GLuint vao;
            Program *shaderProg;

            GLint uMVMatrix;
            GLint uMVPMatrix;
            GLint uNormalMatrix ;

            GLint uTexture;
            GLuint texture[6];

            int posX = 0, posY = 0, posZ = 0;
    };
}

#endif