#pragma once
#include <array>
#include <assert.h>
#include <bitset>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef _WIN32
	#define NOMINMAX
	#include <Windows.h>
#endif

#include "PCH.h"
#include "Utils.h"
#include "Globals.h"

#include "glm.h"
using namespace glm;

#include "Jolt/Jolt.h"
using namespace JPH;

using Path = std::filesystem::path;