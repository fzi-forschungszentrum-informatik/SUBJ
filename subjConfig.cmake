include(CMakeFindDependencyMacro)
find_dependency(Eigen3 3.3)
include("${CMAKE_CURRENT_LIST_DIR}/subjTargets.cmake")
