#ifdef _WIN32
#include <windows.h>
#endif 


#include <stdio.h>
#include <stdlib.h>


#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/common.hpp>
//#include <glimac/Cube.hpp>  // ??
#include <MasterCraft/Application.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>

//#include <glimac/mapCraft.hpp>

using namespace glimac;
using namespace glm;
using namespace std;
using namespace mapCraft;

FilePath *applicationPath; 


int main(int argc, char** argv) {
    
    #ifdef _WIN32
        AllocConsole();
        freopen("khra.txt", "w", stdout);
        freopen("CON", "w", stderr);
    #endif // WIN32
    auto con = fopen("CON", "w");
	if (!con) {
		printf("Cannot open CON\n");
	}
    std::cout << "hey hey " << std::endl;
    // Initialize SDL and open a window in full screen
    SDLWindowManager windowManager("MasterCraft");
    int window_H = windowManager.getMaxH();
    int window_W = windowManager.getMaxW();

    // initialise la bibliothèque GLEW. Cette bibliothèque charge l'ensemble des fonctions OpenGL3. 
    // Sans elle on peut considerer que l'on a accès qu'aux fonctions OpenGL2
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    // std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    // std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
    //the Shaders folder in the same folder as the main program
   applicationPath = new FilePath(argv[0]);

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    //Cube cube = Cube();
    Application MineCraftApp(windowManager);
    MineCraftApp.init();
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            /* ------------------
            *   MANAGE CAMERAS
            *  ------------------ */
           
        }
         MineCraftApp.handleEvent(e, done);

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         * On ecrit ici notre Code, aprés la boucle d'évenement
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MineCraftApp.draw();

        // // Update the display
         windowManager.swapBuffers();
    }

    // glDeleteBuffers(1, &vbo);
    // glDeleteVertexArrays(1, &vao);
    return EXIT_SUCCESS;
}