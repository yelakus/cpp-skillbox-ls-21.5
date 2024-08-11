#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum building_type{
    house = 0,
    garage,
    shed,
    bathhouse
};

enum room_type{
    bedroom = 0,
    kitchen,
    bathroom,
    children,
    living
};


struct room{
    room_type roomType;
    int roomSquares = 0;
};

struct floorHouse{
    int numOfFloor = 0;
    int totalRooms = 0;
    int floorsHeight = 0;
    std::vector<struct room> roomsInFloor;
};

struct houseBuilding{
    int totalFloors = 0;
    struct floorHouse floorInfo;
    bool isOvenThere = true;
};

struct building{
    building_type buildingType;
    int buildingSquares = 0;
};

struct Area{
    int numOfArea = 0;
    std::vector<struct building> BuildingInArea;
    struct houseBuilding houseInfo;

};

building getBuildingInfo(building_type actualType){
    building actualBuilding;
    actualBuilding.buildingType = actualType;
    std::cout << "Введите площадь:" << std::endl;
    std::cin >> actualBuilding.buildingSquares;
    return actualBuilding;
}

std::vector<struct building> getBuildings(){
    std::vector<struct building> Buildings;
    std::string userInptut;
    while(true){
        std::cout << "Введите какое здание есть на участке(house, garage, shed, bathhouse). Если больше нет зданий или участок пуст то введите -" << std::endl;
        std::cin >> userInptut;
        if (userInptut == "-") return Buildings;
        if (userInptut == "house") Buildings.push_back(getBuildingInfo(building_type::house));
        if (userInptut == "garage") Buildings.push_back(getBuildingInfo(building_type::garage));
        if (userInptut == "shed") Buildings.push_back(getBuildingInfo(building_type::shed));
        if (userInptut == "bathhouse") Buildings.push_back(getBuildingInfo(building_type::bathhouse));
    }
}

room getRoomsInfo(int& j){
    room actualRoom;
    std::string userInptut;
    std::cout << "Введите какая это комната(bedroom, kitchen, bathroom, children, living)." << std::endl;
    std::cin >> userInptut;
    if (userInptut == "bedroom") actualRoom.roomType = room_type::bedroom;
    if (userInptut == "kitchen") actualRoom.roomType = room_type::kitchen;
    if (userInptut == "bathroom") actualRoom.roomType = room_type::bathroom;
    if (userInptut == "children") actualRoom.roomType = room_type::children;
    if (userInptut == "living") actualRoom.roomType = room_type::living;

    std::cout << "Введите площадь комнаты:" << std::endl;
    std::cin >> actualRoom.roomSquares;
     
    return actualRoom;
}

floorHouse getFloorInfo(int& i){
    floorHouse actualFloor;
    actualFloor.numOfFloor = i;
    std::cout << "Введите высоту этажа:" << std::endl;
    std::cin >> actualFloor.floorsHeight;
    std::cout << "Введите количество комнат:" << std::endl;
    std::cin >> actualFloor.totalRooms;

    for (int j = 0; j < actualFloor.totalRooms; ++j){
        actualFloor.roomsInFloor.push_back(getRoomsInfo(j));
    }

    return actualFloor;

}

houseBuilding getHouseInfo(){
    houseBuilding actualHouse;
    std::cout << "Введите общее количество этажей в доме:" << std::endl;
    std::cin >> actualHouse.totalFloors;
    for (int i = 0; i < actualHouse.totalFloors; ++i){
        actualHouse.floorInfo = getFloorInfo(i);
    }
    return actualHouse;
}

void fillArea(Area* actualArea, int& i){
    actualArea->numOfArea = i;
    actualArea->BuildingInArea = getBuildings();
    
    for (auto elem : actualArea->BuildingInArea) 
    if (elem.buildingType == building_type::house) 
    actualArea->houseInfo = getHouseInfo();
}

int main(){
    std::vector<struct Area> village;

    int totalNumberOfAreas;
    std::cout << "Введите общее количество участков:" << std::endl;
    std::cin >> totalNumberOfAreas;

    for (int i = 0; i < totalNumberOfAreas; i++){
        Area actualArea;
        fillArea(&actualArea, i);
        village.push_back(actualArea);
    }

    std::cout << "Участок:" << village[0].houseInfo.totalFloors << std::endl;

}