#pragma once

#define EXERCISE_GETTER get_exercise

#ifdef LIBRARY_EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

typedef void (*func_exercise_t)();
typedef func_exercise_t (*func_get_exercise_t)(const char *);
