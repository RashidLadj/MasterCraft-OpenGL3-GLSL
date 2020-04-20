// #include "MasterCraft/planet.hpp"

// // planet::planet(vec4 ballCoords,vec4 pathCoords ,vec3 elipseCoefs, vec2 rotationSpeed) :
// // _ballCoords(ballCoords),_pathCoords(pathCoords),speed(rotationSpeed) , _elipseCoefs(elipseCoefs) {
// //   //Sphere creation
// //   _ball = new Sphere(_ballCoords.w,16,16);

// //   initVBO();
// //   initVAO();

// //   //Matrix initialization
// //   ModelMatrix = glm::mat4(1.0f);
// //   rotations = vec2(0,0);

// //   //Textures
// //   glGenTextures(1,&_texture);

// //   //Path related
// //   path = generatePath();
// //   initPaths();
// // }

// planet::planet(int _Radius):Radius(_Radius){
//   sun = Sphere(Radius, 16, 16);
//   //Creation du VBO
//   initVBO();
//   //Creation du VAO
//   initVAO();
// };

// void planet::initVBO(){
//     glGenBuffers(1, &vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     // Données récupérées de la class Cube ( voir fichier cpp + hpp)
//     glBufferData(GL_ARRAY_BUFFER, sun.getVertexCount() * sizeof(ShapeVertex), sun.getDataPointer(), GL_STATIC_DRAW);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
// };

// void planet::initVAO(){
//     glGenVertexArrays(1, &vao);
//     glBindVertexArray(vao);
//     glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
//     glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
//     glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//         GLsizei stride = sizeof(ShapeVertex);  // le nombre d'octets séparant l'attribut pour deux sommets consécutifs.
//     glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, stride , (const GLvoid*)offsetof(ShapeVertex, position));
//     glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, stride , (const GLvoid*)offsetof(ShapeVertex, normal));
//     glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, stride , (const GLvoid*)offsetof(ShapeVertex, texCoords));
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);  
//     glEnable(GL_DEPTH_TEST);
// };

// void planet::setPosX(int _posX){
//     posX = _posX;
// };

// void planet::setPosY(int _posY){
//     posY = _posY;   
// };

// void planet::setPosZ(int _posZ){
//     posZ = _posZ;
// };

// void planet::assignShader(Program &shader){
//     shaderProg = &shader;
//     shader.use();
//     GLint pgm;
//     glGetIntegerv( GL_CURRENT_PROGRAM, &pgm);
//     uMVMatrix = glGetUniformLocation(shaderProg->getGLId(), "uMVMatrix");
//     uMVPMatrix = glGetUniformLocation(shaderProg->getGLId(), "uMVPMatrix");
//     uNormalMatrix = glGetUniformLocation(shaderProg->getGLId(), "uNormalMatrix");
//     uTexture = glGetUniformLocation(shaderProg->getGLId(), "uTexture");
//     std::cout << "   --> Get Uniform Matrix --> Done " <<endl;
// };

// void planet::loadTexture(const std::string fullPathTexture){
//   cout << "Loading texture Sun" << endl;
//   glGenTextures(1, &texture);
//   std::unique_ptr<Image> texImg = loadImage(FilePath(fullPathTexture));
//   glBindTexture(GL_TEXTURE_2D, texture);
//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImg->getWidth(),texImg->getHeight(),0, GL_RGBA,GL_FLOAT, texImg->getPixels()); // envoie limage à la carte graphique
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//   glBindTexture(GL_TEXTURE_2D, 0);  
    
// }

// void planet::draw(){
//   //Check that the current shader is not this one to avoid swaps
//   GLint pgm;
//   glGetIntegerv( GL_CURRENT_PROGRAM, &pgm);
//   //If the shader is not active load it
//   if(pgm != _shader->getGLId()){
//     _shader->use();
//   }
//   //Drawing
//   glBindTexture(GL_TEXTURE_2D,_texture);
//   glActiveTexture(_texture);
//   glUniform1i(uSampler,0);
  
//   glBindVertexArray(_vao);
//   glDrawArrays(GL_TRIANGLES,0,_ball->getVertexCount());
//   glBindVertexArray(0);
  
//   glBindTexture(GL_TEXTURE_2D,0);

//   //Draw path
//   //drawPaths();
// }

// void planet::update(float delta){
//   //Updating the model matrix of the planet according to the rotation speed
//   rotations.y +=speed.y*delta;
//   translation = vec3(cos(rotations.y)*_pathCoords.w*_elipseCoefs.x + _pathCoords.x , cos(radians(rotations.y))*radians(_pathCoords.y),sin(rotations.y)*_pathCoords.w *_elipseCoefs.z + _pathCoords.z);
//   ModelMatrix = translate(mat4(1),translation);

//   rotations.x += speed.x*delta;
//   ModelMatrix = rotate(ModelMatrix,radians(rotations.x),vec3(0,1,0));




//   glm::mat4 MVMatrix(1);
//   MVMatrix = glm::translate(MVMatrix, glm::vec3(0.f, 0.f, 0.f));         //Translation
//   MVMatrix = glm::rotate(MVMatrix, +10.f, vec3(0,0,1));                   //Rotation * Translation
//   MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), vec3(0,1,0)); //Rotation * Rotation * Translation
//   glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
//   glUniformMatrix4fv(LocMVP,   1, GL_FALSE, glm::value_ptr( ProjMatrix * MVMatrix));
//   glUniformMatrix4fv(LocMV,    1, GL_FALSE, glm::value_ptr( MVMatrix));
//   glUniformMatrix4fv(LocNormal,1, GL_FALSE, glm::value_ptr( NormalMatrix));
//   glUniform1i(LocTextureTerre,0);
//   glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
	
// }

// void planet::DrawPlanet(const glm::mat4 &ProjMatrix, const glm::mat4 &CamView){
//     //Check that the current shader is not this one to avoid swaps
//     GLint pgm;
//     glGetIntegerv( GL_CURRENT_PROGRAM, &pgm);
//     //If the shader is not active load it
//     if(pgm != shaderProg->getGLId()){
//         shaderProg->use();
//         glGetIntegerv( GL_CURRENT_PROGRAM, &pgm);
//     } 

//     glBindVertexArray(vao);
//     //updateVBO à cause de la couleur, on doit mettreà jour les données
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     // Données récupérées de la class Cube ( voir fichier cpp + hpp)
//     glBufferData(GL_ARRAY_BUFFER, sun.getVertexCount() * sizeof(ShapeVertex), sun.getDataPointer(), GL_STATIC_DRAW);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glm::mat4 MVMatrix;
//     // if (BlockOrSkyBox == 0){
//     //     MVMatrix = glm::translate(CamView, vec3(posX,posY,posZ));    
//     //     MVMatrix = glm::scale(MVMatrix, vec3(0.5,0.5,0.5));
//     // }
//     // else{
//     //     MVMatrix = glm::scale(CamView, vec3(mapCraft::widthMap/2,mapCraft::elevationMap/2,mapCraft::heightMap/2));
//     // }        
    
//     glUniform1i(uTexture, 0);
//     glActiveTexture(GL_TEXTURE);

//     glBindTexture(GL_TEXTURE_2D, texture);
//     glUniformMatrix4fv(uMVPMatrix,   1, GL_FALSE, glm::value_ptr( ProjMatrix * MVMatrix));
//     glUniformMatrix4fv(uMVMatrix,    1, GL_FALSE, glm::value_ptr( MVMatrix));
//     glUniformMatrix4fv(uNormalMatrix,1, GL_FALSE, glm::value_ptr( glm::transpose(glm::inverse(MVMatrix))));
//     glDrawArrays(GL_TRIANGLES, i*faceNumber, faceNumber); 

//     glBindTexture(GL_TEXTURE_2D, 0);
//     glBindVertexArray(0);
// }

























// void planet::updateSat(float delta,vec3 source){
//   //Same than update except we pass the original planet path
//   rotations.y +=speed.y*delta;
//   translation = vec3(cos(rotations.y)*_pathCoords.w*_elipseCoefs.x + _pathCoords.x , cos(radians(rotations.y))*radians(_pathCoords.y),sin(rotations.y)*_pathCoords.w *_elipseCoefs.z + _pathCoords.z);
//   ModelMatrix = translate(mat4(1),translation);

//   rotations.x += speed.x*delta;
//   ModelMatrix = rotate(ModelMatrix,radians(rotations.x),vec3(0,1,0));

// }

// vector<vec3> planet::generatePath(){
//    vector<vec3> path;
//    for(float i = 0; i < 2*M_PI; i+=0.1){
//      vec3 tmp = vec3(cos(i)*_pathCoords.w + _ballCoords.x,0,0);
//      path.push_back(tmp);
//    }
//    return path;
//  }

// void planet::initPaths(){
//   //VBO creation
//   glGenBuffers(1,&pvbo);

//   glBindBuffer(GL_ARRAY_BUFFER,pvbo);
//   glBufferData(GL_ARRAY_BUFFER,path.size()*sizeof(vec3),path.data(),GL_STATIC_DRAW);
//   glBindBuffer(GL_ARRAY_BUFFER,0);
  
//   //VAO setting
//   glGenVertexArrays(1,&pvao);
//   glBindVertexArray(pvao);
//   glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
//   glBindBuffer(GL_ARRAY_BUFFER,pvbo);
//   glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT,GL_FALSE,sizeof(vec3),(const GLvoid*)0);
//   glBindBuffer(GL_ARRAY_BUFFER,0);
//   glBindVertexArray(0);
  
// }

// void planet::drawPaths(){

  
//     glBindVertexArray(pvao);
//     glDrawArrays( GL_LINE_LOOP,0,path.size());
//     glBindVertexArray(0);
  
// }
