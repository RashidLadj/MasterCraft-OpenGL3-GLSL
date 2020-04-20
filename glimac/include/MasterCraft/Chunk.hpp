
#ifndef MASTERCRAFT_CHUNK
#define MASTERCRAFT_CHUNK

#include <vector>
#include <cmath>
// #include <MasterCraft/DefaultValue.hpp>
#include <MasterCraft/BlockMineCraft.hpp>

using namespace mapCraft;

namespace game{
    static int chunkSize = 16;
    class Chunk{
        private:
            std::vector<int> values;
            glm::vec3 position;


        public:
         bool empty;
            Chunk(){
                /** inisilize Vcetor of value with 16*16*16 zeros **/
                values = std::vector<int>(std::pow(chunkSize, 3), 0);
                empty = true;
            };

            //Chunk(double*** map3D, int StartX, int StartY, int StartZ);

            ~Chunk() {
            //delete
            };

            void setValue(int position, int value){
               // std::cout << "WTH " << std::endl;
                values[position] =  value;
               // std::cout << "WTH " << std::endl;
            };

            int getValue(int position){
                return values[position];
            };

            void setPosition(int z, int x, int y){
                position.x = x;
                position.y = y;
                position.z = z;
            };

            glm::vec3 getPosition(){
                return position;
            }

            void drawChunk(glm::mat4 ProjMatrix, glm::mat4 viewMatrix, std::vector<game::BlockMineCraft> blocks){
                /** Underwater represente 1 dans la map **/
                /** Water represente 2 dans la map **/
                /** Sand represente 3 dans la map **/
                /** Grass represente 4 dans la map **/
                /** Tree represente 5 dans la map **/
                for (int z = 0; z < chunkSize; ++z){
                    for (int x = 0; x < chunkSize; ++x){
                        for (int y = 0; y < chunkSize; ++y){
                            int typeBlock = values[y * chunkSize * chunkSize + z * chunkSize + x ];

                            if( typeBlock != 0){

                                /** Draw Tree**/
                                if(typeBlock == mapCraft::TREE_B){
                                    for (int yy = 0; yy<3; yy++){
                                        int posZ = position.z * chunkSize  + z - mapCraft::heightMap/2; 
                                        int posX = position.x * chunkSize  + x - mapCraft::widthMap/2;
                                        int posY = position.y * chunkSize  + y+yy - mapCraft::elevationMap/2;

                                        blocks[typeBlock-1].setPosZ(posZ);
                                        blocks[typeBlock-1].setPosX(posX);
                                        blocks[typeBlock-1].setPosY(posY);
                                        blocks[typeBlock-1].DrawBlock(ProjMatrix, viewMatrix, 0);
                                    }
                                    for (int yy = 3; yy<5; yy++){
                                        for (int xx = -1; xx<2; xx++){
                                            for (int zz = -1; zz<2; zz++){
                                                int posZ = position.z * chunkSize  + z+zz - mapCraft::heightMap/2; 
                                                int posX = position.x * chunkSize  + x+xx - mapCraft::widthMap/2;
                                                int posY = position.y * chunkSize  + y+yy - mapCraft::elevationMap/2;

                                                blocks[typeBlock].setPosZ(posZ);
                                                blocks[typeBlock].setPosX(posX);
                                                blocks[typeBlock].setPosY(posY);
                                                blocks[typeBlock].DrawBlock(ProjMatrix, viewMatrix, 0);
                                            }
                                        }
                                    }
                                   
                                }
                                else{
                                    if(typeBlock == mapCraft::WATER){
                                        //For opacity Of Water :'( :'( :'( 
                                        // glEnable(GL_BLEND);
                                        // glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
                                        // glBlendColor(1.f, 1.f, 1.f, 0.1f);
                                    }                         
                                    int posZ = position.z * chunkSize  + z - mapCraft::heightMap/2; 
                                    int posX = position.x * chunkSize  + x - mapCraft::widthMap/2;
                                    int posY = position.y * chunkSize  + y - mapCraft::elevationMap/2;

                                    blocks[typeBlock-1].setPosZ(posZ);
                                    blocks[typeBlock-1].setPosX(posX);
                                    blocks[typeBlock-1].setPosY(posY);
                                    blocks[typeBlock-1].DrawBlock(ProjMatrix, viewMatrix, 0);
                                    glDisable(GL_BLEND);  
                                }
                            }
                        }
                    }
                }
            };
    };
};

#endif