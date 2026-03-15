#include "../engine/Game.h"
#include "../engine/Texture.h"

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
            if (!m_playerTexture.load(m_renderer.get(), "assets/player.png")) {
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
            m_player.x = SDL_clamp(m_player.x, 0.0f, (float)(800 - m_playerTexture.getWidth())); // 800 è la larghezza della finestra, getWidth() è la larghezza del player
            m_player.y = SDL_clamp(m_player.y, 0.0f, (float)(600 - m_playerTexture.getHeight())); // 600 è l'altezza della finestra, getHeight() è l'altezza del player
        }

        // Sovrascrive onRender — disegno del gioco
        void onRender() override {
            // Disegna lo sprite del player nella posizione x,y
            m_playerTexture.draw(m_renderer.get(), m_player.x, m_player.y);
        }

    private:
        Player m_player; // Stato del player
        Tweny2::Texture m_playerTexture; // Sprite del player
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