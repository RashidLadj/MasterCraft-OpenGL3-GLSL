#include "MasterCraft/BlockMineCraft.hpp"


game::BlockMineCraft::BlockMineCraft(){
    cube = Cube();
    /*******************************************
    * HERE SHOULD COME THE INITIALIZATION CODE *
    *******************************************/
    //Creation du VBO
    initVBO();
    //Creation du VAO
    initVAO();
}

void game::BlockMineCraft::initVBO(){
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Données récupérées de la class Cube ( voir fichier cpp + hpp)
    glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount() * sizeof(ShapeVertex), cube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void game::BlockMineCraft::initVAO(){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        GLsizei stride = sizeof(ShapeVertex);  // le nombre d'octets séparant l'attribut pour deux sommets consécutifs.
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, stride , (const GLvoid*)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, stride , (const GLvoid*)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, stride , (const GLvoid*)offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);  
    glEnable(GL_DEPTH_TEST);
}

void game::BlockMineCraft::setPosX(int _posX){
    posX = _posX;
}

void game::BlockMineCraft::setPosY(int _posY){
    posY = _posY;   
}

void game::BlockMineCraft::setPosZ(int _posZ){
    posZ = _posZ;
}

void game::BlockMineCraft::assignShader(Program &shader){
    shaderProg = &shader;
    //cout << "shaderProg->getGLId() int assignShader"<< shader.getGLId() << endl;
    shader.use();
    GLint pgm;
    glGetIntegerv( GL_CURRENT_PROGRAM, &pgm);
    uMVMatrix = glGetUniformLocation(shaderProg->getGLId(), "uMVMatrix");
    uMVPMatrix = glGetUniformLocation(shaderProg->getGLId(), "uMVPMatrix");
    uNormalMatrix = glGetUniformLocation(shaderProg->getGLId(), "uNormalMatrix");
    uTexture = glGetUniformLocation(shaderProg->getGLId(), "uTexture");
    cout << "   --> Get Uniform Matrix --> Done " <<endl;
}

/** Start No Used After **/
/*
void BlockMineCraft::updateColor(glm::vec3 color) {
    for(int i = 0; i < cube.getVertexCount(); ++i){
        cube.getData()[i].normal.x = color.x;
        cube.getData()[i].normal.y = color.y;
        cube.getData()[i].normal.z = color.z;
    }
}

void BlockMineCraft::updateColorFace(int face, glm::vec3 color) {
    std::vector<ShapeVertex>  temp= cube.getData();
    for(int i = 6 * face; i < 6 * (face+1 ); ++i){
         temp[i].normal.x = color.x;
         temp[i].normal.y = color.y;
         temp[i].normal.z = color.z;
    }
}
*/
/** End No Used After **/

/** Ok **/
void game::BlockMineCraft::loadTexture(const std::string pathFile, const std::string nameFile){
   glGenTextures(faceNumber, texture);
    for(int face = 0; face < faceNumber; face++){
        string fullNameFile =  to_string(face) + nameFile;  
        string fullPathTexture = pathFile + fullNameFile;
        std::unique_ptr<Image> texImg = loadImage(FilePath(fullPathTexture));
        glBindTexture(GL_TEXTURE_2D, texture[face]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImg->getWidth(),texImg->getHeight(),0, GL_RGBA,GL_FLOAT, texImg->getPixels()); // envoie limage à la carte graphique
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);  
    }
}

/** Ok **/
void game::BlockMineCraft::loadTexture(const std::string pathFile, const std::string nameFile, const int face){
    string fullNameFile =  to_string(face) + nameFile;  
    string fullPathTexture = pathFile + fullNameFile;
    std::unique_ptr<Image> texImg = loadImage(FilePath(fullPathTexture));
    glBindTexture(GL_TEXTURE_2D, texture[face]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImg->getWidth(),texImg->getHeight(),0, GL_RGBA,GL_FLOAT, texImg->getPixels()); // envoie limage à la carte graphique
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void game::BlockMineCraft::DrawBlock(const glm::mat4 &ProjMatrix, const glm::mat4 &CamView, const int BlockOrSkyBox){
    //Check that the current shader is not this one to avoid swaps
    GLint pgm;
    glGetIntegerv( GL_CURRENT_PROGRAM, &pgm);
    //If the shader is not active load it
    if(pgm != shaderProg->getGLId()){
        shaderProg->use();
        glGetIntegerv( GL_CURRENT_PROGRAM, &pgm);
    } 

    glBindVertexArray(vao);
    //updateVBO à cause de la couleur, on doit mettreà jour les données
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Données récupérées de la class Cube ( voir fichier cpp + hpp)
    glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount() * sizeof(ShapeVertex), cube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glm::mat4 MVMatrix;
    if (BlockOrSkyBox == 0){
        MVMatrix = glm::translate(CamView, vec3(posX,posY,posZ));    
        MVMatrix = glm::scale(MVMatrix, vec3(0.5,0.5,0.5));
    }
    else{
        MVMatrix = glm::scale(CamView, vec3(mapCraft::widthMap/2,mapCraft::elevationMap/2,mapCraft::heightMap/2));
    }        
    //glm::mat4 MVMatrix = glm::translate(mat4(1), vec3(0,0,-20));
    //MVMatrix = glm::rotate(MVMatrix, glm::radians(30.f), vec3(1,0,0));   
    //MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), vec3(0,0,1));                   //Rotation
    //MVMatrix = glm::translate(MVMatrix, vec3(i*cube.m_CubeEdgeSize,0,j*cube.m_CubeEdgeSize));                   //Rotation
    
    //MVMatrix = glm::rotate(MVMatrix, 5, vec3(0,1,0)); //Rotation * Rotation
    //glUniform3f(uColor,   color.x, color.y, color.z);
    
    glUniform1i(uTexture, 0);
    glActiveTexture(GL_TEXTURE);
    for( int i = 0; i<faceNumber; ++i){
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        glUniformMatrix4fv(uMVPMatrix,   1, GL_FALSE, glm::value_ptr( ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix,    1, GL_FALSE, glm::value_ptr( MVMatrix));
        glUniformMatrix4fv(uNormalMatrix,1, GL_FALSE, glm::value_ptr( glm::transpose(glm::inverse(MVMatrix))));
        glDrawArrays(GL_TRIANGLES, i*faceNumber, faceNumber); 
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
};




