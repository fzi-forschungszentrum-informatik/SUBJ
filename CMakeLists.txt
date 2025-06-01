###
### SUBJ CMakeLists.txt
###

# SUBJ requires:
# * C++11 compatible compiler
# * Eigen3 v3.3
# * pybind11

cmake_minimum_required(VERSION 3.16)

project(subj
	VERSION 0.1.0
	LANGUAGES CXX)


##
## Dependencies
##
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

if(BUILD_PYTHON_BINDINGS)
  set(PYBIND11_FINDPYTHON ON)
  find_package(pybind11 CONFIG REQUIRED)
endif()


##
## Set C++11 standard / enable global pedantic and Wall
##
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")


##
## Build the SUBJ library
##
add_library(subj
  src/BinomialOpinion.cpp
  src/DirichletPDF.cpp
  src/Histogram.cpp
  src/HyperOpinion.cpp
  src/MultinomialOpinion.cpp
  src/Operators.cpp
  src/OpinionOwner.cpp
  src/Version.cpp
)
target_compile_options(subj PUBLIC ${CXX11_FLAG})
set_property(TARGET subj PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(subj
                           PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_include_directories(subj PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(subj PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${EIGEN3_INCLUDE_DIR}
)
target_link_libraries(subj PUBLIC
  Eigen3::Eigen
)
add_library(subj::subj ALIAS subj)


##
## Build SUBJ examples
##
add_subdirectory(examples)


##
## Install SUBJ library
##
install(TARGETS subj EXPORT subj_targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)

install(EXPORT subj_targets
  DESTINATION lib/cmake/subj
  FILE subjTargets.cmake
  NAMESPACE subj::)

install(DIRECTORY include/subj
  DESTINATION include
  FILES_MATCHING PATTERN "*.h")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(subjConfigVersion.cmake VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)
install(FILES subjConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/subjConfigVersion.cmake
  DESTINATION lib/cmake/subj)


if(BUILD_PYTHON_BINDINGS)
  ##
  ## Build SUBJ python bindings
  ##
  pybind11_add_module(pysubj MODULE
    src/SubjPythonBindings.cpp
  )
  target_compile_definitions(pysubj
                            PRIVATE VERSION_INFO=${PROJECT_VERSION})
  target_include_directories(pysubj PRIVATE ${EIGEN_INCLUDE_DIR})
  target_link_libraries(pysubj PUBLIC
    subj::subj
    Eigen3::Eigen
    pybind11::headers
  )


  ##
  ## Install SUBJ python bindings
  ##
  install(TARGETS pysubj DESTINATION pysubj)
endif()
