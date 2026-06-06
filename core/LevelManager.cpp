#include "LevelManager.hpp"

std::vector<std::vector<int>> LevelManager::get_level(int level_num) {
    switch (level_num) {
        case 1: return create_level_1();
        default: return create_level_2();
    }
}

std::vector<std::vector<int>> LevelManager::create_level_1() {
    // --- ŚCIĄGAWKA DLA PROJEKTANTA ---
    // 3   - Grass (Trawa / Ściana)
    // 10  - Dirt środek | 20  - Dirt Dark środek | 30  - Area środek
    // 11x - Dirt krawędź| 21x - Dark krawędź     | 31x - Area krawędź
    // 12x - Dirt rog     | 22x - Dark róg         | 32x - Area róg
    // 13x - Dirt tunel   | 23x - Dark tunel       | 33x - Area tunel
    // Końcówki 'x' (rotacja): 0 = góra/TL, 1 = prawo/TR, 2 = dół/BR, 3 = lewo/BL

    std::vector<std::vector<int>> first = {
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,320,310,321,3,3,3,3,3,3,3,3,3,3,220,131,310,310,321,3},
        {3,313,30,311,3,220,110,210,110,210,110,210,110,210,111,3,313,30,311,3},
        {3,313,30,311,3,113,20,10,20,10,20,10,20,10,211,3,313,30,311,3},
        {3,313,30,311,3,213,10,20,10,20,10,20,10,20,111,3,313,30,311,3},
        {3,313,30,311,3,113,212,112,212,112,212,112,212,112,222,3,313,30,311,3},
        {3,323,312,312,131,222,3,3,3,3,3,3,3,3,3,3,323,312,322,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}


    };
    return first;
}

std::vector<std::vector<int>> LevelManager::create_level_2() {
    // Miejsce na kolejny poziom w przyszłości
    return create_level_1();
}