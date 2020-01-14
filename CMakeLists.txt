cmake_minimum_required(VERSION 3.0.0)
project(Hackerrank_Projects VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Add various sub-sections
add_subdirectory ("CtCI")