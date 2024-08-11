#include <iostream>
#include <cmath>
#include <string>

struct vec{
    double x;
    double y;
};

void addOp()
{
    vec vec1, vec2, res;
    std::cout << "Input x1 and y1:" << std::endl;
    std::cin >> vec1.x >> vec1.y;
    std::cout << "Input x2 and y2:" << std::endl;
    std::cin >> vec2.x >> vec2.y;

    res.x = vec1.x + vec2.x;
    res.y = vec1.y + vec2.y;

    std::cout << "Add op res: {" << res.x << ", " << res.y << "}" << std::endl;
};

void subtractOp()
{
    vec vec1, vec2, res;
    std::cout << "Input x1 and y1:" << std::endl;
    std::cin >> vec1.x >> vec1.y;
    std::cout << "Input x2 and y2:" << std::endl;
    std::cin >> vec2.x >> vec2.y;

    res.x = vec1.x - vec2.x;
    res.y = vec1.y - vec2.y;

    std::cout << "Subtract op res: {" << res.x << ", " << res.y << "}" << std::endl;
};

void scaleOp()
{
    vec vec1, res;
    int scalar;
    std::cout << "Input x and y:" << std::endl;
    std::cin >> vec1.x >> vec1.y;
    std::cout << "Input scalar:" << std::endl;
    std::cin >> scalar;

    res.x = vec1.x * scalar;
    res.y = vec1.y * scalar;

    std::cout << "Scale op res: {" << res.x << ", " << res.y << "}" << std::endl;
};

void lengthOp()
{
    vec vec1;
    double res;
    std::cout << "Input x and y:" << std::endl;
    std::cin >> vec1.x >> vec1.y;

    res = std::sqrt(vec1.x * vec1.x + vec1.y * vec1.y);

    std::cout << "Scale op res:" << res << std::endl;
};

void normalizeOp()
{
    vec vec1, res;
    std::cout << "Input x and y:" << std::endl;
    std::cin >> vec1.x >> vec1.y;
    
    double length = std::sqrt(vec1.x * vec1.x + vec1.y * vec1.y);
    if (length == 0) {
        std::cout << "Cannot normalize zero vector" << std::endl;
        return;
    }

    res.x = vec1.x / length;
    res.y = vec1.y / length;

    std::cout << "Normalize op res: {" << res.x << ", " << res.y << "}" << std::endl;
};


int main() {
    std::string op;
    std::cout << "Chose operation(add, subtract, scale, length, normalize):" << std::endl;
    std::cin >> op;

    if(op == "add") addOp();
    else if (op == "subtract") subtractOp();
    else if (op == "scale") scaleOp();
    else if (op == "length") lengthOp();
    else if (op == "normalize") normalizeOp();
    else std::cout << "Incorrect operation" << std::endl;

}