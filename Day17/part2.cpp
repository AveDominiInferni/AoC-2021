#include <iostream>

int main() {
    int minx = 277, maxx = 318, miny = -92, maxy = -53;
    int counter = 0;
    int maxt = std::max(-2 * miny + 1, maxx);

    for (int vyo = miny; vyo <= -miny; vyo++)
        for (int vxo = 1; vxo <= maxx; vxo++)
            for (int t = 1; t <= maxt; t++) {
                int y = vyo * t - t * (t - 1) / 2;
                int x;
                if (t < vxo)
                    x = vxo * t - t * (t - 1) / 2;
                else
                    x = vxo * (vxo + 1) / 2;
                if (miny <= y && y <= maxy && minx <= x && x <= maxx) {
                    counter++;
                    break;
                }
            }
    std::cout << counter << std::endl;
    return 0;
}