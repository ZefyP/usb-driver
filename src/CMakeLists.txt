

# Includes
include_directories(${PROJECT_SOURCE_DIR}/library)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PH2_TCUSB_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Library dirs
# link_directories(${UHAL_UHAL_LIB_PREFIX})
link_directories(${PROJECT_SOURCE_DIR/lib})
link_directories(${PH2_POWERSUPPLY_LIBRARY_DIRS})
link_directories(${PH2_TCUSB_LIBRARY_DIRS})

# Check for PowerSupply
if(${PH2_POWERSUPPLY_FOUND})
include_directories(${PH2_POWERSUPPLY_INCLUDE_DIRS})
link_directories(${PH2_POWERSUPPLY_LIBRARY_DIRS})
set(LIBS ${LIBS} ${PH2_POWERSUPPLY_LIBRARIES})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{PowerSupplyFlag}")
endif()

# Check for TestCard USBDriver
if(${PH2_TCUSB_FOUND})
include_directories(${PH2_TCUSB_INCLUDE_DIRS})
link_directories(${PH2_TCUSB_LIBRARY_DIRS})
set(LIBS ${LIBS} ${PH2_TCUSB_LIBRARIES} usb)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{TCUSBFlag}")
endif(${PH2_TCUSB_FOUND})

# initial set of libraries
set(LIBS ${LIBS} cmsph2_tcusb cmsph2_tcusb_pspoh PowerSupply pugixml boost_system boost_program_options boost_filesystem)

####################################
## EXECUTABLES
####################################

file(GLOB BINARIES RELATIVE ${PROJECT_SOURCE_DIR}/src *.cc)

message("--     ${BoldCyan}#### Building the following executables: ####${Reset}")

foreach(sourcefile ${BINARIES})
string(REPLACE ".cc" "" name ${sourcefile})
message(STATUS "    ${name}")
add_executable(${name} ${sourcefile})
target_link_libraries(${name} ${LIBS})
#check for PowerSupply
if(${PH2_POWERSUPPLY_FOUND})
   target_link_libraries(${name} ${LIBS} "${PH2_POWERSUPPLY_LIBRARIES}")
endif()
endforeach(sourcefile ${BINARIES})

message("--     ${BoldCyan}#### End ####${Reset}")

link_directories(${UHAL_UHAL_LIB_PREFIX})
link_directories(${PROJECT_SOURCE_DIR/lib})
