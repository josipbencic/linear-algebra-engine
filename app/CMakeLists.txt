add_executable(app
  ApplicationState.cpp
  ApplicationState.hpp
  ApplicationInputManager.cpp
  ApplicationInputManager.hpp
  ApplicationStateMachine.cpp
  ApplicationStateMachine.hpp
  ConsoleAppMain.cpp
  Platform.hpp
)
target_link_libraries("app" "numerical")
target_compile_features(numerical  PUBLIC cxx_constexpr)

if(MSVC)
  add_compile_options(/W3 /WX)
else()
  add_compile_options(-W -Wall -Werror)
endif()

