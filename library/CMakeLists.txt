MESSAGE(STATUS " ")

# Includes
# Find source files
file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cc)

# Power supplt
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
set(LIBS ${LIBS} usb ${PH2_TCUSB_LIBRARIES})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{TCUSBFlag}")
endif(${PH2_TCUSB_FOUND})

file(GLOB BINARIES RELATIVE ${PROJECT_SOURCE_DIR}/libraries *.cc)

####################################
## EXECUTABLES
####################################

message("--     ${BoldCyan}#### Adding the LIBRARY: ####${Reset}")
# Add the library
add_library(cmsph2_tcusb_pspoh SHARED ${SOURCES} ${HEADERS})
TARGET_LINK_LIBRARIES(cmsph2_tcusb_pspoh ${LIBS})
message("${SOURCES} ${HEADERS}")
