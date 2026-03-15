#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    // Gestisce la tastiera — aggiorna lo stato dei tasti ogni frame
    class Input {
        public:
            void update(bool& running); // Processa tutti gli eventi in coda e quindi va chiamato ad ogni frame, (ritorna false se l'utente chiude la finestra o preme ESC)

            // Ritorna true se il tasto è premuto in questo momento
            bool isKeyDown(SDL_Scancode key) const { return m_keys[key];}

        private:
            bool m_keys[SDL_NUM_SCANCODES] = {}; // Stato di ogni tasto (true = premuto, false = non premuto)
        };
}