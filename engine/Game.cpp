#include "Game.h"
#include <iostream>

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    bool Game::init(const char* title, int width, int height) {
        // Inizializza SDL con video e audio
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
            std::cerr << "SDL_Init error: " << SDL_GetError() << "\n";
            return false;
        }

        // Crea la finestra
        if (!m_window.create(title, width, height)) {
            SDL_Quit();
            return false;
        }

        // Crea il renderer collegato alla finestra
        if (!m_renderer.create(m_window)) {
            m_window.destroy();
            SDL_Quit();
            return false;
        }

        m_renderer.setBackgroundColor(0, 0, 0); // Colore di sfondo nero
        
        m_running = true;

        std::cout << "Tweny2 inizializzato.\n";
        return true;
    }

    void Game::run() {
        Uint64 lastTime = SDL_GetPerformanceCounter(); // Tempo del frame precedente
        const Uint64 perfFreq = SDL_GetPerformanceFrequency(); // Numero di "tick" al secondo (usato per calcolare deltaTime)

        // -------------------------------------------------------
        // GAME LOOP
        // -------------------------------------------------------
        while (m_running) {

            // Calcola il deltaTime in secondi
            Uint64 now = SDL_GetPerformanceCounter(); // Tempo attuale
            float deltaTime = static_cast<float>(now - lastTime) / static_cast<float>(perfFreq); // Tempo trascorso in secondi
            lastTime = now; // Aggiorna lastTime per il prossimo frame

            // Limita deltaTime per evitare salti se il gioco va in lag
            if (deltaTime > 0.05f) {
                deltaTime = 0.05f;
            }
            
            m_input.update(m_running); // Leggi input — aggiorna lo stato dei tasti e controlla la chiusura
            
            onUpdate(deltaTime); // Aggiorna logica — sovrascritta dalla classe figlia (il gioco)

            // Disegna — pulisce il frame, chiama onRender(), presenta il frame
            m_renderer.clear(); 
            onRender();
            m_renderer.present();

            // Frame cap — aspetta se il frame è stato troppo veloce
            float elapsed = static_cast<float>(SDL_GetPerformanceCounter() - now) / static_cast<float>(perfFreq) * 1000.0f;

            if (elapsed < FRAME_TIME) {
                SDL_Delay(static_cast<Uint32>(FRAME_TIME - elapsed));
            }
        }

        shutdown();
    }

    void Game::shutdown() {
        // Pulizia in ordine inverso rispetto alla creazione
        m_assets.clear();
        m_renderer.destroy();
        m_window.destroy();
        SDL_Quit();

        std::cout << "Tweny2 chiuso.\n";
    }
}