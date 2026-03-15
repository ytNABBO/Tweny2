#include "AssetManager.h"
#include <iostream>

// Evita conflitti di nomi con altre librerie
namespace Tweny2 {
    Texture* AssetManager::loadTexture(SDL_Renderer* renderer, const std::string& name, const std::string& path) {
        // Controlla se la texture è già in cache — se sì, la restituisce senza ricaricarla
        auto it = m_textures.find(name);
        if (it != m_textures.end()) {
            std::cout << "AssetManager: texture '" << name << "' già in cache\n";
            return &it->second;
        }

        // La texture non è in cache — la carica dal disco
        Texture texture;
        if (!texture.load(renderer, path)) {
            std::cerr << "AssetManager: impossibile caricare '" << path << "'\n";
            return nullptr;
        }

        // Inserisce la texture in cache e restituisce il puntatore
        m_textures[name] = std::move(texture);

        return &m_textures[name];
    }

    Texture* AssetManager::getTexture(const std::string& name) {
        // Cerca la texture in cache e la restituisce se trovata
        auto it = m_textures.find(name);
        if (it != m_textures.end()) {
            return &it->second;
        }

        std::cerr << "AssetManager: texture '" << name << "' non trovata in cache\n";
        return nullptr;
    }
    
    void AssetManager::clear() {
        // Distrugge tutte le texture e svuota la cache
        for (auto& pair : m_textures) {
            pair.second.destroy();
        }

        m_textures.clear();
    }
}