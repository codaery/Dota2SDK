#pragma once

#include "../../includes.hpp"
#include "vector.h"
#include "matrix.h"

namespace utils {
    bool world_to_screen(const Vector& spot, int& xOut, int& yOut, const matrix& vMatrix);
    std::uint8_t* pattern_scan(char* module_name, const char* signature);
}