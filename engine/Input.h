#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    // Gestisce la tastiera — aggiorna lo stato dei tasti ogni frame
    class Input {
        public:
            void update(bool& running);  // Processa tutti gli eventi in coda — va chiamata ogni frame
            
            bool isKeyDown(SDL_Scancode key) const { return m_keys[key]; } // Ritorna true se il tasto è premuto in questo momento
            
            SDL_Scancode lastPressed(SDL_Scancode keyA, SDL_Scancode keyB) const; // Ritorna l'ultimo tasto premuto tra i due

        private:
            bool m_keys[SDL_NUM_SCANCODES] = {}; // Stato di ogni tasto — true = premuto
            int m_order[SDL_NUM_SCANCODES] = {}; // Ordine di pressione — numero più alto = premuto più di recente
            int m_counter = 0;                   // Contatore globale — aumenta ad ogni tasto premuto
    };
}