#version 330 core

in vec4 vFragPositionVC;
in vec3 vFragColor;
in vec2 vFragTexture;
in vec4 vFragNormal;

out vec3 fFragTexture;

uniform sampler2D uTexture;

//uniform vec3 fPositionSun;
//uniform vec3 fPositionCamera;


void main() {
    vec4 texColor = texture(uTexture, vFragTexture);

    /** Ambient Lighting **/
    float ambientStrength = 0.1;
    vec3 lightColor = vec3(1, 1, 1);
    vec3 ambient = ambientStrength * lightColor;

    /** Diffuse Lighting **/
    vec3 norm = normalize(vFragNormal.xyz);
    vec3 lightDir = normalize( vec3(1,1,1) - vFragPositionVC.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    /** Specular Lighting **/
    float specularStrength = 0.5;
    vec3 viewDir = normalize(vec3(0,100,0) - vFragPositionVC.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 2);
    vec3 specular = specularStrength * spec * lightColor;

    fFragTexture = (ambient+diffuse+specular) * texColor.xyz; 
    
    //fFragTexture = vFragColor;

}
