#include "filepersistence.h"
#include "config.h"
#include <fstream>

void saveBestTimesToFile() {
    std::ofstream file("besttimes.dat", std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(bestTimes), sizeof(bestTimes));
        file.close();
    }
}

void loadBestTimesFromFile() {
    std::ifstream file("besttimes.dat", std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(bestTimes), sizeof(bestTimes));
        file.close();
    }
}