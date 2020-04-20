#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexture;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec4 vFragPositionVC;
out vec3 vFragColor;
out vec2 vFragTexture;
out vec4 vFragNormal;

// need it for Diffuse Light
// uniform mat4 uMVMatrix;
// out vec3 FragPos;  

void main() {
    // Passage en coordonnées homogènes
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);
    
    // Calcul des valeurs de sortie
    vFragPositionVC = uMVMatrix * vertexPosition;
    vFragColor = vec3(aVertexTexture,  1);   // just for testing
    vFragNormal = uNormalMatrix * vertexNormal;
    vFragTexture = aVertexTexture;

    // Calcul de la position projetée
    gl_Position = uMVPMatrix * vec4(aVertexPosition,  1);
}