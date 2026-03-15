#include "Renderer.h"
#include <iostream>

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    bool Renderer::create(Window& window) {
        m_renderer = SDL_CreateRenderer(
            window.get(),
            -1, // Usa il primo driver disponibile
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // Usa la GPU e sincronizza con il refresh del monitor
        );

        // Controlla se la creazione è fallita
        if (!m_renderer) {
            std::cerr << "Renderer::create error: " << SDL_GetError() << "\n";
            return false;
        }

        return true;
    }

    void Renderer::destroy() {
        if (m_renderer) {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr; // Azzera il puntatore dopo la distruzione
        }
    }

    void Renderer::clear() {
        SDL_SetRenderDrawColor(m_renderer, m_bgR, m_bgG, m_bgB, m_bgA);
        SDL_RenderClear(m_renderer);
    }

    void Renderer::present() {
        SDL_RenderPresent(m_renderer);
    }

    void Renderer::setBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        m_bgR = r;
        m_bgG = g;
        m_bgB = b;
        m_bgA = a;
    }

    void Renderer::setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }

    void Renderer::fillRect(float x, float y, float w, float h) {
        SDL_FRect rect = { x, y, w, h }; // Crea un rettangolo con le coordinate e dimensioni specificate
        SDL_RenderFillRectF(m_renderer, &rect);
    }
}