#include <iostream>
#include "../engine/core/Game.h"
#include "../engine/graphics/Animation.h"
#include "../engine/graphics/Tilemap.h"
#include "../engine/graphics/Camera.h"
#include "../engine/physics/Collision.h"

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
            // Carica il tileset e la mappa
            if (!m_assets.loadTexture(m_renderer.get(), "tileset", "assets/tileset.png")) {
                return false;
            }
            
            if (!m_tilemap.load("assets/map.txt", m_assets.getTexture("tileset"), 32, 3)) {
                return false;
            }
            
            m_camera.setup(800, 600, m_tilemap.getWidthPixels(), m_tilemap.getHeightPixels(), 5.0f); // Configura la camera

            return true;
        }
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

            // Applica X e controlla collisione con tilemap
            m_player.x += moveX;
            m_player.x = SDL_clamp(m_player.x, 0.0f, (float)(m_tilemap.getWidthPixels() - 64));
            if (m_tilemap.collides(m_player.x, prevY, 64.0f, 96.0f)) {
                m_player.x = prevX;
            }

            // Applica Y e controlla collisione con tilemap
            m_player.y += moveY;
            m_player.y = SDL_clamp(m_player.y, 0.0f, (float)(m_tilemap.getHeightPixels() - 96));
            if (m_tilemap.collides(m_player.x, m_player.y, 64.0f, 96.0f)) {
                m_player.y = prevY;
            }

            // Anima solo se il player si sta muovendo
            if (moveX != 0.0f || moveY != 0.0f) {
                m_walkAnim.setPaused(false);
            } else {
                m_walkAnim.setPaused(true);
            }

            m_walkAnim.update(deltaTime);
            
            m_camera.update(m_player.x + 32.0f, m_player.y + 48.0f, deltaTime); // Aggiorna la camera — insegue il centro del player
        }

        void onRender() override {
            m_tilemap.draw(m_renderer.get(), m_camera.getOffsetX(), m_camera.getOffsetY());
            m_walkAnim.draw(m_renderer.get(), m_player.x - m_camera.getOffsetX(), m_player.y - m_camera.getOffsetY());
        }
        
    private:
        Player m_player;
        Tweny2::Animation m_walkAnim; // Animazione di camminata
        Tweny2::Tilemap m_tilemap; // Mappa di gioco
        Tweny2::Camera m_camera; // Camera del gioco
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