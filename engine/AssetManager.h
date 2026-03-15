#pragma once // Evita che questo header venga incluso più volte nello stesso file

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include "Texture.h"

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    // Gestisce il caricamento e la cache delle texture
    class AssetManager {
        public:
            // Carica una texture dal disco e la salva in cache con un nome, (ritorna nullptr se il caricamento fallisce)
            // Se la texture è già in cache, non la ricarica e restituisce il puntatore alla texture esistente
            Texture* loadTexture(SDL_Renderer* renderer, const std::string& name, const std::string& path);

            Texture* getTexture(const std::string& name); // Restituisce una texture dalla cache tramite il suo nome, (ritorna nullptr se la texture non è in cache)

            void clear(); // Distrugge tutte le texture in cache e libera la memoria
        
        private:
            std::unordered_map<std::string, Texture> m_textures; // Struttura dati che associa una chiave a un valore e permette di trovare una texture per nome in tempo costante
    };
}