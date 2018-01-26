#include "Platform.hpp"

#if CONSOLE_APP > 0

#include "../Core/ConsoleApp/ApplicationStateMachine.hpp"

int main() {
  ApplicationStateMachine app;
  while (1) {
    app.showScene();
  }
}
#endif
