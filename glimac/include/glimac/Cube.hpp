#pragma once

#include <vector>

#include "common.hpp"
#include <GL/glew.h>
#include "glm.hpp"
#include "Program.hpp"

using namespace std;

namespace glimac {
    class Cube {
        public:
            // Constructeur: alloue le tableau de données et construit les attributs des vertex
            
            Cube();
            
            //Renvoit le pointeur vers les données
            const ShapeVertex* getDataPointer() const {
                return &m_Vertices[0];
            }

            std::vector<ShapeVertex> getData()  {
                return m_Vertices;
            }
            
            // Renvoit le nombre de vertex
            GLsizei getVertexCount() const {
                return m_nVertexCount;
            }
            GLsizei m_CubeEdgeSize = 2; // EdgeSize of Cube
            
        private:
            std::vector<ShapeVertex> m_Vertices;
            GLsizei m_nVertexCount; // Nombre de sommets
            
    };
}