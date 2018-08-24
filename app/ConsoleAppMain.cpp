#include "Platform.hpp"

#include "ApplicationStateMachine.hpp"

int main() {
  ApplicationStateMachine app;
  while (1) {
    app.showScene();
  }
}
