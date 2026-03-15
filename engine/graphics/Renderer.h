#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>
#include "../core/Window.h"

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
// Gestisce il disegno a schermo — creazione renderer, pulizia frame, presentazione
class Renderer {
    public:
        bool create(Window& window); // Crea il renderer collegato alla finestra, (ritorna false se la creazione fallisce)
        
        void destroy(); // Distrugge il renderer e libera la memoria
        
        void clear(); // Pulisce il frame corrente con il colore di sfondo
        
        void present(); // Scambia il buffer nascosto con quello visibile
        
        void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255); // Imposta il colore di sfondo (R, G, B, Trasparenza)
        
        void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255); // Imposta il colore di disegno corrente (R, G, B, Trasparenza)
        
        void fillRect(float x, float y, float w, float h); // Disegna un rettangolo pieno
        
        // Ritorna il puntatore al renderer SDL
        SDL_Renderer* get() const { return m_renderer;}
        
        // Ritorna true se il renderer è stato creato correttamente
        bool isValid() const { return m_renderer != nullptr; }

    private:
        SDL_Renderer* m_renderer = nullptr; // Puntatore al renderer SDL (nullptr = non creato)
        uint8_t m_bgR = 0; // Rosso
        uint8_t m_bgG = 0; // Verde
        uint8_t m_bgB = 0; // Blu
        uint8_t m_bgA = 255; // Trasparenza
    };
}