#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    // Rettangolo AABB — definisce la hitbox di un oggetto
    struct AABB {
        float x = 0.0f; // Posizione orizzontale dell'angolo in alto a sinistra
        float y = 0.0f; // Posizione verticale dell'angolo in alto a sinistra
        float w = 0.0f; // Larghezza
        float h = 0.0f; // Altezza
    };
    
    bool checkCollision(const AABB& a, const AABB& b); // Controlla se due rettangoli AABB si sovrappongono, (ritorna true se c'è collisione)
    
    void drawAABB(SDL_Renderer* renderer, const AABB& aabb); // Disegna il rettangolo AABB a schermo (utile per debug)
}