#include "Window.h"
#include <iostream>

namespace Tweny2 {

bool Window::create(const std::string& title, int width, int height) {
    // Crea la finestra SDL con le opzioni standard dell'engine
    m_window = SDL_CreateWindow(
        title.c_str(),               // SDL vuole un const char*, .c_str() converte da std::string
        SDL_WINDOWPOS_CENTERED,      // centra orizzontalmente
        SDL_WINDOWPOS_CENTERED,      // centra verticalmente
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!m_window) {
        std::cerr << "Window::create error: " << SDL_GetError() << "\n";
        return false;
    }

    // Salva le dimensioni per uso futuro
    m_width  = width;
    m_height = height;

    return true;
}

void Window::destroy() {
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr; // Azzera il puntatore dopo la distruzione
    }
}

SDL_Window* Window::get() const {
    return m_window;
}

bool Window::isValid() const {
    return m_window != nullptr;
}

} // namespace Tweny2