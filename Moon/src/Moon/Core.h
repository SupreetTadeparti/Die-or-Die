#pragma once

#ifdef MOON_PLATFORM_WINDOWS
	#ifdef MOON_BUILD_DLL
		#define MOON_API __declspec(dllexport)
	#else
		#define MOON_API __declspec(dllimport)
	#endif
#else
	#error Moon only supports Windows!
#endif

#include <windows.h>

#include <glew.h>
#include <glfw3.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>

typedef int32_t Int;
typedef int32_t Int32;
typedef int64_t Int64;
typedef uint32_t Uint;
typedef uint32_t Uint32;
typedef uint64_t Uint64;
typedef bool Bool;
typedef char Char;
typedef float Float;
typedef double Double;
typedef long double LongDouble;
typedef std::string String;
typedef std::wstring WString;
typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::mat3 Mat3;
typedef glm::mat4 Mat4;

#define List std::vector
#define Map std::map
#define HashMap std::unordered_map

#include "Util.hpp"
#include "Math.hpp"
#include "Logger.hpp"
#include "Window.hpp"
#include "Event.hpp"
