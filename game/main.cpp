#include "../engine/Game.h"

// -------------------------------------------------------
// MyGame — il gioco specifico costruito sopra Tweny2
// Eredita da Tweny2::Game e sovrascrive onUpdate e onRender
// -------------------------------------------------------
struct Player {
    float x     = 400.0f;
    float y     = 300.0f;
    float speed = 200.0f;
};

class MyGame : public Tweny2::Game {
    public:
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
            m_player.x = SDL_clamp(m_player.x, 16.0f, 784.0f); // La finestra è 800px, il player è largo 32px, quindi lo limito tra 16 e 784 per tenerlo dentro
            m_player.y = SDL_clamp(m_player.y, 16.0f, 584.0f); // La finestra è 600px, il player è alto 32px, quindi lo limito tra 16 e 584 per tenerlo dentro
        }

        // Sovrascrive onRender — disegno del gioco
        void onRender() override {
            // Disegna il player — quadrato 32x32 centrato su x,y
            m_renderer.setDrawColor(220, 220, 255);
            m_renderer.fillRect(m_player.x - 16.0f, m_player.y - 16.0f, 32.0f, 32.0f); // Il player è un quadrato 32x32, quindi lo disegno spostato di 16 pixel per centrarlo su x,y
        }

    private:
        Player m_player; // Stato del player
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