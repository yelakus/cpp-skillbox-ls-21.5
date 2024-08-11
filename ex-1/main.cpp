#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct reg {
    std::string name = "unknown";
    std::string date = "00.00.0000";
    int payment = 0;
};

void listCommand(std::ifstream& file, reg& userInfo){
    std::string lastNameTemp, paymentTemp;
    file >> userInfo.name;
    if (file.eof()) return;
    file >> lastNameTemp;
    userInfo.name += " " + lastNameTemp;

    file >> userInfo.date;
    
    file >> paymentTemp;
    userInfo.payment = std::stoi(paymentTemp);

    std::cout << userInfo.name << " " << userInfo.date << " " << userInfo.payment <<"p." << std::endl;
}

bool isPositiveNumber(std::string sum){
    if (sum[0] == '-'){
        std::cout << "Нужно ввести целое положительное число." << std::endl;
        return false;
    }

    for(int i = 0; i < sum.length(); ++i){
        if(!(isdigit(sum[i]))){
            std::cout << "Нужно ввести целое положительное число." << std::endl;
            return false;
        }
    }    
    return true;
}

std::string getSumInput(){
    std::string sum;

    while(true){
        std::cout << "Введите сумму:" << std::endl;
        std::cin >> sum;
        if (isPositiveNumber(sum)) break;
    }

    return sum;
}

bool isDateInputCorrect(std::string date){
    if (date.length() != 10 || date[2] != '.' || date[5] != '.') {
        std::cout << "Неправильный ввод!" << std::endl;
        return false;
    }

    std::string day, month, year;
    day = date.substr(0, 2);
    month = date.substr(3, 2);
    year = date.substr(6, 4);
    
    if(isPositiveNumber(day) && isPositiveNumber(month) && isPositiveNumber(year)) return true;
    
    std::cout << "Неправильный ввод!" << std::endl;
    return false;
}

std::string getDateInput(){
    std::string date;

    while(true){
        std::cout << "Введите дату в формате ДД.ММ.ГГГГ: " << std::endl;
        std::cin >> date;
        if (isDateInputCorrect(date)) break;
    }

    return date;
}

void addCommand(std::ofstream& file, reg& userInfo){
    std::string lastName;

    std::cout << "Введите Имя: " << std::endl;
    std::cin >> userInfo.name;
    std::cout << "Введите Фамилию: " << std::endl;
    std::cin >> lastName;
    userInfo.name += " " + lastName;

    userInfo.date = getDateInput();
    userInfo.payment = std::stoi(getSumInput());
    
    file << userInfo.name << " "  << userInfo.date << " " << userInfo.payment << "p." << std::endl;
}

int main(){
    reg person;

    std::string command;
    std::cout << "enter command list or add:" << std::endl;
    std::cin >> command;

    if (command == "list")
    {
        std::ifstream file("register.txt");
        while(!file.eof()) listCommand(file, person);
        file.close();
    } 
    else if (command == "add")
    {
        std::ofstream file("register.txt", std::ios::app);
        addCommand(file, person);
        file.close();
    } 
    else std::cout << "You can enter only list or add!" << std::endl;
    
}