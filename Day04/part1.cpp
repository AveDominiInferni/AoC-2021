#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

class field {
public:
    int value;
    bool marked;
    field(int value) : value(value) { marked = false; }
};

class board {
public:
    std::vector<std::vector<field>> b;
    int mark(int num) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (b.at(i).at(j).value == num) {
                    b.at(i).at(j).marked = true;
                    bool bingo = true;
                    for (int k = 0; k < 5; k++)
                        if (b.at(i).at(k).marked != true)
                            bingo = false;
                    if (bingo)
                        return sum_of_unmarked() * num;  

                    bingo = true;                        
                    for (int k = 0; k < 5; k++)
                        if (b.at(k).at(j).marked != true)
                            bingo = false;
                    if (bingo)
                        return sum_of_unmarked() * num;
                }
            }
        }
        return -1;
    }
    int sum_of_unmarked() {
        int sum = 0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (b.at(i).at(j).marked != true)
                    sum += b.at(i).at(j).value;
        return sum;
    }
};

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector<int> v;
        std::vector<board> boards;
        std::string line;
        std::getline(file, line);
        std::stringstream ss(line);
        std::string num;

        while (std::getline(ss, num, ','))
            v.push_back(std::stoi(num));
        
        while (std::getline(file, line)) {
            board b1;
            for (int i = 0; i < 5; i++) {
                std::getline(file, line);
                std::stringstream temp(line);
                std::vector<field> row;
                while(std::getline(temp, num, ' '))
                    if (num != "")
                        row.push_back(std::stoi(num));
                b1.b.push_back(row);
            }
            boards.push_back(b1);
        }
        file.close();

        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < boards.size(); j++) {
                auto result = boards.at(j).mark(v.at(i));
                if (result != -1) {
                    std::cout << result << std::endl;
                    return 0;
                }
            }
        }
    }
    return 1;
}