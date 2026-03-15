# Versione minima di CMake richiesta per usare questo file
# Se l'utente ha una versione più vecchia, CMake si ferma subito con un messaggio chiaro invece di fallire a metà compilazione
cmake_minimum_required(VERSION 3.16)

# Definisce il progetto:
# - Nome: Tweny2 (diventa anche il nome del .exe finale)
# - Version: 0.1.0 (major.minor.patch, utile per tracking)
# - LANGUAGES CXX (solo C++)
project(Tweny2 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17) # Imposta la versione dello standard C++ da usare (C++17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Se il compilatore non supporta C++17, CMake si ferma con errore

# Cerca SDL2 installata nel sistema (tramite MSYS2)
# Se la trova, CMake popola automaticamente due variabili:
# - SDL2_INCLUDE_DIRS: percorso degli header (.h cioé dichiarazione della funzione)
# - SDL2_LIBRARIES: percorso della libreria compilata (.dll / .lib cioé il codice della funzione)
# REQUIRED significa se non la trova, si ferma con errore
find_package(SDL2 REQUIRED)

# Crea l'eseguibile chiamato "Tweny2" compilando i file elencati
# Quando si aggiungono altri file .cpp all'engine, bisogna collegarli qui, uno per riga
add_executable(Tweny2
    game/main.cpp
    engine/Window.cpp
    engine/Renderer.cpp
    engine/Input.cpp
)

# Dice al compilatore dove trovare i file header di SDL2
# PRIVATE significa che questi "include" servono solo a Tweny2, non ad altri target
target_include_directories(Tweny2 PRIVATE ${SDL2_INCLUDE_DIRS})

# Collega la libreria SDL2 all'eseguibile.
# Il compilatore conosce già le funzioni SDL2 grazie agli header, ma senza questa riga non saprebbe dove trovare il codice che le esegue
# PRIVATE significa che la dipendenza è solo di Tweny2, non viene propagata ad altri
target_link_libraries(Tweny2 PRIVATE ${SDL2_LIBRARIES})

# Su Windows le librerie condivise sono file .dll che devono stare nella stessa cartella dell'eseguibile per poter essere trovate
# Questo comando copia SDL2.dll accanto a Tweny2.exe dopo ogni build
# "copy_if_different" evita copie inutili se il file non è cambiato
if(WIN32)
    add_custom_command(TARGET Tweny2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2> # Percorso sorgente: SDL2.dll di MSYS2
        $<TARGET_FILE_DIR:Tweny2> # Destinazione: cartella di Tweny2.exe
    )
endif()