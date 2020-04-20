
#ifndef MASTERCRAFT_MAPGENERATOR
#define MASTERCRAFT_MAPGENERATOR

#include <glm/gtc/noise.hpp>
#include <glm/glm.hpp>

#include <MasterCraft/Noise.hpp>
#include <MasterCraft/Chunk.hpp>

#include <stdio.h>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

namespace mapCraft {

    typedef Noise<glm::vec2> Noise2D;
    class mapGenerator{
        private:
            float *heightMapNoise;
            float *heightMapNormalize;
            Noise2D *noise;

            //Just For Me
            float oldMin = 0, oldMax = 1, newMin = 0, newMax = 92;
            float separatorGrassWater = 0.22f;

            /**/
            float *TreeMap;
            void generateHeightMap();
            void generateTree();
            int biome(float e);

        public:
            int nbChunkWidth;
            int nbChunkHeight;
            int nbChunkDepth;
            mapGenerator();


            /**
             * Generation de la map se basant sur le Noise "Simplex"
             * */
            void generateMap();

            float* getHeightMap(){
                return heightMapNormalize;
            };

            /**
             * Decoupage de la map en Chunk de 16 * 16 * 16
             * */
            void generateChunks(std::vector<std::vector<std::vector<game::Chunk*>>> &listOfChunk);

           
    };

    // const int leftFace = 0;
    // const int backFace = 1;
    // const int rightFace = 2;
    // const int frontFace = 3;
    // const int downFace = 4;
    // const int upFace = 5; 
}

#endif