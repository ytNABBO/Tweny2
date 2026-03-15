#include <iostream>
#include "../engine/Game.h"
#include "../engine/Collision.h"

// -------------------------------------------------------
// MyGame — il gioco specifico costruito sopra Tweny2
// -------------------------------------------------------
struct Player {
    float x = 400.0f;
    float y = 300.0f;
    float speed = 200.0f;
};

class MyGame : public Tweny2::Game {
    public:
        // Chiamato una volta all'avvio — carica le risorse
        bool init(const char* title, int width, int height) {
            // Prima chiama init() della classe padre (Game)
            if (!Tweny2::Game::init(title, width, height)) {
                return false;
            }

            // Carica lo sprite del player dalla cartella assets
            if (!m_assets.loadTexture(m_renderer.get(), "player", "assets/player.png")) {
                return false;
            }

            return true;
        }

        // Sovrascrive onUpdate — logica del gioco
        void onUpdate(float deltaTime) override {
            // Movimento con WASD — l'asse Y è invertito (y decresce andando verso l'alto)
            if (m_input.isKeyDown(SDL_SCANCODE_W)) {
                m_player.y -= m_player.speed * deltaTime;
            }

            if (m_input.isKeyDown(SDL_SCANCODE_S)) {
                m_player.y += m_player.speed * deltaTime;
            }

            if (m_input.isKeyDown(SDL_SCANCODE_A)) {
                m_player.x -= m_player.speed * deltaTime;
            }

            if (m_input.isKeyDown(SDL_SCANCODE_D)) {
                m_player.x += m_player.speed * deltaTime;
            }

            // Impedisce al player di uscire dalla finestra
            m_player.x = SDL_clamp(m_player.x, 0.0f, (float)(800 - m_assets.getTexture("player")->getWidth())); // 800 è la larghezza della finestra, getWidth() è la larghezza dello sprite del player
            m_player.y = SDL_clamp(m_player.y, 0.0f, (float)(600 - m_assets.getTexture("player")->getHeight())); // 600 è l'altezza della finestra, getHeight() è l'altezza dello sprite del player
            
            // Hitbox del player
            Tweny2::AABB playerAABB = {
                m_player.x, m_player.y,
                (float)m_assets.getTexture("player")->getWidth(),
                (float)m_assets.getTexture("player")->getHeight()
            };

            // Controlla la collisione con il muro
            if (Tweny2::checkCollision(playerAABB, m_wall)) {
                std::cout << "Collisione con il muro!\n";
            }
        }
        
        // Sovrascrive onRender — disegno del gioco
        void onRender() override {
            m_assets.getTexture("player")->draw(m_renderer.get(), m_player.x, m_player.y); // Disegna lo sprite del player nella posizione x,y
            
            Tweny2::drawAABB(m_renderer.get(), m_wall); // Disegna il muro e le hitbox per debug
        }

    private:
        Player m_player; // Stato del player

        // Muro al centro dello schermo
        Tweny2::AABB m_wall = {
            350.0f, 200.0f, 80.0f, 80.0f
        };
};

// -------------------------------------------------------
// MAIN — crea il gioco e lo avvia
// -------------------------------------------------------
int main(int argc, char* argv[]) {
    MyGame game;

    if (!game.init("Tweny2", 800, 600)) {
        return 1;
    }

    game.run(); // Avvia il loop — ritorna quando l'utente chiude il gioco

    return 0;
}