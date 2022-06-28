# diacpp-components
set(diacpp-components_FOUND ON)

set(diacpp-components_DIR ${CMAKE_CURRENT_LIST_DIR})

set(diacpp-components_INCLUDE_DIR "${diacpp-components_DIR}/include")
set(diacpp-components_INCLUDE_DIRS ${diacpp-components_INCLUDE_DIR})
set(diacpp-components_LIBRARY_DIR "${diacpp-components_DIR}/lib")

file(GLOB_RECURSE diacpp-components_LIBRARIES "${diacpp-components_LIBRARY_DIR}/*")

# Total files in the libraries folder
list(LENGTH diacpp-components_LIBRARIES diacpp-components_LIBRARIES_LEN)

# When run without a compiled library,
# it gets installed
if(diacpp-components_LIBRARIES_LEN EQUAL 0)
	add_subdirectory(${diacpp-components_DIR})
else()
	# Create the static library
	add_library(diacpp-components STATIC IMPORTED)

	# Set files to use when compiling
	set_property(TARGET diacpp-components
		PROPERTY
		INTERFACE_INCLUDE_DIRECTORIES ${diacpp-components_INCLUDE_DIRS}
	)

	set_property(TARGET diacpp-components
		PROPERTY
		IMPORTED_LOCATION ${diacpp-components_LIBRARIES}
	)
endif()
