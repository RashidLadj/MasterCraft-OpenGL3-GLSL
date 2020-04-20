#include "glimac/FreeflyCamera.hpp"

#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <iostream>

using namespace glimac;

void FreeflyCamera::computeDirectionVectors(){
	//std::cout << "Phi : " << m_fPhi << " Theta : " << m_fTheta << std::endl;

	//F⃗ =(cos(θ)sin(ϕ), sin(θ), cos(θ)cos(ϕ));
	m_FrontVector = glm::vec3( glm::cos(m_fTheta)*glm::sin(m_fPhi), glm::sin(m_fTheta), glm::cos(m_fTheta)*glm::cos(m_fPhi) );

	//L⃗ =(sin(ϕ+π/2), 0, cos(ϕ+π2))
	m_LeftVector = glm::vec3( glm::sin(m_fPhi + glm::pi<float>()/2), 0, glm::cos(m_fPhi + glm::pi<float>()/2) );

	//U⃗ =F⃗ × L⃗ 
	m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

// Constructeurs
FreeflyCamera::FreeflyCamera(){
	m_Position = glm::vec3(0, +0, 0);
	m_fPhi = glm::pi<float>();
	//m_fPhi = 270 * glm::pi<float>()/180;
	m_fTheta = 0.f;
	computeDirectionVectors();

}

FreeflyCamera::FreeflyCamera(glm::vec3 position = glm::vec3(0), float phi = glm::pi<float>(), float theta = 0.f){
	m_Position = position;
	m_fPhi = phi;
	m_fTheta = theta;
	computeDirectionVectors();

}

void FreeflyCamera::moveLeft(float t){
	//std::cout << m_Position << std::endl;
	m_Position += t*m_LeftVector;
	computeDirectionVectors();
}

void FreeflyCamera::moveFront(float t){
	//std::cout << m_Position << std::endl;
	m_Position += t*m_FrontVector;
	computeDirectionVectors();
}

void FreeflyCamera::rotateLeft(float degrees){
	m_fPhi += glm::radians(degrees);
	computeDirectionVectors();
}
void FreeflyCamera::rotateUp(float degrees){
	m_fTheta += glm::radians(degrees);
	computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const{
	glm::mat4 MVMatrix = glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
	return MVMatrix;
}

glm::mat4 FreeflyCamera::getViewMatrix(glm::mat4 matrix) const {
	glm::mat4 MVMatrix = glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
	return MVMatrix;
}

void FreeflyCamera::setEye(glm::vec3 _Pos){
	m_Position = _Pos;
}

glm::vec3 FreeflyCamera::getEye(){
	return m_Position;
}
