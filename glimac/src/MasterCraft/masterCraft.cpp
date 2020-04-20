#include <MasterCraft/masterCraft.hpp>


using namespace game;


masterCraft::masterCraft(Program *_Program):m_Program(_Program){
    map = mapCraft::mapGenerator();
    /** Initialize List Of Chunk , with Chunk with All case 0 **/
    for (int i = 0; i < mapCraft::heightMap / game::chunkSize; ++i){
        listOfChunk.push_back(std::vector<std::vector<game::Chunk*>>());
        for (int j = 0; j < mapCraft::widthMap / game::chunkSize; ++j){
            listOfChunk[i].push_back(std::vector<game::Chunk*>());
            for (int k = 0; k < mapCraft::elevationMap / game::chunkSize; ++k){
                listOfChunk[i][j].push_back(new Chunk());
            }
        }
    }
    std::cout << "init List of Chunks" << std::endl;
};

masterCraft::~masterCraft(){
    // for (int i = 0; i < game::chunkSize; ++i){
    //     listOfChunk.push_back(std::vector<std::vector<game::Chunk*>>());
    //     for (int j = 0; j < game::chunkSize; ++j){
    //         listOfChunk[i].push_back(std::vector<game::Chunk*>());
    //         for (int k = 0; k < game::chunkSize; ++k){
    //             delete listOfChunk[i][j][k];
    //         }
    //     }
    // }
};

void masterCraft::initGame(){
    map.generateMap();
        cout << "   --> Generate Map Done " << endl;
    map.generateChunks(listOfChunk);
        cout << "   --> Generate Chunks Done " << endl;    
    generateBlocks();
        cout << "   --> Generate Blocks Done " << endl;            
};

/**
 *  Charger les 27 chunks à afficher dont le chunk central est al position de la camera
 * l'appelle de cette methode ne se fait que si la camera change de position
 * */
void masterCraft::loadChunks(const glm::vec3 cameraChunk){
    chunksToDisplay.clear();
    int offset = 1;
    for (int zChunk = cameraChunk.z-offset; zChunk <= cameraChunk.z+offset; ++zChunk){
        for (int xChunk = cameraChunk.x-offset; xChunk <= cameraChunk.x+2+offset; ++xChunk){
            for (int yChunk = cameraChunk.y-offset; yChunk <= cameraChunk.y+2+offset; ++yChunk){
                if (zChunk>= 0 && zChunk< map.nbChunkHeight && 
                        xChunk>= 0 && xChunk< map.nbChunkWidth && 
                        yChunk>= 0 && yChunk< map.nbChunkDepth){

                    Chunk *chunk = listOfChunk[zChunk][xChunk][yChunk];
                    //std::cout << "    Done " <<  std::endl;
                    listOfChunk[zChunk][xChunk][yChunk]->setPosition(zChunk, xChunk, yChunk);
                    if( !listOfChunk[zChunk][xChunk][yChunk]->empty){
                        //std::cout << "  Chunk Condidat       ->  zxy [" << zChunk <<"]["<< xChunk <<"]["<< yChunk <<"]  Done is not Emplty";
                        chunksToDisplay.push_back(chunk);
                    }
                }
            }
        }
    }
    std::cout << "   --> Load Chunks to Display Done " << chunksToDisplay.size() << std::endl;
};

void masterCraft::Draw(glm::mat4 ProjMatrix, glm::mat4 viewMatrix){
    for (auto chunk : chunksToDisplay){
        chunk->drawChunk(ProjMatrix, viewMatrix, differentBlocks);
    }
};


void masterCraft::generateBlocks(){
    /** water represente 1 dans la map **/
    BlockMineCraft blockMineCraftWater = BlockMineCraft();
    blockMineCraftWater.assignShader(*m_Program);
    blockMineCraftWater.loadTexture((applicationPath->dirPath()).str() + "/Textures/Water/", "-Water.png");

    /** Sand represente 2 dans la map **/
    BlockMineCraft blockMineCraftSand = BlockMineCraft();
    blockMineCraftSand.assignShader(*m_Program);
    blockMineCraftSand.loadTexture((applicationPath->dirPath()).str() + "/Textures/Sand/", "-sand.png");

    /** Grass represente 3 dans la map **/
    BlockMineCraft blockMineCraftGrass = BlockMineCraft();
    blockMineCraftGrass.assignShader(*m_Program);
    blockMineCraftGrass.loadTexture((applicationPath->dirPath()).str() + "/Textures/Grass/", "-Grass.png");

    /** Tree represente 4 dans la map **/
    BlockMineCraft blockMineCraftTreeBois = BlockMineCraft();
    blockMineCraftTreeBois.assignShader(*m_Program);
    blockMineCraftTreeBois.loadTexture((applicationPath->dirPath()).str() + "/Textures/Tree/", "-Tree.png");

    /** Tree represente 4 dans la map **/
    BlockMineCraft blockMineCraftTreeVerdure = BlockMineCraft();
    blockMineCraftTreeVerdure.assignShader(*m_Program);
    blockMineCraftTreeVerdure.loadTexture((applicationPath->dirPath()).str() + "/Textures/Tree/", "-Tree3.png");

    differentBlocks.push_back(blockMineCraftSand);
    differentBlocks.push_back(blockMineCraftWater);
    differentBlocks.push_back(blockMineCraftSand);
    differentBlocks.push_back(blockMineCraftGrass);
    differentBlocks.push_back(blockMineCraftTreeBois);
    differentBlocks.push_back(blockMineCraftTreeVerdure);
};  

void masterCraft::DrawAll(glm::mat4 ProjMatrix, glm::mat4 viewMatrix){
    for (auto vvchunk : listOfChunk){
        for (auto vchunk : vvchunk){
            for (auto chunk : vchunk){
                //std::cout << ">> " << chunk.getValue(posZinChunk * game::chunkSize + posXinChunk * game::chunkSize + posYinChunk) << std::endl;
                if(!chunk->empty){
                    chunk->drawChunk(ProjMatrix, viewMatrix, differentBlocks);
                }   
            }
        }
    }
};