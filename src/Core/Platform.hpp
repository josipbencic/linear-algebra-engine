#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#ifdef _WIN32
# define CLEAR "cls"

#elif defined(__unix__)
# define CLEAR "clear"

#elif define (__APPLE__)
# define CLEAR "clear"

#else
# define CLEAR ""
#endif  //  OS



#define CONSOLE_APP 0
#define UNIT_TESTER 0
#define MATH_MAIN 1
#define PLAYGROUND_MAIN 0


#endif  // PLATFORM_HPP
