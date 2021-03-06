add_library(numerical
  AlgebraicStructures/Mat3.hpp
  AlgebraicStructures/Polynomial.hpp
  AlgebraicStructures/Polynomial2.hpp
  AlgebraicStructures/RealCoordinateSpace.hpp
  AlgebraicStructures/Surface.hpp
  Algorithms/Interpolation.cpp
  Algorithms/Interpolation.hpp
  Algorithms/LinearSystems.cpp
  Algorithms/LinearSystems.hpp
  Algorithms/GramSchmidt.hpp
  Constants.hpp
  MathStreams.cpp
  MathStreams.hpp
)

target_compile_features(numerical PUBLIC cxx_std_17)
target_include_directories(numerical PUBLIC ${PROJECT_SOURCE_DIR}/extern/eigen)


add_executable(playground PlaygroundMain.cpp)
target_compile_features(playground PUBLIC cxx_std_17)
target_link_libraries(playground numerical)

if(MSVC)
  add_compile_options(/W3 /WX)
else()
  add_compile_options(-W -Wall -Werror)
endif()

