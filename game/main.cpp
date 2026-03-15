#include <iostream>
#include "../engine/Game.h"
#include "../engine/Collision.h"
#include "../engine/Animation.h"
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
            if (!Tweny2::Game::init(title, width, height)) {
                return false;
            }

            // Carica lo spritesheet di camminata
            if (!m_assets.loadTexture(m_renderer.get(), "player_walk", "assets/player_walk.png")) {
                return false;
            }

            // Configura l'animazione — 4 frame, 0.15s per frame
            m_walkAnim.setup(m_assets.getTexture("player_walk"), 4, 0.15f);

            return true;
        }

        // Sovrascrive onUpdate — logica del gioco
        void onUpdate(float deltaTime) override {
            float prevX = m_player.x;
            float prevY = m_player.y;
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

            // Applica X e controlla collisione
            m_player.x += moveX;
            m_player.x = SDL_clamp(m_player.x, 0.0f, 736.0f);
            Tweny2::AABB playerAABB = { m_player.x, m_player.y, 64.0f, 96.0f };
            if (Tweny2::checkCollision(playerAABB, m_wall)) {
                m_player.x = prevX;
            }

            // Applica Y e controlla collisione
            m_player.y += moveY;
            m_player.y = SDL_clamp(m_player.y, 0.0f, 504.0f);
            playerAABB = { m_player.x, m_player.y, 64.0f, 96.0f };
            if (Tweny2::checkCollision(playerAABB, m_wall)) {
                m_player.y = prevY;
            }

            // Anima solo se il player si sta muovendo
            if (moveX != 0.0f || moveY != 0.0f) {
                m_walkAnim.setPaused(false);
            } else {
                m_walkAnim.setPaused(true);
            }

            m_walkAnim.update(deltaTime);
        }
        // Sovrascrive onRender — disegno del gioco
        void onRender() override {
            m_walkAnim.draw(m_renderer.get(), m_player.x, m_player.y); // Disegna il frame corrente dell'animazione
            Tweny2::drawAABB(m_renderer.get(), m_wall); // Disegna il muro per debug
        }

    private:
        Player m_player;
        Tweny2::Animation m_walkAnim; // Animazione di camminata
        Tweny2::AABB m_wall = { 350.0f, 200.0f, 80.0f, 80.0f };
};

// -------------------------------------------------------
// MAIN
// -------------------------------------------------------
int main(int argc, char* argv[]) {
    MyGame game;
    if (!game.init("Tweny2", 800, 600)) {
        return 1;
    }
    game.run();
    return 0;
}