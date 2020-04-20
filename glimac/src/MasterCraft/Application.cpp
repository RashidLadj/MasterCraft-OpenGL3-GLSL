#include "MasterCraft/Application.hpp"



Application::Application(SDLWindowManager &_window){
  cout << "Start Application Of MasterCraft --> Done " << endl;
  window = &_window;
}

bool Application::init(){
  glEnable(GL_DEPTH_TEST);

  cam = FreeflyCamera();
  cam.moveFront(0);
  cout << "Implementation of FreeFlyCamera and eneable DepthTest --> Done " << endl;
  //glEnable(GL_TEXTURE_2D);
  
  //loadingShaders
  m_Program = loadProgram(  applicationPath->dirPath() + "Shaders/VertexShader.glsl", applicationPath->dirPath() + "Shaders/FragmentShaderLight.glsl");
    cout << "   --> Load Shaders program \"VertexShader.glsl\" and \"VertexShader.gls\" --> Done "<<endl;

  SkyBox = game::BlockMineCraft();
  SkyBox.assignShader(m_Program);
  SkyBox.loadTexture(applicationPath->dirPath().str() + "/Textures/SkyBox/SkyBoxNuit/", "-SkyBoxNuit.png");
  cout << "   --> Create SkyBox + Create VAO and VBO and Assign Program Shaders and textures --> Done " << endl;

  // sun = planet(5);
  
  //Init projections
  cout << "   --> Init Projection Done " << endl;
  ProjMatrix = glm::perspective(glm::radians(70.f), (float)(window->getMaxW()/window->getMaxH()), 0.1f, 400.f);
  
  /** init Game (Map, Chunks, ChunksToDisplay, and Block) **/
  masterGame = game::masterCraft(&m_Program);
  masterGame.initGame();
  /** Declarer pos OldChunk and NewChunk **/
  posCamera = cam.getEye();
  oldChunk = glm::vec3(int((posCamera.z + mapCraft::widthMap/2)/game::chunkSize), int((posCamera.x + mapCraft::heightMap/2)/game::chunkSize), int((posCamera.y + mapCraft::widthMap/2)/game::chunkSize));
  masterGame.loadChunks(oldChunk);
  return true;
}

void Application::handleEvent(SDL_Event e, bool &boolean){

  //continuous-response keys
    const Uint8 *state = SDL_GetKeyState(NULL);
    
  switch(e.type){
    case SDL_KEYDOWN :
      if(window->isKeyPressed(SDLK_ESCAPE)) {
          boolean = true; // Leave the loop after this iteration
      }
      if(window->isKeyPressed(SDLK_w)) {    //z
        z = true;
      }
      if(window->isKeyPressed(SDLK_s)) {    //s
        s = true;
      }
      if(window->isKeyPressed(SDLK_a)) {    //q
        q = true;
      }
      if(window->isKeyPressed(SDLK_d)) {    //d
        d = true;
      }
      if(window->isKeyPressed(SDLK_e)) {    //d
        drawAllMap = true;
      }
      if(window->isKeyPressed(SDLK_f)) {    //d
        drawAllMap = false;
      }
      if(window->isKeyPressed(SDLK_SPACE)) {
        glm::vec3 pos = cam.getEye();
        if (pos.y < (0 + mapCraft::elevationMap/2 - 3)){
          pos.y++;
          cam.setEye(pos); //ajouter un dans le Y :'(
        }
      }
      break;

    case SDL_KEYUP :
      if(e.key.keysym.sym == (SDLK_w)) {    //z
        z = false;
      }
      if(e.key.keysym.sym == (SDLK_s)) {    //s
        s = false; 
      }
      if(e.key.keysym.sym == (SDLK_a)) {    //q
        q = false;
      }
      if(e.key.keysym.sym == (SDLK_d)) {    //d
        d = false;
      }
      break;
    
    case SDL_MOUSEMOTION :
      if(leftClickIsPressed) {
        cam.rotateUp((e.button.y - y) * 0.1); // Leave the loop after this iteration
        cam.rotateLeft((e.button.x - x) * 0.1); 
        y = e.button.y;
        x = e.button.x;                                                                                                            
      }
      break;            
    
    case SDL_MOUSEBUTTONDOWN :
      if(e.button.button == SDL_BUTTON_LEFT) {
        leftClickIsPressed = true;
        y = e.button.y;
        x = e.button.x;                                                                                                            
      }
      break;

    case SDL_MOUSEBUTTONUP:
      if(e.button.button == SDL_BUTTON_LEFT) {
        leftClickIsPressed = false;                                                                                                            
      }
      break;
  }
  if(  cam.getEye().x > (0 - mapCraft::widthMap/2 +3)     &&  cam.getEye().x < (0 + mapCraft::widthMap/2 -3)
    && cam.getEye().y > (0 - mapCraft::elevationMap/2 +3) &&  cam.getEye().y < (0 + mapCraft::elevationMap/2 -3)
    && cam.getEye().z > (0 - mapCraft::heightMap/2 +3)    &&  cam.getEye().z < (0 + mapCraft::heightMap/2 -3)
  ){
    if (q)
    cam.moveLeft(pas);
    if (d)
    cam.moveLeft(-pas);
    if (z)
      cam.moveFront(pas); 
    if (s)
      cam.moveFront(-pas);
  }
  else{
    if(cam.getEye().x <= (0 - mapCraft::widthMap/2 +3)){
      glm::vec3 pos = cam.getEye();
      pos.x++;
      cam.setEye(pos); //ajo
    }
    if(cam.getEye().y <= (0 - mapCraft::elevationMap/2 +3)){
      glm::vec3 pos = cam.getEye();
      pos.y++;
      cam.setEye(pos); //ajo
    }
    if(cam.getEye().z <= (0 - mapCraft::heightMap/2 +3)){
      glm::vec3 pos = cam.getEye();
      pos.z++;
      cam.setEye(pos); //ajo
    }
    if(cam.getEye().x >= (0 + mapCraft::widthMap/2 -3)){
      glm::vec3 pos = cam.getEye();
      pos.x--;
      cam.setEye(pos); //ajo
    }
    if(cam.getEye().y >= (0 + mapCraft::elevationMap/2 -3)){
      glm::vec3 pos = cam.getEye();
      pos.y--;
      cam.setEye(pos); //ajo
    }
    if(cam.getEye().z >= (0 + mapCraft::heightMap/2 -3)){
      glm::vec3 pos = cam.getEye();
      pos.z--;
      cam.setEye(pos); //ajo
    }
    
    std::cout << "Positiona ctuelle .. "<< cam.getEye() << std::endl;
  }
  
   
}

void Application::draw(){
  SkyBox.DrawBlock(ProjMatrix, cam.getViewMatrix(), 1);

  /******* after load necaisary ***/
  if(!drawAllMap){
    posCamera = cam.getEye(); // x y z
    int xCam = posCamera.x;
    int yCam = posCamera.y;
    int zCam = posCamera.z;
   //brg
    glm::vec3 newChunk = glm::vec3(int((posCamera.x + mapCraft::widthMap/2)/game::chunkSize), int((posCamera.y + mapCraft::heightMap/2)/game::chunkSize), int((posCamera.z + mapCraft::widthMap/2)/game::chunkSize));
    if (newChunk.x>=0 && newChunk.x<mapCraft::widthMap/game::chunkSize 
        && newChunk.y>=0 && newChunk.y<mapCraft::elevationMap/game::chunkSize
        && newChunk.z>=0 && newChunk.z<mapCraft::heightMap/game::chunkSize
        && oldChunk != newChunk){
      masterGame.loadChunks(newChunk);
      oldChunk = newChunk;
      masterGame.Draw(ProjMatrix, cam.getViewMatrix());
    }
    else
      masterGame.Draw(ProjMatrix, cam.getViewMatrix());
  }
  else{
    masterGame.DrawAll(ProjMatrix, cam.getViewMatrix());
  }

  /*Recuperation position Lumiere qui ne amrche pas actuellement*/
  glm::mat4 MVMatrix(1);
  MVMatrix = glm::translate(MVMatrix, glm::vec3(mapCraft::widthMap/2, mapCraft::elevationMap/6, -0.f));         //Translation
  MVMatrix = glm::rotate(MVMatrix, window->getTime()*1000, vec3(0,0,1));                   //Rotation * Translation  
  glm::vec4 positionLight = glm::vec4(0,0,0,1) * MVMatrix;
  //std::cout << "Why ??  == "<< khra.x << " "<< khra.y << " "<< khra.z << " "<< khra.w << "   " << window->getTime()*1000 <<std::endl; 




//   skybox.draw();
//   //Setting cull face to its origin to not affect other plantes
//   glCullFace(GL_BACK);
}
