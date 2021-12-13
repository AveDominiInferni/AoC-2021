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
        std::getline(file, line);
        p.fold(line.at(11), std::stoi(line.substr(13)));
        std::cout << p.dots.size() << std::endl;
    }
    file.close();
    return 0;
}