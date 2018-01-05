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
#endif  // PLATFORM_HPP
