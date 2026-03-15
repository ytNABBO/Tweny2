#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "Texture.h"

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    // Gestisce una mappa di tile — caricamento, disegno e collisioni
    class Tilemap {
        public:
            // Carica la mappa da un file di testo e il tileset da un'immagine
            // tileSize — dimensione di ogni tile in px
            // tilesetCols — numero di colonne nel tileset
            bool load(const std::string& mapPath, Texture* tileset, int tileSize, int tilesetCols);
            
            void draw(SDL_Renderer* renderer, float offsetX = 0.0f, float offsetY = 0.0f); // Disegna tutta la mappa a schermo
            
            bool isSolid(int tileID) const; // Ritorna true se la tile in quella posizione è solida (blocca il movimento)
            
            bool collides(float x, float y, float w, float h) const; // Ritorna true se il rettangolo AABB collide con una tile solida
            
            int getWidthPixels()  const { return m_cols * m_tileSize; } // Ritorna la larghezza della mappa in px
            
            int getHeightPixels() const { return m_rows * m_tileSize; } // Ritorna l'altezza della mappa in px

        private:
            std::vector<std::vector<int>> m_map; // Matrice 2D di ID tile
            Texture* m_tileset = nullptr; // Tileset — puntatore alla texture (non la possiede)
            int m_tileSize = 32; // Dimensione di ogni tile in pixel
            int m_tilesetCols = 1; // Numero di colonne nel tileset
            int m_rows = 0; // Numero di righe della mappa
            int m_cols = 0; // Numero di colonne della mappa

            // ID tile considerati solidi — il player non può attraversarli
            // 0 = tile vuota (trasparente), gli altri dipendono dal tileset
            std::vector<int> m_solidTiles;
    };
}