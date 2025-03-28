###
### SUBJ examples
###

##
## Build examples
##
add_executable(subj_example subj_example.cpp)
target_compile_options(subj_example PRIVATE ${CXX11_FLAG})
target_link_libraries(subj_example
  subj::subj
  Eigen3::Eigen
)
