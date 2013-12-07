set( TEST_INCLUDE "include" )
set( RESOURCES_DIR "resources" )
set( RESOURCES_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR}" )
set( TEST_INCLUDE_CONFIGURED "${CMAKE_CURRENT_BINARY_DIR}/include" )

configure_file( ${TEST_INCLUDE}/file_names.h.cmake ${TEST_INCLUDE_CONFIGURED}/file_names.h )

include_directories(
	${TEST_INCLUDE}
	${TEST_INCLUDE_CONFIGURED})

add_subdirectory( ipv4 )

# New cmake copy command
#file(COPY ${RESOURCES_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Old cmake copy command
set(destDir ${RESOURCES_OUTPUT_DIR})
set(srcDir ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_DIR})

make_directory(${destDir})

file(GLOB templateFiles RELATIVE ${srcDir} ${RESOURCES_DIR}/*)
message(STATUS "Files to be copied: ${templateFiles}")
foreach(templateFile ${templateFiles})
	set(srcTemplatePath ${srcDir}/${templateFile})
	if(NOT IS_DIRECTORY ${srcTemplatePath})
		message(STATUS "Copying ${templateFile}")
		configure_file(
			${srcTemplatePath}
			${destDir}/${templateFile}
			COPYONLY)
	endif(NOT IS_DIRECTORY ${srcTemplatePath})
endforeach(templateFile)
