#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>
#include <string>

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    // Gestisce la finestra SDL — creazione, distruzione e accesso al puntatore interno
    class Window {
        public:
            bool create(const std::string& title, int width, int height); // Crea la finestra con titolo, larghezza e altezza (ritorna false se la creazione fallisce)

            void destroy(); // Distrugge la finestra e libera la memoria

            SDL_Window* get() const; // Ritorna il puntatore alla finestra SDL (usato dal Renderer)

            bool isValid() const; // Ritorna true se la finestra è stata creata correttamente

        private:
            SDL_Window* m_window = nullptr; // Puntatore alla finestra SDL (nullptr = non creata)
            int m_width  = 0;
            int m_height = 0;
    };

    }