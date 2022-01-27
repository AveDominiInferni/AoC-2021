#include <iostream>
#include <set>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

class coordinate {
public:
    int x, y, z;
    coordinate(int x, int y, int z) : x(x), y(y), z(z) {}
    bool operator <(const coordinate& c) const {
        if (x < c.x)
            return true;
        if (x == c.x && y < c.y)
            return true;
        if (x == c.x && y == c.y && z < c.z)
            return true;
        return false;
    }
};

class grid {
    std::set<coordinate> active;
public:
    uint32_t size() { return active.size(); }
    void add(int x, int y, int z) { active.insert(coordinate({x, y, z})); }
    void erase(int x, int y, int z) { active.erase(coordinate({x, y, z})); }
};

int main() {
    grid g;
    std::ifstream file("input.txt");
    std::string line;
    int i = 0;
    while(std::getline(file, line)) {
        std::map<char, std::pair<int, int>> seg;
        std::stringstream ss;
        std::string field;
        if (line.at(1) == 'n')
            ss << line.substr(3);
        else
            ss << line.substr(4);
        while(std::getline(ss, field, ',')) {
            int pos = field.find('.');
            seg[field.at(0)] = {std::stoi(field.substr(2, pos - 2)), std::stoi(field.substr(pos + 2))};
        }

        for (int i = std::max(seg['x'].first, -50); i <= std::min(seg['x'].second, 50); i++) {
            for (int j = std::max(seg['y'].first, -50); j <= std::min(seg['y'].second, 50); j++) {
                for (int k = std::max(seg['z'].first, -50); k <= std::min(seg['z'].second, 50); k++) {
                    if (line.at(1) == 'n')
                        g.add(i, j, k);
                    else
                        g.erase(i, j, k);
                }
            }
        }
    }
    std::cout << g.size() << std::endl;
    file.close();
    return 0;
}