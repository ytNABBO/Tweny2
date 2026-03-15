#include <SDL2/SDL.h>
#include <iostream>
#include "../engine/Window.h"
#include "../engine/Renderer.h"
#include "../engine/Input.h"

// -------------------------------------------------------
// COSTANTI DI CONFIGURAZIONE
// -------------------------------------------------------
static constexpr int WINDOW_W = 800;
static constexpr int WINDOW_H = 600;
static constexpr float TARGET_FPS = 60.0f;
static constexpr float FRAME_TIME = 1000.0f / TARGET_FPS;

// -------------------------------------------------------
// STRUTTURA PLAYER
// -------------------------------------------------------
struct Player {
    float x = WINDOW_W / 2.0f;
    float y = WINDOW_H / 2.0f;
    float speed = 200.0f;
};

// -------------------------------------------------------
// UPDATE — aggiorna la logica del gioco
// -------------------------------------------------------
void update(Player& player, const Tweny2::Input& input, float deltaTime) {
    // L'asse Y è invertito — y decresce andando verso l'alto
    if (input.isKeyDown(SDL_SCANCODE_W)) {
        player.y -= player.speed * deltaTime;
    }

    if (input.isKeyDown(SDL_SCANCODE_S)) {
        player.y += player.speed * deltaTime;
    }

    if (input.isKeyDown(SDL_SCANCODE_A)) {
        player.x -= player.speed * deltaTime;
    }

    if (input.isKeyDown(SDL_SCANCODE_D)) {
        player.x += player.speed * deltaTime;
    }

    // Impedisce al player di uscire dalla finestra
    // -16 perché il player è 32x32 e x,y sono al centro
    player.x = SDL_clamp(player.x, 16.0f, (float)(WINDOW_W - 16));
    player.y = SDL_clamp(player.y, 16.0f, (float)(WINDOW_H - 16));
}

// -------------------------------------------------------
// RENDER — disegna tutto a schermo
// -------------------------------------------------------
void render(Tweny2::Renderer& renderer, const Player& player) {
    renderer.clear(); // Pulisce il frame con il colore di sfondo

    // Disegna il player — quadrato 32x32 centrato su x,y
    renderer.setDrawColor(220, 220, 255);
    renderer.fillRect(player.x - 16.0f, player.y - 16.0f, 32.0f, 32.0f);

    renderer.present(); // Presenta il frame a schermo
}

// -------------------------------------------------------
// MAIN
// -------------------------------------------------------
int main(int argc, char* argv[]) {

    // Inizializza SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << "\n";
        return 1;
    }

    // Crea la finestra tramite il modulo Window dell'engine
    Tweny2::Window window;
    if (!window.create("Tweny2", WINDOW_W, WINDOW_H)) {
        SDL_Quit();
        return 1;
    }

    // Crea il renderer tramite il modulo Renderer dell'engine
    Tweny2::Renderer renderer;
    if (!renderer.create(window)) {
        window.destroy();
        SDL_Quit();
        return 1;
    }

    // Imposta il colore di sfondo
    renderer.setBackgroundColor(18, 18, 24);

    // Crea il modulo Input
    Tweny2::Input input;

    // Crea il player con i valori di default
    Player player;

    bool running = true;

    Uint64 lastTime = SDL_GetPerformanceCounter();
    const Uint64 perfFreq = SDL_GetPerformanceFrequency();

    std::cout << "Tweny2 avviato. WASD per muoversi, ESC per uscire.\n";

    // -------------------------------------------------------
    // GAME LOOP
    // -------------------------------------------------------
    while (running) {

        // Calcola il deltaTime in secondi
        Uint64 now = SDL_GetPerformanceCounter();
        float deltaTime = static_cast<float>(now - lastTime) / static_cast<float>(perfFreq);
        lastTime = now;

        // Limita deltaTime per evitare salti enormi se il gioco va in lag
        if (deltaTime > 0.05f) {
            deltaTime = 0.05f;
        }

        // Le tre fasi del loop
        input.update(running);  // 1. leggi input
        update(player, input, deltaTime); // 2. aggiorna logica
        render(renderer, player); // 3. disegna

        // Frame cap — aspetta se il frame è stato troppo veloce
        float elapsed = static_cast<float>(SDL_GetPerformanceCounter() - now)  / static_cast<float>(perfFreq) * 1000.0f;

        if (elapsed < FRAME_TIME) {
            SDL_Delay(static_cast<Uint32>(FRAME_TIME - elapsed));
        }
    }

    // -------------------------------------------------------
    // PULIZIA — in ordine inverso rispetto alla creazione
    // -------------------------------------------------------
    renderer.destroy();
    window.destroy();
    SDL_Quit();

    return 0;
}