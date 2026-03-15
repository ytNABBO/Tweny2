#include "Animation.h"

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    void Animation::setup(Texture* texture, int frameCount, float frameTime) {
        m_texture = texture;
        m_frameCount = frameCount;
        m_frameTime = frameTime;
        m_currentFrame = 0;
        m_timer = 0.0f;
    }

    void Animation::update(float deltaTime) {
        // Se l'animazione è in pausa o non c'è una texture, non fare nulla
        if (m_paused || !m_texture) {
            return;
        }

        m_timer += deltaTime;

        // Quando il timer supera frameTime, avanza al frame successivo
        if (m_timer >= m_frameTime) {
            m_timer = 0.0f;
            m_currentFrame = (m_currentFrame + 1) % m_frameCount; // % frameCount per tornare al primo frame dopo l'ultimo
        }
    }

    void Animation::draw(SDL_Renderer* renderer, float x, float y) {
        // Se non c'è una texture, non disegnare nulla
        if (!m_texture) {
            return;
        }

        // Larghezza di un singolo frame = larghezza totale / numero di frame
        int frameWidth = m_texture->getWidth() / m_frameCount;
        int frameHeight = m_texture->getHeight();

        // Il ritaglio dello spritesheet corrispondente al frame corrente
        SDL_Rect srcRect = {
            m_currentFrame * frameWidth, // x = frame corrente * larghezza di un frame
            0,
            frameWidth,
            frameHeight
        };

        // Dove disegnare sullo schermo
        SDL_FRect dstRect = {
            x,
            y,
            (float)frameWidth,
            (float)frameHeight
        };
        
        SDL_RenderCopyF(renderer, m_texture->getSDLTexture(), &srcRect, &dstRect);
    }

    void Animation::reset() {
        m_currentFrame = 0;
        m_timer = 0.0f;
    }
}