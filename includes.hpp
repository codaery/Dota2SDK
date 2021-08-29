#pragma once

#include <windows.h>
#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <array>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <intrin.h>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "engine/dota_sdk.hpp"

#include "keybind.h"
#include "engine/utils/utils.h"
#include "utilities/utilities.hpp"
#include "minhook/minhook.h"
#include "hooks/hooks.hpp"
#include "engine/interfaces/interfaces.hpp"