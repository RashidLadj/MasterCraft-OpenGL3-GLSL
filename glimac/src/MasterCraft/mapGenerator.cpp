#include "MasterCraft/mapGenerator.hpp"

using namespace mapCraft;

mapGenerator::mapGenerator(){
    /** reglages des parametre du Noise se basant sur Simplex **/
    srand(time(NULL));
    noise = new Noise2D(3, 1.f, 1/256.f, 0.5f, 2.f, glm::vec2(0,0));//rand()%10000, rand()%10000));
    /** Initisalisation de la taille de la map **/
    heightMapNoise = (float*)malloc(sizeof(float) * mapCraft::heightMap * mapCraft::widthMap);
    heightMapNormalize = (float*)malloc(sizeof(float) * mapCraft::heightMap * mapCraft::widthMap);
    TreeMap = (float*)malloc(sizeof(float) * mapCraft::heightMap * mapCraft::widthMap);

    nbChunkWidth = mapCraft::widthMap/game::chunkSize;
    nbChunkHeight = mapCraft::heightMap/game::chunkSize;
    nbChunkDepth = mapCraft::elevationMap/game::chunkSize;
    std::cout << "Init Parameters of Map " << std::endl;
};

void  mapGenerator::generateMap(){
    generateHeightMap();
    std::cout << "??" << std::endl;
    generateTree();
    std::cout << "!!!" << std::endl;
};

void mapGenerator::generateHeightMap(){
    for (int i =0; i < mapCraft::heightMap; ++i){
        for (int j =0; j < mapCraft::widthMap; ++j){
            float elevation = noise->generateNoise(glm::vec2(i, j));   
            heightMapNoise[i * mapCraft::widthMap + j] = elevation;
        }
    }
    for (int y = 0; y < mapCraft::heightMap; y++) {
        for (int x = 0; x < mapCraft::widthMap; x++) {
            float elevation = noise->Normalize(heightMapNoise[y * mapCraft::widthMap+ x], oldMin, oldMax, newMin, newMax);
            heightMapNormalize[y * mapCraft::widthMap + x] = (int)elevation;
        }
    }
};

void mapGenerator::generateTree(){
    /** For Tree **/
    int R = 4;
    for (int yc = R; yc < mapCraft::heightMap - R; yc++) {
        for (int xc = R; xc < mapCraft::widthMap - R; xc++) {
            double max = 0;
            // there are more efficient algorithms than this
            for (int yn = yc - R; yn <= yc + R; yn++) {
                for (int xn = xc - R; xn <= xc + R; xn++) {
                    double e = heightMapNoise[yn * mapCraft::widthMap + xn];
                    if (e > max) { max = e; }
                }
            }
            if (heightMapNoise[yc * mapCraft::widthMap + xc] == max) {
                // place tree at xc,yc
                TreeMap[yc * mapCraft::widthMap + xc] = 1;
            }
        }
    }
};

int mapGenerator::biome(float e){
    int WaterVsLand = noise->Normalize(separatorGrassWater, oldMin, oldMax, newMin, newMax);
    if (e < WaterVsLand) return UNDERWATER;
    if (e == WaterVsLand) return SAND;
    if (e > WaterVsLand) return LAND;
    return EMPTINESS;
};

void mapGenerator::generateChunks(std::vector<std::vector<std::vector<game::Chunk*>>> &listOfChunk){
    /** x/j => width && y/k => pronfondeur && z/i => height **/
    /** z * width + x * profondeur + k **/
    for (int z=0; z<mapCraft::heightMap; z++){
        for (int x=0; x<mapCraft::widthMap; x++){
            {
                /** Recuperation du chunk concerné par la modification **/
                int posZchunk = z/game::chunkSize;
                int posXchunk = x/game::chunkSize;
                
                int posYchunk = heightMapNormalize[z * mapCraft::widthMap + x]/game::chunkSize;

                game::Chunk *chunk = listOfChunk[posZchunk][posXchunk][posYchunk];
      
                /** Recuperation du Block concerné par la modification **/
                int posZinChunk = z % game::chunkSize;
                int posXinChunk = x % game::chunkSize;

                int posYinChunk = ((int)heightMapNormalize[z * mapCraft::widthMap + x] + mapCraft::elevationMap/2) % game::chunkSize;
                 //std::cout << "WTF" << posYinChunk*(game::chunkSize*game::chunkSize) + posZinChunk*game::chunkSize + posXinChunk <<std::endl;
                chunk->setValue(posYinChunk*(game::chunkSize*game::chunkSize) + posZinChunk*game::chunkSize + posXinChunk, biome(heightMapNormalize[z * mapCraft::widthMap + x]));
                //std::cout << "WTF" << biome(heightMapNormalize[z * mapCraft::widthMap + x]) << std::endl;
                chunk->empty = false;
            }
            {
                /** cas a traité pour dessiner l'eau au meme niveau **/
                if(biome(heightMapNormalize[z * mapCraft::widthMap + x]) == UNDERWATER){
                    int WaterVsLand = noise->Normalize(separatorGrassWater, oldMin, oldMax, newMin, newMax);
                    for(int k = heightMapNormalize[z * mapCraft::widthMap + x]+1; k <WaterVsLand; k++  ){
                        /** Recuperation du chunk concerné par la modification **/
                        int posZchunk = z/game::chunkSize;
                        int posXchunk = x/game::chunkSize;
                        int posYchunk = k/game::chunkSize;
                        game::Chunk *chunk = listOfChunk[posZchunk][posXchunk][posYchunk];
                        /** Recuperation du Block concerné par la modification **/
                        int posZinChunk = z % game::chunkSize;
                        int posXinChunk = x % game::chunkSize;
                        int posYinChunk = (k + mapCraft::elevationMap/2) % game::chunkSize; // WTH
                        chunk->setValue(posYinChunk*(game::chunkSize*game::chunkSize) + posZinChunk*game::chunkSize + posXinChunk, WATER);
                        chunk->empty = false;
                    }
                }
            }
            {
                if(TreeMap[z * mapCraft::widthMap + x] == 1){
                    int Pos = heightMapNormalize[z * mapCraft::widthMap + x];
                    for(int k = Pos; k <Pos+3; k++  ){
                        /** Recuperation du chunk concerné par la modification **/
                        int posZchunk = z/game::chunkSize;
                        int posXchunk = x/game::chunkSize;
                        int posYchunk = (Pos)/game::chunkSize;
                        game::Chunk *chunk = listOfChunk[posZchunk][posXchunk][posYchunk];
                        /** Recuperation du Block concerné par la modification **/
                        int posZinChunk = z % game::chunkSize;
                        int posXinChunk = x % game::chunkSize;
                        int posYinChunk = (Pos + mapCraft::elevationMap/2) % game::chunkSize;
                        chunk->setValue(posYinChunk*(game::chunkSize*game::chunkSize) + posZinChunk*game::chunkSize + posXinChunk, TREE_B);
                        chunk->empty = false;
                    }
                //     for(int k = Pos+3; k <Pos+4; k++  ){
                //         for(int k = Pos; k <Pos+3; k++  ){
                //             /** Recuperation du chunk concerné par la modification **/
                //             int posZchunk = z/game::chunkSize;
                //             int posXchunk = x/game::chunkSize;
                //             int posYchunk = (k)/game::chunkSize;
                //             game::Chunk *chunk = listOfChunk[posZchunk][posXchunk][posYchunk];
                //             /** Recuperation du Block concerné par la modification **/
                //             int posZinChunk = z % game::chunkSize;
                //             int posXinChunk = x % game::chunkSize;
                //             int posYinChunk = (k + mapDepth/2) % game::chunkSize;
                //             chunk->setValue(posYinChunk*(game::chunkSize*game::chunkSize) + posZinChunk*game::chunkSize + posXinChunk, TREE_B);
                //             chunk->empty = false;
                //         }
                //     }
                 }
            }
        }
    }
};