#include "Input.h"

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    void Input::update(bool& running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) { // Estrae un evento dalla coda e lo mette in "event", ritorna 0 quando la coda è vuota

            // L'utente ha chiuso la finestra
            if (event.type == SDL_QUIT) {
                running = false;
            }

            // Un tasto è stato premuto
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    running = false;
                }
                
                m_keys[event.key.keysym.scancode] = true; // Segna il tasto come premuto nell'array
            }

            // Un tasto è stato rilasciato
            if (event.type == SDL_KEYUP) {
                m_keys[event.key.keysym.scancode] = false;
            }
        }
    }
}