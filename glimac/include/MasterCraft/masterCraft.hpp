
#ifndef MASTERCRAFT_GAME
#define MASTERCRAFT_GAME

#include "MasterCraft/mapGenerator.hpp"
#include <glimac/Program.hpp>
#include "MasterCraft/BlockMineCraft.hpp"
#include "glimac/FilePath.hpp"

extern FilePath *applicationPath;

namespace game{
    class masterCraft{
        private:
            Program* m_Program;
            mapCraft::mapGenerator map;
            std::vector<game::BlockMineCraft> differentBlocks;
            std::vector<std::vector<std::vector<Chunk*>>> listOfChunk;
            std::vector<Chunk*> chunksToDisplay;


        public:
            masterCraft(){};
            masterCraft(Program *_Program);
            ~masterCraft();
            
            /** prepare tout les chunks et les stock dans listOfChunk **/
            void initGame();

            /** load que les chunks a  afficher **/
            void loadChunks(glm::vec3 cameraChunk);

            /** draw els chunk a afficher **/ 
            void Draw(glm::mat4 ProjMatrix, glm::mat4 viewMatrix);

            void DrawAll(glm::mat4 ProjMatrix, glm::mat4 viewMatrix);

            void generateBlocks();
    };
}

#endif