#include "Camera.h"

namespace Tweny2 {
    void Camera::setup(int screenW, int screenH, int worldW, int worldH, float smoothSpeed) {
        m_screenW = screenW;
        m_screenH = screenH;
        m_worldW = worldW;
        m_worldH = worldH;
        m_smoothSpeed = smoothSpeed;
        m_x = 0.0f;
        m_y = 0.0f;
    }

    void Camera::update(float targetX, float targetY, float deltaTime) {
        // Calcola la posizione ideale — player al centro dello schermo
        float idealX = targetX - m_screenW / 2.0f;
        float idealY = targetY - m_screenH / 2.0f;

        // Avvicina la camera alla posizione ideale gradualmente
        m_x += (idealX - m_x) * m_smoothSpeed * deltaTime;
        m_y += (idealY - m_y) * m_smoothSpeed * deltaTime;

        // Impedisce alla camera di uscire dai bordi del mondo
        m_x = SDL_clamp(m_x, 0.0f, (float)(m_worldW - m_screenW));
        m_y = SDL_clamp(m_y, 0.0f, (float)(m_worldH - m_screenH));
    }
}