#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>
#include "../core/Window.h"
#include "../graphics/Renderer.h"
#include "../input/Input.h"
#include "../assets/AssetManager.h"
#include "../graphics/Texture.h"

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    // Classe principale dell'engine — gestisce init, loop e shutdown
    class Game {
        public:
            bool init(const char* title, int width, int height); // Inizializza SDL, finestra, renderer e input, (ritorna false se qualcosa fallisce)
            
            void run(); // Avvia il game loop — gira finché running è false
            
            void quit() { m_running = false;} // Ferma il game loop
            
            void shutdown(); // Distrugge tutto e libera la memoria

            void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) { m_renderer.setBackgroundColor(r, g, b, a); } // Imposta il colore di sfondo (opzionale alpha, default 255)

        protected:
            // Queste funzioni vengono chiamate dal loop ogni frame
            virtual void onUpdate(float deltaTime) {}
            virtual void onRender() {}

            Window m_window; // Finestra SDL
            Renderer m_renderer; // Renderer SDL
            Input m_input; // Input tastiera
            AssetManager m_assets; // Gestisce il caricamento e la cache delle texture

        private:
            bool m_running = false; // Controlla se il game loop deve continuare

            static constexpr float TARGET_FPS  = 60.0f;
            static constexpr float FRAME_TIME  = 1000.0f / TARGET_FPS;
    };
}