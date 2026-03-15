#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    // Gestisce il caricamento e il disegno di una texture a schermo
    class Texture {
        public:
            bool load(SDL_Renderer* renderer, const std::string& path); // Carica un'immagine da file, (ritorna false se il caricamento fallisce)
            
            void draw(SDL_Renderer* renderer, float x, float y); // Disegna la texture a schermo nella posizione (x, y)
           
            void drawScaled(SDL_Renderer* renderer, float x, float y, float w, float h);  // Disegna la texture ridimensionata a (w, h) pixel
            
            void destroy(); // Distrugge la texture e libera la memoria
            
            int getWidth()  const { return m_width; } // Ritorna la larghezza della texture in pixel
            
            int getHeight() const { return m_height; } // Ritorna l'altezza della texture in pixel
            
            bool isValid()  const { return m_texture != nullptr; } // Ritorna true se la texture è stata caricata correttamente

            SDL_Texture* getSDLTexture() const { return m_texture; } // Ritorna il puntatore alla texture SDL (o nullptr se non caricata)

        private:
            SDL_Texture* m_texture = nullptr; // Puntatore alla texture SDL (nullptr = non caricata)
            int m_width  = 0; // Larghezza in pixel
            int m_height = 0; // Altezza in pixel
    };
}