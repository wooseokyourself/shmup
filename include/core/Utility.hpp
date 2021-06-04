#ifndef __UTILITY__
#define __UTILITY__

#include <random>
#include <map>

#include <core/GL/glew.h>

#ifdef __APPLE__
#   include <OpenGL/gl3.h>
#   include <GLUT/glut.h>
#   define GL_SILENCE_DEPRECATION
#elif _WIN32
#   include <GL/freeglut.h>
#endif

inline float getRadian(const float degree) {
    return degree * 3.141592653589793f / 180.0f;
}

inline double randomRealNumber(const double min, const double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return (double)dis(gen);
}

inline int randomIntegerNumber(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return (int)dis(gen);
}

#endif