#pragma once

#include <iostream>

#include <memory>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>
#include <map>
#include <string>

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "Opengl32.lib")

using namespace std;

#include "TVector.h"

typedef TVector<int, 2> T2Int;
typedef TVector<int, 4> T4Int;

typedef glm::vec2 Vec2f;
typedef glm::ivec2 Vec2i;

typedef int Type_Not_Determined;

#define DTR(x) ((x)*PI/180.0)
#define RTD(x) ((x)*180.0/PI)
#define MC_In(a,b,x) (x <= b && x >= a)
#define MC_R(x) ((int)((x)+0.5))
#define CR_(x) const x&
