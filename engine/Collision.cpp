#include "Collision.h"

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    bool checkCollision(const AABB& a, const AABB& b) {
        // Se anche solo una condizione è falsa, non c'è collisione

        // A è completamente a sinistra di B
        if (a.x + a.w <= b.x) {
            return false;
        }
        // A è completamente a destra di B
        if (a.x >= b.x + b.w) {
            return false;
        }

        // A è completamente sopra B
        if (a.y + a.h <= b.y) {
            return false;
        }

        // A è completamente sotto B
        if (a.y >= b.y + b.h) {
            return false;
        }

        return true; // Nessuna condizione di separazione trovata
    }
    void drawAABB(SDL_Renderer* renderer, const AABB& aabb) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
        
        SDL_FRect rect = {
            aabb.x, aabb.y, aabb.w, aabb.h
        };

        SDL_RenderDrawRectF(renderer, &rect); // Disegna solo il bordo, non il riempimento
    }
}