#include "Tilemap.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    bool Tilemap::load(const std::string& mapPath, Texture* tileset, int tileSize, int tilesetCols) {
        m_tileset = tileset;
        m_tileSize = tileSize;
        m_tilesetCols = tilesetCols;
        m_map.clear();

        // Apre il file di testo della mappa
        std::ifstream file(mapPath);
        if (!file.is_open()) {
            std::cerr << "Tilemap::load error: impossibile aprire '" << mapPath << "'\n";
            return false;
        }
        
        // Legge la mappa riga per riga
        std::string line;
        while (std::getline(file, line)) {
            // Salta le righe vuote
            if (line.empty()) {
                continue;
            }

            std::vector<int> row;
            std::stringstream ss(line);
            std::string token;

            // Ogni riga è una serie di numeri separati da virgola
            while (std::getline(ss, token, ',')) {
                row.push_back(std::stoi(token));
            }

            m_map.push_back(row);
        }

        m_rows = (int)m_map.size();
        m_cols = m_rows > 0 ? (int)m_map[0].size() : 0;

        // Le tile solide di default sono quelle con ID > 0
        // ID 0 = tile vuota (nessun disegno, nessuna collisione)
        m_solidTiles = { 2 }; // ID 2 = muro solido
        std::cout << "Tilemap caricata: " << m_cols << "x" << m_rows << " tile\n";

        return true;
    }

    void Tilemap::draw(SDL_Renderer* renderer) {
        if (!m_tileset) {
            return;
        }

        for (int row = 0; row < m_rows; row++) {
            for (int col = 0; col < m_cols; col++) {
                int tileID = m_map[row][col];
                if (tileID == 0) { continue; } // Tile vuota — non disegnare nulla

                // Calcola la posizione della tile nel tileset
                // Il tileset è una griglia — ogni tile ha una riga e una colonna
                int tilesetRow = (tileID - 1) / m_tilesetCols; // -1 perché gli ID partono da 1
                int tilesetCol = (tileID - 1) % m_tilesetCols;

                // srcRect — ritaglio del tileset corrispondente a questo ID
                SDL_Rect srcRect = {
                    tilesetCol * m_tileSize,
                    tilesetRow * m_tileSize,
                    m_tileSize,
                    m_tileSize
                };

                // dstRect — posizione sullo schermo
                SDL_FRect dstRect = {
                    (float)(col * m_tileSize),
                    (float)(row * m_tileSize),
                    (float)m_tileSize,
                    (float)m_tileSize
                };

                SDL_RenderCopyF(renderer, m_tileset->getSDLTexture(), &srcRect, &dstRect); // Disegna la tile a schermo
            }
        }
    }

    bool Tilemap::isSolid(int tileID) const {
        for (int id : m_solidTiles) {
            if (id == tileID) { return true; }
        }

        return false;
    }

    bool Tilemap::collides(float x, float y, float w, float h) const {
        // Controlla tutte le tile che il rettangolo tocca
        int left = (int)(x / m_tileSize);
        int right = (int)((x + w - 1) / m_tileSize);
        int top = (int)(y / m_tileSize);
        int bottom = (int)((y + h - 1) / m_tileSize);

        // Clamp per non uscire dalla mappa
        left = SDL_max(0, left);
        right = SDL_min(m_cols - 1, right);
        top = SDL_max(0, top);
        bottom = SDL_min(m_rows - 1, bottom);

        // Controlla se almeno una delle tile toccate è solida
        for (int row = top; row <= bottom; row++) {
            for (int col = left; col <= right; col++) {
                if (isSolid(m_map[row][col])) {
                    return true; // Almeno una tile solida trovata
                }
            }
        }

        return false;
    }
}