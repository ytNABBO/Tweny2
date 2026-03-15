#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    // Gestisce la visuale del gioco — segue il player con smooth lerp
    class Camera {
        public:
            // Configura la camera
            // screenW, screenH — dimensioni dello schermo
            // worldW, worldH — dimensioni del mondo (in px)
            // smoothSpeed — velocità di inseguimento
            void setup(int screenW, int screenH, int worldW, int worldH, float smoothSpeed = 5.0f);
            
            // Aggiorna la posizione della camera inseguendo il target con lerp
            // targetX, targetY — posizione del centro del player
            void update(float targetX, float targetY, float deltaTime);
            
            float getOffsetX() const { return m_x; } // Ritorna l'offset X da applicare a tutto quello che si disegna
            
            float getOffsetY() const { return m_y; } // Ritorna l'offset Y da applicare a tutto quello che si disegna

        private:
            // Posizione attuale della camera (angolo in alto a sinistra)
            float m_x = 0.0f;
            float m_y = 0.0f;

            int m_screenW = 800; // Larghezza dello schermo
            int m_screenH = 600; // Altezza dello schermo
            int m_worldW = 0; // Larghezza del mondo in pixel
            int m_worldH = 0; // Altezza del mondo in pixel
            float m_smoothSpeed = 5.0f; // Velocità di inseguimento
    };
}