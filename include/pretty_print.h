#pragma once

#define ANSI_RESET "\033[0m"

// Text Formatting
#define ANSI_BOLD "\033[1m"
#define ANSI_ITALIC "\033[3m"
#define ANSI_UNDERLINE "\033[4m"
#define ANSI_BLINK "\033[5m"
#define ANSI_REVERSE "\033[7m"
#define ANSI_CONCEALED "\033[8m"

// Text Color
#define ANSI_FORE_BLACK "\033[30m"
#define ANSI_FORE_RED "\033[31m"
#define ANSI_FORE_GREEN "\033[32m"
#define ANSI_FORE_YELLOW "\033[33m"
#define ANSI_FORE_BLUE "\033[34m"
#define ANSI_FORE_MAGENTA "\033[35m"
#define ANSI_FORE_CYAN "\033[36m"
#define ANSI_FORE_WHITE "\033[37m"

#define ANSI_BACK_BLACK "\033[40m"
#define ANSI_BACK_RED "\033[41m"
#define ANSI_BACK_GREEN "\033[42m"
#define ANSI_BACK_YELLOW "\033[43m"
#define ANSI_BACK_BLUE "\033[44m"
#define ANSI_BACK_MAGENTA "\033[45m"
#define ANSI_BACK_CYAN "\033[46m"
#define ANSI_BACK_WHITE "\033[47m"

// Cursor Movement
#define ANSI_CURSOR_UP(n) "\033[" #n "A"
#define ANSI_CURSOR_DOWN(n) "\033[" #n "B"
#define ANSI_CURSOR_RIGHT(n) "\033[" #n "C"
#define ANSI_CURSOR_LEFT(n) "\033[" #n "D"
#define ANSI_CURSOR_TO_LINE_BEGIN "\033[E"
#define ANSI_CURSOR_TO_PREVIOUS_LINE "\033[F"

// Clear Screen
#define ANSI_CLEAR_SCREEN "\033[2J"
#define ANSI_CLEAR_SCREEN_TO_END "\033[J"
#define ANSI_CLEAR_SCREEN_TO_BEGIN "\033[1J"
