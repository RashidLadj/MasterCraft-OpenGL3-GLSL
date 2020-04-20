#ifndef MASTERCRAFT_NOISE
#define MASTERCRAFT_NOISE

#include <iostream>
/**
 * a fractal Brownian Motion (fBM) given noise function.
 * Source 01: https://www.redblobgames.com/maps/terrain-from-noise/
 * Source 02: https://thebookofshaders.com/13/
 */
namespace mapCraft {
    /** T <=> {vec2 vec3 vec4 } **/
    /** For add after in template, parameter of noise <=> {Simplex , Perlin} 
     *  I used Simplex
     * **/
    
    template <typename T>
    class Noise{
        private:
            T Input;
            int octaves;      /**< Number of iteration of the noise. */
            float amplitude;      /**< Initial amplitude of the noise. */
            float frequency;      /**< Initial frequency of the noise. */
            float gain;           /**< Value the amplitude is multiplied each octave. */
            float lacunarity;     /**< Value the frequency is multiplied each octave. */

        public:
            Noise(int _octaves, float _amplitude, float _frequency, float _gain, float _lacunarity, T _Input): 
                octaves(_octaves), amplitude(_amplitude), frequency(_frequency), gain(_gain), lacunarity(_lacunarity), Input(_Input){
                std::cout << "Start Constructor Noise" << std::endl;
            };
        
            float generateNoise(T location){
                float value = 0.f;
                float freq = this->frequency;
                float ampl = this->amplitude;
                float totalAmp = ampl;
                for (int i = 0; i < octaves; ++i) {
                    value += ampl * (glm::simplex( freq *(location + Input)));
                    ampl *= this->gain;
                    totalAmp += ampl;
                    freq *= this->lacunarity;
                }
                float elevation = value  / totalAmp  / 2 + 0.5;
                return elevation;
            }

            float Normalize(float x, float oldMin, float oldMax, float newMin, float newMax){
                float value = x;
                float oldRange = (oldMax - oldMin);
                float newRange = (newMax - newMin);
                return (((value - oldMin) * newRange) / oldRange) + newMin;
            };
    };
}
#endif //MASTERCRAFT_NOISE