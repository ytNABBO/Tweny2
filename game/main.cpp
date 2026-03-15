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
            // Salva posizione precedente
            float prevX = m_player.x;
            float prevY = m_player.y;

            // Calcola il movimento
            float moveX = 0.0f;
            float moveY = 0.0f;

            // Movimento orizzontale — last-input-wins
            SDL_Scancode hKey = m_input.lastPressed(SDL_SCANCODE_A, SDL_SCANCODE_D);
            if (hKey == SDL_SCANCODE_A) {
                moveX -= m_player.speed * deltaTime;
            }
            if (hKey == SDL_SCANCODE_D) {
                moveX += m_player.speed * deltaTime;
            }

            // Movimento verticale — last-input-wins
            SDL_Scancode vKey = m_input.lastPressed(SDL_SCANCODE_W, SDL_SCANCODE_S);
            if (vKey == SDL_SCANCODE_W) {
                moveY -= m_player.speed * deltaTime;
            }
            if (vKey == SDL_SCANCODE_S) {
                moveY += m_player.speed * deltaTime;
            }

            // Applica X e controlla
            m_player.x += moveX;
            m_player.x = SDL_clamp(m_player.x, 0.0f, (float)(800 - m_assets.getTexture("player")->getWidth()));
            Tweny2::AABB playerAABB = { m_player.x, m_player.y, (float)m_assets.getTexture("player")->getWidth(), (float)m_assets.getTexture("player")->getHeight() };
            
            if (Tweny2::checkCollision(playerAABB, m_wall)) {
                m_player.x = prevX;
            }

            // Applica Y e controlla
            m_player.y += moveY;
            m_player.y = SDL_clamp(m_player.y, 0.0f, (float)(600 - m_assets.getTexture("player")->getHeight()));
            playerAABB = { m_player.x, m_player.y, (float)m_assets.getTexture("player")->getWidth(), (float)m_assets.getTexture("player")->getHeight() };
            
            if (Tweny2::checkCollision(playerAABB, m_wall)) {
                m_player.y = prevY;
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