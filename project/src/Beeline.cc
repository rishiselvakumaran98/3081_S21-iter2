#include "Beeline.h"
namespace csci3081 {
    std::vector<std::vector<float>> Beeline::GetPath(std::vector<float> source, std::vector<float> destination) {
        std::vector<std::vector<float>> path;
        source[1] += 200;
        destination[1] += 200;
        path.push_back(source);
        path.push_back(destination);
        destination[1] -= 200;
        path.push_back(destination);
        return path;
    }
} //close namespace 