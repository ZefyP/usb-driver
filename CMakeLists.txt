MESSAGE(STATUS " ")
MESSAGE(STATUS "${BoldBlue}========================================================================================================${Reset}")
MESSAGE(STATUS "    ${BoldYellow}MIDDLEWARE${Reset} [stand-alone]: Compilation of the middleware package")
MESSAGE(STATUS "    ${BoldYellow}MIDDLEWARE${Reset} [stand-alone]: [${BoldCyan}${BASE_DIR}/CMakeLists.txt${Reset}]")
MESSAGE(STATUS " ")

cmake_minimum_required(VERSION 2.8)
project(Ph2_ACF)

# Set the output directory
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
MESSAGE( STATUS "${BoldRed}" )
MESSAGE( FATAL_ERROR "${Reset}In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

# ---------- Setup output Directories -------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
${PROJECT_SOURCE_DIR}/lib
CACHE PATH
"Single Directory for all Libraries"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
${PROJECT_SOURCE_DIR}/bin
CACHE PATH
"Single Directory for all Executables."
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
${PROJECT_SOURCE_DIR}/bin
CACHE PATH
"Single Directory for all static libraries."
)
# ---------- Setup output Directories -------------------------

# Set the cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

MESSAGE(STATUS "")
MESSAGE(STATUS "    ${BoldYellow}COMPILATION FLAGS:${Reset}")

# If it's a recent gcc compiler, then let's add some
# compiler options to avoid warnings promoted to errors

#original flags
#set (GCC_NOERROR_FLAGS " -Wno-error=unused-result    -Wno-error=deprecated-declarations")
#new temporary flags
set (GCC_NOERROR_FLAGS " -Wno-error=unused-result    -Wno-error=deprecated-declarations -Wno-error=unused-variable    -Wno-error=unused-but-set-variable -Wno-error=overflow")
set (GCC_6_NOERROR_FLAGS "-Wno-error=misleading-indentation")
set (GCC_7_NOERROR_FLAGS "-Wno-expansion-to-defined -Wno-error=format-overflow")
set (GCC_8_NOERROR_FLAGS "-Wno-error=catch-value -Wno-error=class-memaccess -Wno-error=format-overflow")
#set (GCC_9_NOERROR_FLAGS "-Wno-error=deprecated-copy -Wno-error=int-in-bool-context -Wno-error=unused-variable")

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
EXECUTE_PROCESS( COMMAND gcc -dumpversion OUTPUT_VARIABLE GCC_VERSION )
if(NOT (GCC_VERSION VERSION_LESS 6))
set (GCC_NOERROR_FLAGS "${GCC_NOERROR_FLAGS} ${GCC_6_NOERROR_FLAGS}")
endif()
if(NOT (GCC_VERSION VERSION_LESS 7))
set (GCC_NOERROR_FLAGS "${GCC_NOERROR_FLAGS} ${GCC_7_NOERROR_FLAGS}")
endif()
if(NOT (GCC_VERSION VERSION_LESS 8))
set (GCC_NOERROR_FLAGS "${GCC_NOERROR_FLAGS} ${GCC_8_NOERROR_FLAGS}")
endif()
if(NOT (GCC_VERSION VERSION_LESS 9))
set (GCC_NOERROR_FLAGS "${GCC_NOERROR_FLAGS} ${GCC_9_NOERROR_FLAGS}")
endif()
endif ()
set (CMAKE_CXX_FLAGS "-std=c++11 -gdwarf-4 -O4 -fopenmp -fno-omit-frame-pointer -pedantic -Wno-unused-parameter -Wno-ignored-qualifiers -Wno-missing-field-initializers -Wall -Werror=return-type -Wextra -Winit-self -Wno-unused-local-typedefs -Woverloaded-virtual -Wnon-virtual-dtor -Wdelete-non-virtual-dtor ${GCC_NOERROR_FLAGS} -pthread -Wcpp -fPIC ${CMAKE_CXX_FLAGS}")
if(NoDataShipping)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{UseRootFlag}")
endif()


# Check for external dependences
message("--")
message("--     ${BoldCyan}#### Checking for external Dependencies ####${Reset}")

# Power supply
find_package(PH2_POWERSUPPLY) #========================================================
if(PH2_POWERSUPPLY_FOUND)
message(STATUS "    Building the PowerSupply components")
endif(PH2_POWERSUPPLY_FOUND)

# Ph2_TCUSB [USB control of hybrids]
find_package(PH2_TCUSB)  
if(PH2_TCUSB_FOUND)
message(STATUS "    Building the TestCards USB components")
endif(PH2_TCUSB_FOUND)

message("--     ${BoldCyan}#### Done ####${Reset}")


MESSAGE(STATUS " ")

add_subdirectory(library)
add_subdirectory(src)

message("--     ${BoldRed}#### Don't forget to set the path and ld_library_path by sourcing setup.sh before running ###${Reset}")
#set(ENV{PATH} "$ENV{PATH}:${PROJECT_SOURCE_DIR}/bin")
#set(ENV{LD_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/lib:$ENV(LD_LIBRARY_PATH)")

MESSAGE(STATUS " ")
MESSAGE(STATUS "${BoldYellow}MIDDLEWARE${Reset} [stand-alone]: [${BoldCyan}${BASE_DIR}/CMakeLists.txt${Reset}]")
MESSAGE(STATUS "${BoldBlue}========================================================================================================${Reset}")
MESSAGE(STATUS " ")
