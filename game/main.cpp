#include <iostream>
#include <SDL2/SDL.h> // Include il file header di SDL2 — contiene le dichiarazioni di tutte le funzioni SDL

// -------------------------------------------------------
// COSTANTI DI CONFIGURAZIONE
// "constexpr" significa che il valore è calcolato a compile time, non a runtime
// "static" significa che esistono solo in questo file
// -------------------------------------------------------
static constexpr int WINDOW_W = 800; // Larghezza finestra in pixel
static constexpr int WINDOW_H = 600; // Altezza finestra in pixel
static constexpr float TARGET_FPS = 60.0f; // Frame al secondo minimi accettabili
static constexpr float FRAME_TIME = 1000.0f / TARGET_FPS; // Millisecondi per frame

// -------------------------------------------------------
// STRUTTURA PLAYER
// Una "struct" raggruppa dati correlati in un unico oggetto
// -------------------------------------------------------
struct Player {
    float x = WINDOW_W / 2.0f; // Posizione orizzontale
    float y = WINDOW_H / 2.0f; // Posizione verticale
    float speed = 200.0f;      // Velocità in pixel al secondo
};

// -------------------------------------------------------
// FASE 1 DEL LOOP: processInput()
// Legge tutti gli eventi in coda (tastiera, mouse, chiusura finestra) e aggiorna lo stato di "running" e dell'array "keys"
//
// "running" controlla se il game loop deve continuare a girare
// "bool keys[]" contiene un valore per tasto possibile
// -------------------------------------------------------
void processInput(bool& running, bool keys[SDL_NUM_SCANCODES]) {
    SDL_Event event; // Struttura che SDL riempie con le info sull'evento

    // SDL_PollEvent estrae un evento dalla coda e lo mette in "event"
    // Ritorna 0 quando la coda è vuota — il while processa tutti gli eventi accumulati
    while (SDL_PollEvent(&event)) {

        // L'utente ha chiuso la finestra
        if (event.type == SDL_QUIT) {
            running = false;
        }

        // Un tasto è stato premuto
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) { // ESC chiude il gioco
                running = false;
            }

            // "scancode" identifica il tasto fisico indipendentemente dalla lingua della tastiera
            keys[event.key.keysym.scancode] = true; // Segna il tasto come premuto nell'array
        }

        // Un tasto è stato rilasciato
        if (event.type == SDL_KEYUP) {
            keys[event.key.keysym.scancode] = false; // Segna il tasto come non premuto nell'array
        }
    }
}

// -------------------------------------------------------
// FASE 2 DEL LOOP: update()
// Aggiorna la logica del gioco in base agli input e al tempo trascorso.
//
// "deltaTime" è il tempo in secondi dall'ultimo frame (es. 0.016 a 60fps).
// Moltiplicare la velocità per deltaTime rende il movimento indipendente
// dal framerate — il player si muove alla stessa velocità su qualsiasi PC.
// -------------------------------------------------------
void update(Player& player, const bool keys[SDL_NUM_SCANCODES], float deltaTime) {
    // L'asse y è invertito rispetto al classico grafico matematico
    
    if (keys[SDL_SCANCODE_W]) { // W
        player.y -= player.speed * deltaTime;
    }
    
    if (keys[SDL_SCANCODE_S]) { // S
        player.y += player.speed * deltaTime;
    }
    
    if (keys[SDL_SCANCODE_A]) { // A
        player.x -= player.speed * deltaTime;
    }
    
    if (keys[SDL_SCANCODE_D]) { // D
        player.x += player.speed * deltaTime;
    }

    // SDL_clamp(valore, minimo, massimo) — impedisce al player di uscire dalla finestra
    // Il player è un quadrato di 32px quindi il -16 serve per evitare che vada per metà fuori (dato che x e y sono nel centro sono distanti entrambi 16px dal bordo del player)
    player.x = SDL_clamp(player.x, 16.0f, (float)(WINDOW_W - 16));
    player.y = SDL_clamp(player.y, 16.0f, (float)(WINDOW_H - 16));
}

// -------------------------------------------------------
// FASE 3 DEL LOOP: render()
// Disegna tutto sullo schermo
// SDL usa il "double buffering": disegna su un buffer nascosto, poi lo scambia con quello visibile tutto in una volta questo evita il flickering
// -------------------------------------------------------
void render(SDL_Renderer* renderer, const Player& player) {
    SDL_SetRenderDrawColor(renderer, 18, 18, 24, 255); // Colore di sfondo (R, G, B, Trasparenza)
    SDL_RenderClear(renderer); // Cancella tutto il frame precedente e riempe quello attuale con il colore impostato

    // SDL_FRect definisce un rettangolo con coordinate float: {x, y, larghezza, altezza}
    // Sottraiamo 16 a x e y per centrare il rettangolo sulla posizione del player
    SDL_FRect rect = {
        // Angolo in alto a sinistra del quadrato
        player.x - 16.0f,
        player.y - 16.0f,

        32.0f, // Larghezza player
        32.0f // Altezza player
    };
    
    SDL_SetRenderDrawColor(renderer, 220, 220, 255, 255); // Imposta il colore del player
    SDL_RenderFillRectF(renderer, &rect); // Riempe lo sprite del colore scelto

    SDL_RenderPresent(renderer); // Scambia il buffer nascosto con quello visibile
}

// -------------------------------------------------------
// Main
// -------------------------------------------------------
int main(int argc, char* argv[]) {
    // Inizializzazione SDL
    // SDL_INIT_VIDEO apre il sottosistema grafico, SDL_INIT_AUDIO quello audio
    // Se fallisce, ritorna un valore diverso da 0
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << "\n";
        return 1; // Termina il programma con codice di errore
    }

    // Crea la finestra del gioco
    // SDL_WINDOWPOS_CENTERED: centra la finestra sullo schermo (sia per x che per y)
    // SDL_WINDOW_SHOWN: mostra la finestra subito
    // SDL_WINDOW_RESIZABLE: l'utente può ridimensionarla
    SDL_Window* window = SDL_CreateWindow("Tweny2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    // Se la creazione fallisce, va in errore
    if (!window) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // Crea il renderer (l'oggetto che gestisce il disegno sulla finestra)
    // -1: usa il primo driver disponibile
    // SDL_RENDERER_ACCELERATED: usa la GPU invece della CPU per disegnare
    // SDL_RENDERER_PRESENTVSYNC: si sincronizza con il refresh del monitor
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Se il render fallisce, va in errore
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window); // Pulisce la finestra creata prima di uscire
        SDL_Quit();
        return 1;
    }

    Player player; // Crea il player con i valori di default definiti nella struct

    // Array di booleani per lo stato di ogni tasto (tutti false all'inizio)
    // SDL_NUM_SCANCODES è il numero totale di tasti possibili definito da SDL
    bool keys[SDL_NUM_SCANCODES] = {};
    
    bool running = true; // Controlla se il gioco deve continuare ad andare

    
    Uint64 lastTime = SDL_GetPerformanceCounter(); // Restituisce un contatore ad alta precisione in tick (usato per misurare il tempo trascorso tra un frame e l'altro)

    const Uint64 perfFreq = SDL_GetPerformanceFrequency(); // Restituisce quanti tick ci sono in un secondo (tick trascorsi / frequenza = deltaTime)

    std::cout << "Engine avviato. WASD, ESC per uscire.\n";

    // -------------------------------------------------------
    // GAME LOOP
    // Gira continuamente finché "running" è true
    // Ogni iterazione è un frame
    // -------------------------------------------------------
    while (running) {
        // Legge il contatore attuale e calcola quanti secondi sono passati dall'ultimo frame (deltaTime)
        Uint64 now = SDL_GetPerformanceCounter();
        float deltaTime = static_cast<float>(now - lastTime) / static_cast<float>(perfFreq);
        lastTime = now; // Aggiorna per il prossimo frame

        // Se deltaTime supera 50ms lo limitiamo per evitare errori nella logica di gioco
        if (deltaTime > 0.05f) {
            deltaTime = 0.05f;
        }

        // Le tre fasi del loop
        processInput(running, keys); // Leggi input
        update(player, keys, deltaTime); // Aggiorna logica
        render(renderer, player); // Disegna

        // Se il frame è stato più veloce di FRAME_TIME, aspetta il tempo rimanente per non sprecare CPU inutilmente
        float elapsed = static_cast<float>(SDL_GetPerformanceCounter() - now) / static_cast<float>(perfFreq) * 1000.0f;
        if (elapsed < FRAME_TIME) {
            SDL_Delay(static_cast<Uint32>(FRAME_TIME - elapsed));
        }
    }

    // -------------------------------------------------------
    // PULIZIA
    // Renderer, finestra, SDL
    // -------------------------------------------------------
    SDL_DestroyRenderer(renderer); // Libera la memoria del renderer
    SDL_DestroyWindow(window); // Chiude la finestra
    SDL_Quit(); // Chiude SDL

    return 0;
}