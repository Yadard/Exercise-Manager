#pragma once

#define EXERCISE_GETTER get_exercise
#include <stddef.h>

#if defined(_WIN32) || defined(_WIN64)
#ifdef LIBRARY_EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif
#else
#define LIBRARY_API
#endif

typedef void (*func_exercise_t)();
typedef func_exercise_t (*func_get_exercise_t)(const char *, size_t);
