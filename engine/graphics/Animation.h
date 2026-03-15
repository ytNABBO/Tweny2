#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>
#include "Texture.h"

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    // Gestisce un'animazione da spritesheet — avanza i frame in base al tempo
    class Animation {
        public:
            // Configura l'animazione
            // texture — lo spritesheet da cui leggere i frame
            // frameCount — numero di frame nel spritesheet
            // frameTime  — secondi per frame
            void setup(Texture* texture, int frameCount, float frameTime);
            
            void update(float deltaTime); // Aggiorna il timer e avanza al frame successivo se necessario
            
            void draw(SDL_Renderer* renderer, float x, float y); // Disegna il frame corrente nella posizione (x, y)
            
            void reset(); // Resetta l'animazione al primo frame
            
            void setPaused(bool paused) { m_paused = paused; } // Mette in pausa o riprende l'animazione
        
        private:
            Texture* m_texture = nullptr; // Spritesheet da cui leggere i frame
            int m_frameCount = 1; // Numero totale di frame
            int m_currentFrame = 0; // Frame corrente
            float m_frameTime = 0.15f; // Secondi per frame
            float m_timer = 0.0f; // Timer accumulato
            bool m_paused = false; // Se true, l'animazione non avanza
    };
}