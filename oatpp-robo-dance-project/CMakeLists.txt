cmake_minimum_required(VERSION 3.1)


set(project_name robo-dance-project)
set(CMAKE_CXX_STANDARD 17)

project(${project_name})

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/controller/MyController.cpp
        src/controller/MyController.hpp
        src/dto/DTOs.hpp
        src/kinematics/RoboKinematicModel.cpp
        src/kinematics/RoboKinematicModel.hpp
)

set_target_properties(${project_name}-lib
    PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS off
    )

## link libs

find_package(oatpp 1.3.0 REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        Eigen3::Eigen
)

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe
        src/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

# tests
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(
  test_kinematics
  tests/test_kinematics.cpp
)
target_link_libraries(
  test_kinematics
  GTest::gtest_main
  ${project_name}-lib
)

include(GoogleTest)
gtest_discover_tests(test_kinematics)
