#include "Texture.h"
#include <iostream>

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    bool Texture::load(SDL_Renderer* renderer, const std::string& path) {
        destroy(); // Distrugge la texture precedente se esiste
        
        SDL_Surface* surface = IMG_Load(path.c_str()); // IMG_Load carica l'immagine dal disco e la converte in una SDL_Surface (CPU)
        
        // Controlla se il caricamento dell'immagine è riuscito
        if (!surface) {
            std::cerr << "Texture::load error: " << IMG_GetError() << "\n";
            return false;
        }

        // SDL_CreateTextureFromSurface converte la Surface in una Texture (GPU)
        // Le texture sono più veloci da disegnare perché stanno nella memoria della GPU
        m_texture = SDL_CreateTextureFromSurface(renderer, surface);
        
        SDL_FreeSurface(surface); // La surface dopo aver creato la texture non serve più

        // Controlla se la creazione della texture è riuscita
        if (!m_texture) {
            std::cerr << "Texture::load SDL_CreateTextureFromSurface error: " << SDL_GetError() << "\n";
            return false;
        }
        
        SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height); // Salva le dimensioni della texture

        return true;
    }

    void Texture::draw(SDL_Renderer* renderer, float x, float y) {
        SDL_FRect dst = { x, y, (float)m_width, (float)m_height };
        SDL_RenderCopyF(renderer, m_texture, nullptr, &dst);
    }

    void Texture::drawScaled(SDL_Renderer* renderer, float x, float y, float w, float h) {
        SDL_FRect dst = { x, y, w, h };
        SDL_RenderCopyF(renderer, m_texture, nullptr, &dst);
    }

    void Texture::destroy() {
        if (m_texture) {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr; // Azzera il puntatore dopo la distruzione
            m_width   = 0;
            m_height  = 0;
        }
    }
}