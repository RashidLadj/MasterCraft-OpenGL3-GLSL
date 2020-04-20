#version 330 core

in vec4 vFragPositionVC;
in vec3 vFragColor;
in vec2 vFragTexture;
in vec4 vFragNormal;

out vec3 fFragTexture;

uniform sampler2D uTexture;

void main() {
    vec4 texColor = texture(uTexture, vFragTexture);
    fFragTexture = texColor.xyz; 
    
    //fFragTexture = vFragColor;

}
