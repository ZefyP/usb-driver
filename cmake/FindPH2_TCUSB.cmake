file(GLOB_RECURSE PH2_TCUSB_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../cmsph2_tcusb/src/USB_a.h)
if(PH2_TCUSB_SOURCE_DIR)
	
	message("${PH2_TCUSB_SOURCE_DIR}")	

        set(PH2_TCUSB_FOUND TRUE)
        #strip to the blank path
        get_filename_component(PH2_TCUSB_SOURCE_DIR "${PH2_TCUSB_SOURCE_DIR}" PATH)
        
        message("${PH2_TCUSB_SOURCE_DIR}")
        
#        find_library(PH2_TCUSB_LIBRARY_DIRS
#        NAMES
#        lib/libcmsph2_TCUSB.so
#        PATHS
#        ${PH2_TCUSB_SOURCE_DIR}/../
#        )

        find_library(PH2_TCUSB_LIBRARY_DIRS
        NAMES
        ../lib/libcmsph2_tcusb.so
        PATHS
        ${PH2_TCUSB_SOURCE_DIR}
        )
        message("${PH2_TCUSB_LIBRARY_DIRS}")


        #strip away the path
        get_filename_component(PH2_TCUSB_LIBRARY_DIRS "${PH2_TCUSB_LIBRARY_DIRS}" PATH)
        message("${PH2_TCUSB_LIBRARY_DIRS}")
        #strip again to get the path to the Ph2_USBInstDriver directory from the root of the FS
        get_filename_component(PH2_TCUSB_SOURCE_DIR "${PH2_TCUSB_LIBRARY_DIRS}" PATH)
        message("${PH2_TCUSB_LIBRARY_DIRS}")

        set(PH2_TCUSB_INCLUDE_DIRS
             ${PH2_TCUSB_SOURCE_DIR})

        file(GLOB_RECURSE PH2_TCUSB_LIBRARIES ${PH2_TCUSB_LIBRARY_DIRS}/*.so)
else(PH2_TCUSB_SOURCE_DIR)
        set(PH2_TCUSB_FOUND FALSE)

endif(PH2_TCUSB_SOURCE_DIR)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(PH2_TCUSB DEFAULT_MSG PH2_TCUSB_SOURCE_DIR)

  # show the PH2_USBINSTLIB_INCLUDE_DIRS and PH2_USBINSTLIB_LIBRARIES variables only in the advanced view
  mark_as_advanced(PH2_TCUSB_INCLUDE_DIRS PH2_TCUSB_LIBRARY_DIRS)

