#define CONSOLE_APP 1

#if CONSOLE_APP > 0

#include "../Core/ConsoleApp/ApplicationStateMachine.hpp"

int main() {
  ApplicationStateMachine app;
  while (1) {
    app.showScene();
  }
}

#else

#ifndef TESTER
#define TESTER 1
#endif

#endif
