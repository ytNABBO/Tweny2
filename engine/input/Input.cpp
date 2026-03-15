#include "Input.h"

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    void Input::update(bool& running) {
        SDL_Event event;

        // Processa tutti gli eventi in coda
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    running = false;
                }

                m_keys[event.key.keysym.scancode] = true;
                m_order[event.key.keysym.scancode] = ++m_counter; // Aggiorna l'ordine di pressione — il contatore aumenta ad ogni tasto premuto
            }
            if (event.type == SDL_KEYUP) {
                m_keys[event.key.keysym.scancode] = false;
                m_order[event.key.keysym.scancode] = 0; // Azzera l'ordine quando il tasto viene rilasciato
            }
        }
    }

    SDL_Scancode Input::lastPressed(SDL_Scancode keyA, SDL_Scancode keyB) const {
        bool aDown = m_keys[keyA];
        bool bDown = m_keys[keyB];

        // Se nessuno dei due è premuto, ritorna SDL_SCANCODE_UNKNOWN
        if (!aDown && !bDown) {
            return SDL_SCANCODE_UNKNOWN;
        }

        // Se solo uno è premuto, ritorna quello
        if (aDown && !bDown) {
            return keyA;
        }
        if (bDown && !aDown) {
            return keyB;
        }
        
        return (m_order[keyA] > m_order[keyB]) ? keyA : keyB; // Entrambi premuti — ritorna quello con premuto più di recente
    }
}