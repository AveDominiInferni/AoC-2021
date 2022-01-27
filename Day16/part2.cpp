#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>

using namespace std::chrono;
auto start = high_resolution_clock::now();

std::map<char, std::string> hex = {
    {'0', "0000"},
    {'1', "0001"},
    {'2', "0010"},
    {'3', "0011"},
    {'4', "0100"},
    {'5', "0101"},
    {'6', "0110"},
    {'7', "0111"},
    {'8', "1000"},
    {'9', "1001"},
    {'A', "1010"},
    {'B', "1011"},
    {'C', "1100"},
    {'D', "1101"},
    {'E', "1110"},
    {'F', "1111"}
};

struct packet {
    int version;
    int type;
    uint64_t value;
    std::vector<packet> sub;
    packet (int version, int type, uint64_t value, const std::vector<packet> &sub) : version(version), type(type), value(value), sub(sub) {};
    uint64_t get_packet_value();
};

uint64_t bin_to_dec(const std::string &s) {
    uint64_t d = 0;
    for (int i = 0; i < s.length(); i++)
        if (s.at(s.length() -  i -  1) == '1')
            d += std::pow(2, i);
    return d;
}

std::string hex_to_bin(const std::string &s) {
    std::string bin;
    for (auto x : s)
        bin.append(hex[x]);
    return bin;
}

packet get_packet(const std::string &s, int &i) {
    int packet_version = bin_to_dec(s.substr(i, 3));
    int packet_type_id = bin_to_dec(s.substr(i + 3, 3));
    i += 6;
    if (packet_type_id == 4) {
        std::string num;
        while (i < s.length()) {
            num.append(s.substr(i + 1, 4));
            i += 5;
            if (s.at(i - 5) == '0')
                break;
        }
        return packet(packet_version, packet_type_id, bin_to_dec(num), std::vector<packet>());
    }
    else {
        int packet_length_id = bin_to_dec(s.substr(i, 1));
        i += 1;
        if (packet_length_id == 0) {
            uint64_t len  = bin_to_dec(s.substr(i, 15));
            i += 15;
            int j = i;
            packet p = packet(packet_version, packet_type_id, -1, std::vector<packet>());
            while (i < j + len)
                p.sub.push_back(get_packet(s, i));
            return p;
        } 
        else {
            int count  = bin_to_dec(s.substr(i, 11));
            i += 11;
            packet p = packet(packet_version, packet_type_id, -1, std::vector<packet>());
            for (int j = 0; j < count; j++)
                p.sub.push_back(get_packet(s, i));
            return p;
        }
    }
    return packet(0, 0 , 0, {});
}

int main() {
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::vector<int> ver;
        std::string line;
        std::getline(file, line);
        line = hex_to_bin(line);
        int i = 0;
        packet p = get_packet(line, i);
        std::cout << p.get_packet_value() << std::endl;     
    }
    file.close();
    auto stop = high_resolution_clock::now();
    std::cout << "Execution time: " << duration_cast<microseconds>(stop - start).count() << " microseconds" << std::endl;
    // Execution time: 3001 microseconds
    return 0;
}

uint64_t packet::get_packet_value() {
  if (value == -1) {
    for (auto &x : sub)
        x.get_packet_value();
    if (type == 0) {
        value = 0;
        for (packet x : sub)
            value += x.value;
    } 
    else if (type == 1) {
        value = 1;
        for (packet x : sub)
            value *= x.value;
    }
    else if (type == 2) {
        value = UINT64_MAX;
        for (packet x : sub)
            if (x.value < value)
                value = x.value;
    }
    else if (type == 3) {
        value = 0;
        for (packet x : sub)
            if (x.value > value)
                value = x.value;
    }
    else if (type == 5)
        value = sub[0].value > sub[1].value ? 1 : 0;
    else if (type == 6)
        value = sub[0].value < sub[1].value ? 1 : 0;
    else if (type == 7)
        value = sub[0].value == sub[1].value ? 1 : 0;
    }
    return value;
}