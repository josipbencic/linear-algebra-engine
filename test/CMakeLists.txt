add_executable(test
  Main.cpp
  Tester.cpp
  Tester.hpp
  Algorithms/LinearSystemsTests.hpp
  Algorithms/LinearSystemsTests.cpp
  Algorithms/InterpolationTests.hpp
  Algorithms/InterpolationTests.cpp
)

target_link_libraries("test" "numerical")
target_compile_features(test PUBLIC cxx_constexpr)

if(MSVC)
  add_compile_options(/W3 /WX)
else()
  add_compile_options(-W -Wall -Werror)
endif()
