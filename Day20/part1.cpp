#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <set>
#include <chrono>

using namespace std::chrono;
auto start = high_resolution_clock::now();
std::vector<std::pair<int, int>> neighbours = {{-1, -1},{0, -1},{1, -1},{-1, 0},{0, 0},{1, 0},{-1, 1},{0, 1}, {1, 1}};

int bin_to_dec(const std::string &s) {
    int d = 0;
    for (int i = 0; i < s.length(); i++)
        if (s.at(s.length() -  i -  1) == '1')
            d += std::pow(2, i);
    return d;
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::set<std::pair<int, int>> image;
        std::string iea;
        std::string line;
        std::getline(file, iea);
        std::getline(file, line);
        int j = 0;
        while (std::getline(file, line)) {
            int i = 0;
            for (auto c : line) {
                if (c == '#')
                    image.insert({i, j});
                i++;
            }
            j++;
        }
        for (int k = 0; k < 2; k++) {
            std::set<std::pair<int, int>> copy;
            int x_min = INT32_MAX, x_max = INT32_MIN, y_min = INT32_MAX, y_max = INT32_MIN;
            for (auto x : image) {
                x_min = std::min(x_min, x.first);
                x_max = std::max(x_max, x.first);
                y_min = std::min(y_min, x.second);
                y_max = std::max(y_max, x.second);  
            }

            for (int j = y_min - 1; j <= y_max + 1; j++) {
                for (int i = x_min - 1; i <= x_max + 1; i++) {
                    std::string num;
                    for (auto x : neighbours) {
                        if (i + x.first < x_min || i + x.first > x_max || j + x.second < y_min || j + x.second > y_max) {
                            if ((k + 1) % 2)
                                num.push_back('0');
                            else
                                num.push_back('1');
                        }
                        else if (image.find({i + x.first, j + x.second}) != image.end())
                            num.push_back('1');
                        else
                            num.push_back('0');
                    }
                    if (iea.at(bin_to_dec(num)) == '#')
                        copy.insert({i, j});
                }
            }
            image = copy;
        }
        std::cout << image.size() << std::endl;
    }
    file.close();
    auto stop = high_resolution_clock::now();
    std::cout << "Execution time: " << duration_cast<microseconds>(stop - start).count() << " microseconds" << std::endl;
    // Execution time: 0.17 seconds
    return 0;
}