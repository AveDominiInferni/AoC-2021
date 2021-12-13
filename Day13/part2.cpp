#include <iostream>
#include <fstream>
#include <set>

class coordinate {
public:
    int x, y;
    coordinate(int x, int y) : x(x), y(y) {}
    bool operator <(const coordinate& c) const { if (x < c.x) return true; if (x == c.x && y < c.y) return true; return false; }
};

class paper {
public:
    std::set<coordinate> dots;
    void fold(char c, int n) {
        std::set<coordinate> temp;
        for (auto el : dots) {
            if (c == 'y' && el.y > n) {
                temp.insert(coordinate(el.x,  el.y - 2 * (el.y - n)));
            }
            else if (c == 'x' && el.x > n) {
                temp.insert(coordinate(el.x - 2 * (el.x - n), el.y));
            }
            else
                temp.insert(el);
        }
        dots = temp;
    }
    void draw() {
        int max_x = 0, max_y = 0;
        for (auto el : dots) {
            if (el.x > max_x)
                max_x = el.x;
            if (el.y > max_y)
                max_y = el.y;
        }
        for (int j = 0 ; j <= max_y ; j++) {
            for (int i = 0 ; i <= max_x ; i++) {
                if (dots.find(coordinate(i, j)) != dots.end())
                    std::cout << "#";
                else
                    std::cout << ".";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        paper p;
        std::string line;
        while (std::getline(file, line)) {
            if (line == "")
                break;
            auto coma = line.find(',');
            p.dots.insert(coordinate(std::stoi(line.substr(0, coma)), std::stoi(line.substr(coma + 1))));
        }
        while (std::getline(file, line))
            p.fold(line.at(11), std::stoi(line.substr(13)));
        p.draw();
    }
    file.close();
    return 0;
}