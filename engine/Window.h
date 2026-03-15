#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>
#include <string>

namespace Tweny2 { // Namespace dell'engine — evita conflitti di nomi con altre librerie

// Gestisce la finestra SDL — creazione, distruzione e accesso al puntatore interno
class Window {
public:
    // Crea la finestra con titolo, larghezza e altezza
    // Ritorna false se la creazione fallisce
    bool create(const std::string& title, int width, int height);

    // Distrugge la finestra e libera la memoria
    void destroy();

    // Ritorna il puntatore alla finestra SDL (usato dal Renderer)
    SDL_Window* get() const;

    // Ritorna true se la finestra è stata creata correttamente
    bool isValid() const;

private:
    SDL_Window* m_window = nullptr; // Puntatore alla finestra SDL (nullptr = non creata)
    int m_width  = 0;
    int m_height = 0;
};

} // namespace Tweny2