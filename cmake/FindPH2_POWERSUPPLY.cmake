file(GLOB_RECURSE PH2_POWERSUPPLY_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../power_supply/src/PowerSupply.h)
if(PH2_POWERSUPPLY_SOURCE_DIR)
      set(PH2_POWERSUPPLY_FOUND TRUE)
      #strip to the blank path
      get_filename_component(PH2_POWERSUPPLY_SOURCE_DIR "${PH2_POWERSUPPLY_SOURCE_DIR}" PATH)
message ("${PH2_POWERSUPPLY_SOURCE_DIR}")
         find_library(PH2_POWERSUPPLY_LIBRARY_DIRS
         NAMES
           lib/libPowerSupply.so
         PATHS
         ${PH2_POWERSUPPLY_SOURCE_DIR}/..
         )

         #strip away the path
         get_filename_component(PH2_POWERSUPPLY_LIBRARY_DIRS "${PH2_POWERSUPPLY_LIBRARY_DIRS}" PATH)
         #strip again to get the path to the Ph2_USBInstDriver directory from the root of the FS
         #get_filename_component(PH2_POWERSUPPLY_SOURCE_DIR "${PH2_POWERSUPPLY_LIBRARY_DIRS}" PATH)

message ("${PH2_POWERSUPPLY_SOURCE_DIR}")

         set(PH2_POWERSUPPLY_INCLUDE_DIRS
             ${PH2_POWERSUPPLY_SOURCE_DIR})

	message ("${PH2_POWERSUPPLY_INCLUDE_DIRS}")
         file(GLOB_RECURSE PH2_POWERSUPPLY_LIBRARIES ${PH2_POWERSUPPLY_LIBRARY_DIRS}/*.so)
 
else(PH2_POWERSUPPLY_SOURCE_DIR)
         set(PH2_POWERSUPPLY_FOUND FALSE)

endif(PH2_POWERSUPPLY_SOURCE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PH2_PowerSupply DEFAULT_MSG PH2_POWERSUPPLY_SOURCE_DIR)
  # show the PH2_USBINSTLIB_INCLUDE_DIRS and PH2_USBINSTLIB_LIBRARIES variables only in the advanced view
  mark_as_advanced(PH2_POWERSUPPLY_INCLUDE_DIRS PH2_POWERSUPPLY_LIBRARY_DIRS)

