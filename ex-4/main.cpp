#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

struct character{
    bool isAlive = true;
    std::string name;
    int hp, armor, damage, posX, posY;
};

bool isPositiveNumber(std::string sum){
    if (sum[0] == '-'){
        std::cout << "You need to enter a positive integer." << std::endl;
        return false;
    }

    for(int i = 0; i < sum.length(); ++i){
        if(!(isdigit(sum[i]))){
            std::cout << "You need to enter a positive integer." << std::endl;
            return false;
        }
    }    
    return true;
}

void playerInit(character* player){
    std::cout << "Player name:" << std::endl;
    std::cin >> player->name;

    std::string checkInput;
    while(true){
        std::cout << "Player hp:" << std::endl;
        std::cin >> checkInput;
        if (isPositiveNumber(checkInput)) break;
    }
    player->hp = stoi(checkInput);

    while(true){
        std::cout << "Player armor:" << std::endl;
        std::cin >> checkInput;
        if (isPositiveNumber(checkInput)) break;
    }
    player->armor = stoi(checkInput);

    while(true){
        std::cout << "Player damage:" << std::endl;
        std::cin >> checkInput;
        if (isPositiveNumber(checkInput)) break;
    }
    player->damage = stoi(checkInput);
    
}

void mapOutput(std::vector<std::vector<char>>& map){
    for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 20; ++j){
            std::cout << map[i][j];
        }
            std::cout << std::endl;
    }
}

void playerStatsOutput(character& player){
    std::cout << "Player status " << player.name << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "Name: " << player.name << std::endl;
    std::cout << "HP: " << player.hp << std::endl;
    std::cout << "Armor: " << player.armor << std::endl;
    std::cout << "Damage: " << player.damage << std::endl;
    std::cout << "**********************" << std::endl;
}

void enemiesInit(std::vector<character>* enemies){
    character enemy;
    for (int i = 1; i < 6; ++i){
        enemy.name = "Enemy #" + std::to_string(i);
        enemy.hp = std::rand() % 101 + 50;
        enemy.armor = std::rand() % 51;
        enemy.damage = std::rand() % 16 + 15;
        enemies->push_back(enemy);
    }
}

int randCoor(){
    return std::rand() % 20;
}

void placeCharactersOnMap(character* player, std::vector<character>* enemies, std::vector<std::vector<char>>* map){
    player->posX = randCoor();
    player->posY = randCoor();
    (*map)[player->posX][player->posY] = 'P';

    for(int i = 0; i < 5; ++i){
        bool isPlaceEmpty = false;
        while(!isPlaceEmpty){
            (*enemies)[i].posX = randCoor();
            (*enemies)[i].posY = randCoor();
            if ((*map)[(*enemies)[i].posX][(*enemies)[i].posY] == '-') isPlaceEmpty = true;
        }
        (*map)[(*enemies)[i].posX][(*enemies)[i].posY] = 'E';
    }
};

void newGame(character* player, std::vector<character>* enemies, std::vector<std::vector<char>>* map){
    playerInit(player);
    enemiesInit(enemies);
    placeCharactersOnMap(player, enemies, map);
}

std::string getCorrectStartCommand(){
    std::string gameStartCommand; 
    while(true){
        std::cout << "Enter: \"new\" or \"load\"" << std::endl;
        std::cin >> gameStartCommand;
        if ((gameStartCommand == "new") || (gameStartCommand == "load")) break;
        std::cout << "Incorrect command!" << std::endl;
    }
    return gameStartCommand;
}

std::string getCorrectMoveCommand(){
    std::string MoveCommand; 
    while(true){
        std::cout << "Your move. Enter U, D, L, R or \"save\" to save the current game or \"exit\" to leave the game:" << std::endl;
        std::cin >> MoveCommand;
        if ((MoveCommand == "exit") || (MoveCommand == "save") || (MoveCommand == "U") || (MoveCommand == "D") || (MoveCommand == "L") || (MoveCommand == "R")) break;
        std::cout << "Incorrect command!" << std::endl;
    }
    return MoveCommand;
}

void checkGameOver(character* player, std::vector<character>* enemies) {
    if (!player->isAlive) {
        std::cout << "Game Over!" << std::endl;
        exit(0);
    }

    bool allEnemiesDead = true;
    for (auto& enemy : *enemies) {
        if (enemy.isAlive) {
            allEnemiesDead = false;
            break;
        }
    }

    if (allEnemiesDead) {
        std::cout << "Win!" << std::endl;
        exit(0);
    }
}

void applyDamage(character* attacker, character* defender) {
    int actualDamage = attacker->damage;

    std::cout << attacker->name << " is atacking " << defender->name << std::endl;

    if (defender->armor > 0) {
        if (defender->armor >= actualDamage) {
            defender->armor -= actualDamage;
            actualDamage = 0;
        } else {
            actualDamage -= defender->armor;
            defender->armor = 0;
        }
    }

    defender->hp -= actualDamage;

    if (defender->hp <= 0) {
        defender->isAlive = false;
        std::cout << defender->name << " defeated!" << std::endl;
    }
}

void changePositions(std::string& userInput, character* player, std::vector<character>* enemies, std::vector<std::vector<char>>* map){
    int newX = player->posX;
    int newY = player->posY;

    if (userInput == "U" && newX > 0)  newX -= 1;
    if (userInput == "D" && newX < (*map)[0].size() - 1)  newX += 1;
    if (userInput == "L" && newY > 0)  newY -= 1;
    if (userInput == "R" && newY < map->size() - 1)  newY += 1;

    if ((*map)[newX][newY] == 'E') {
        for (int i = 0; i < enemies->size(); ++i) {
            if ((*enemies)[i].posX == newX && (*enemies)[i].posY == newY && (*enemies)[i].isAlive) {
                applyDamage(player, &(*enemies)[i]);
                break;
            }
        }
    } else if ((*map)[newX][newY] == '-') {
        (*map)[player->posX][player->posY] = '-';
        player->posX = newX;
        player->posY = newY;
        (*map)[newX][newY] = 'P';
    }

    for (int i = 0; i < 5; ++i){
        if (!(*enemies)[i].isAlive) continue;

        newX = (*enemies)[i].posX;
        newY = (*enemies)[i].posY;
        int randEnemyDirection = std::rand() % 4;

        if (randEnemyDirection == 0 && newX > 0 && (*map)[newX - 1][newY] == '-')  newX -= 1;
        if (randEnemyDirection == 1 && newX < (*map)[0].size() - 1 && (*map)[newX + 1][newY] == '-')  newX += 1;
        if (randEnemyDirection == 2 && newY > 0 && (*map)[newX][newY - 1] == '-')  newY -= 1;
        if (randEnemyDirection == 3 && newY < map->size() - 1 && (*map)[newX][newY + 1] == '-')  newY += 1;

        if ((*map)[newX][newY] == 'P') {
            applyDamage(&(*enemies)[i], player);
        } else if ((*map)[newX][newY] == '-') {
            (*map)[(*enemies)[i].posX][(*enemies)[i].posY] = '-';
            (*enemies)[i].posX = newX;
            (*enemies)[i].posY = newY;
            (*map)[newX][newY] = 'E';
        }
    }

    checkGameOver(player, enemies);
}

void saveGame(character& player, std::vector<character>& enemies){
    std::ofstream file(".\\save.bin", std::ios::binary);

    //file.write(player.isAlive ? "1" : "0", 1);
    int len = player.name.length();
    file.write((char*)&len, sizeof(len));
    file.write(player.name.c_str(), len);
    file.write((char*)&player.hp, sizeof(player.hp));
    file.write((char*)&player.armor, sizeof(player.armor));
    file.write((char*)&player.damage, sizeof(player.damage));
    file.write((char*)&player.posX, sizeof(player.posX));
    file.write((char*)&player.posY, sizeof(player.posY));

    for (int i = 0; i < 5; ++i){
        file.write(enemies[i].isAlive ? "1" : "0", 1);
        int len = enemies[i].name.length();
        file.write((char*)&len, sizeof(len));
        file.write(enemies[i].name.c_str(), len);
        file.write((char*)&enemies[i].hp, sizeof(enemies[i].hp));
        file.write((char*)&enemies[i].armor, sizeof(enemies[i].armor));
        file.write((char*)&enemies[i].damage, sizeof(enemies[i].damage));
        file.write((char*)&enemies[i].posX, sizeof(enemies[i].posX));
        file.write((char*)&enemies[i].posY, sizeof(enemies[i].posY));
    }

    file.close();
}

void loadGame(character& player, std::vector<character>& enemies, std::vector<std::vector<char>>& map){
    std::ifstream file(".\\save.bin", std::ios::binary);

    int len;
    file.read((char*)&len, sizeof(len));
    player.name.resize(len);
    file.read((char*)player.name.c_str(), len);
    file.read((char*)&player.hp, sizeof(player.hp));
    file.read((char*)&player.armor, sizeof(player.armor));
    file.read((char*)&player.damage, sizeof(player.damage));
    file.read((char*)&player.posX, sizeof(player.posX));
    file.read((char*)&player.posY, sizeof(player.posY));

    enemies.resize(5);

    for (int i = 0; i < 5; ++i){
        char isAliveCheck;
        file.read(&isAliveCheck, 1);
        isAliveCheck == '1' ? enemies[i].isAlive = true : enemies[i].isAlive = false;
        file.read((char*)&len, sizeof(len));
        enemies[i].name.resize(len);
        file.read((char*)enemies[i].name.c_str(), len);
        file.read((char*)&enemies[i].hp, sizeof(enemies[i].hp));
        file.read((char*)&enemies[i].armor, sizeof(enemies[i].armor));
        file.read((char*)&enemies[i].damage, sizeof(enemies[i].damage));
        file.read((char*)&enemies[i].posX, sizeof(enemies[i].posX));
        file.read((char*)&enemies[i].posY, sizeof(enemies[i].posY));
    }

    file.close();

    (map)[player.posX][player.posY] = 'P';

    for(int i = 0; i < 5; ++i){
        (map)[(enemies)[i].posX][(enemies)[i].posY] = 'E';
    }

}

int main(){
    std::srand(std::time(nullptr));
    std::vector<std::vector<char>> map(20, std::vector<char>(20, '-'));
    character player;
    std::vector<character> enemies;

    std::string gameStartCommand = getCorrectStartCommand();
    if (gameStartCommand == "new") newGame(&player, &enemies, &map);
    else if (gameStartCommand == "load") loadGame(player, enemies, map);

    playerStatsOutput(player);
    
    mapOutput(map);

    while(true){
        std::string userInput = getCorrectMoveCommand();
        if(userInput == "exit") return 0;
        if(userInput == "save") saveGame(player, enemies);
        else changePositions(userInput, &player, &enemies, &map);

        playerStatsOutput(player);
        for(int i = 0; i < 5; ++i) playerStatsOutput(enemies[i]);
        
        mapOutput(map);
    }


}