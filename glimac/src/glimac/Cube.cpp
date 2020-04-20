#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cube.hpp"
#include "glimac/Image.hpp"

static const GLfloat g_vertex_buffer_data[] = { //vec3 (pos 3D)  ,  vec2(PosTexture 2D), 
    // const int leftFace = ;
    -1.0f,-1.0f,-1.0f,  +1.0f,+1.0f,        // triangle 1 : begin
    -1.0f,-1.0f,+1.0f,  +0.0f,+1.0f,
    -1.0f,+1.0f,+1.0f,  +0.0f,+0.0f,        // triangle 1 : end
    -1.0f,-1.0f,-1.0f,  +1.0f,+1.0f,        // triangle 2 : begin
    -1.0f,+1.0f,+1.0f,  +0.0f,+0.0f,        
    -1.0f,+1.0f,-1.0f,  +1.0f,+0.0f,        // triangle 2 : end  

    // const int backFace = ;
    +1.0f,+1.0f,-1.0f,  +1.0f,+0.0f,        // triangle 3 : begin  
    -1.0f,-1.0f,-1.0f,  +0.0f,+1.0f,
    -1.0f,+1.0f,-1.0f,  +0.0f,+0.0f,        // triangle 3 : end   
    +1.0f,+1.0f,-1.0f,  +1.0f,+0.0f,        // triangle 4 : begin
    +1.0f,-1.0f,-1.0f,  +1.0f,+1.0f,        
    -1.0f,-1.0f,-1.0f,  +0.0f,+1.0f,        // triangle 4 : end 

     // const int rightFace = ;
    +1.0f,+1.0f,+1.0f,  +1.0f,+0.0f,        // triangle 9 : begin  
    +1.0f,-1.0f,-1.0f,  +0.0f,+1.0f,          
    +1.0f,+1.0f,-1.0f,  +0.0f,+0.0f,        // triangle 9 : end
    +1.0f,-1.0f,-1.0f,  +0.0f,+1.0f,        // triangle 10 : end
    +1.0f,+1.0f,+1.0f,  +1.0f,+0.0f,        
    +1.0f,-1.0f,+1.0f,  +1.0f,+1.0f,        // triangle 10 : end  

    // const int frontFace = ;
    -1.0f,+1.0f,+1.0f,  +1.0f,+0.0f,        // triangle 5 : begin  
    -1.0f,-1.0f,+1.0f,  +1.0f,+1.0f,        
    +1.0f,-1.0f,+1.0f,  +0.0f,+1.0f,        // triangle 5: end 
    +1.0f,+1.0f,+1.0f,  +0.0f,+0.0f,        // triangle 6: begin 
    -1.0f,+1.0f,+1.0f,  +1.0f,+0.0f,        
    +1.0f,-1.0f,+1.0f,  +0.0f,+1.0f,        /// triangle 6 : end  
    
    // const int downFace = ;
    +1.0f,-1.0f,+1.0f,  +1.0f,+0.0f,        // triangle 7 : begin  
    -1.0f,-1.0f,-1.0f,  +0.0f,+1.0f,        
    +1.0f,-1.0f,-1.0f,  +1.0f,+1.0f,        // triangle 7 : end
    +1.0f,-1.0f,+1.0f,  +1.0f,+0.0f,        // triangle 8 : begin
    -1.0f,-1.0f,+1.0f,  +0.0f,+0.0f,        
    -1.0f,-1.0f,-1.0f,  +0.0f,+1.0f,        /// triangle 8 : end  

    // const int upFace = ;
    +1.0f,+1.0f,+1.0f,  +1.0f,+0.0f,        // triangle 11 : end   rectangle  en haut  begin
    +1.0f,+1.0f,-1.0f,  +1.0f,+1.0f,        
    -1.0f,+1.0f,-1.0f,  +0.0f,+1.0f,        // triangle 11 : begin
    +1.0f,+1.0f,+1.0f,  +1.0f,+0.0f,        // triangle 12 : end
    -1.0f,+1.0f,-1.0f,  +0.0f,+1.0f,        
    -1.0f,+1.0f,+1.0f,  +0.0f,+0.0f        // triangle 12 : end   rectangle  en haut  end
};

namespace glimac {

    Cube::Cube(){
        GLsizei tablenght = sizeof(g_vertex_buffer_data) / sizeof(GLfloat);
        
        std::vector<ShapeVertex> data;
        
        // Construit l'ensemble des vertex
        for(GLsizei j = 0; j < tablenght; j+=5) {
            ShapeVertex vertex;
            vertex.position.x = g_vertex_buffer_data[j+0];
            vertex.position.y = g_vertex_buffer_data[j+1];
            vertex.position.z = g_vertex_buffer_data[j+2];
            
            vertex.texCoords.x = g_vertex_buffer_data[j+3];
            vertex.texCoords.y = g_vertex_buffer_data[j+4];

            vertex.normal.x = 1;
            vertex.normal.y = 0;
            vertex.normal.z = 0;
            
            m_Vertices.push_back(vertex);
        }

        m_nVertexCount = tablenght / 5;

        //     //Matrix initialization
        //     ModelMatrix = glm::mat4(1.0f);
        //     rotations = vec2(0,0);

        //     //Textures
        //     glGenTextures(1,&_texture);

        //     //Path related
        //     path = generatePath();
        //     initPaths();
        //  * 
        //  * 
        // ****/
        
        // GLuint idx = 0;
        // Construit les vertex finaux en regroupant les données en triangles:
        // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
        // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
        // avec i sur la bande correspondant à la longitude
        // for(GLsizei j = 0; j < discLong; ++j) {
        //     GLsizei offset = j * (discLat + 1);
        //     for(GLsizei i = 0; i < discLat; ++i) {
        //         m_Vertices.push_back(data[offset + i]);
        //         m_Vertices.push_back(data[offset + (i + 1)]);
        //         m_Vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
        //         m_Vertices.push_back(data[offset + i]);
        //         m_Vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
        //         m_Vertices.push_back(data[offset + i + discLat + 1]);
        //     }
        // }
        
        // Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
        // par un Index Buffer Object, que nous verrons dans les prochains TDs
    }

}
