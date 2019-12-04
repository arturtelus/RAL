cmake_minimum_required(VERSION 3.15)

project("RAL" VERSION 0.1.1.1
	DESCRIPTION "RAII framework for OpenAL and OpenAL-soft (+utilities)"
	LANGUAGES C CXX
)

set(RAL_LIB_NAME "ral")

add_library(${RAL_LIB_NAME} STATIC 
	"${PROJECT_SOURCE_DIR}/src/ral_error.cpp"
	"${PROJECT_SOURCE_DIR}/src/ral_device.cpp"
	"${PROJECT_SOURCE_DIR}/src/ral_context.cpp"
	"${PROJECT_SOURCE_DIR}/src/ral_listener.cpp"
	"${PROJECT_SOURCE_DIR}/src/ral_wave.cpp"
)
add_library(RAL::RAL ALIAS ${RAL_LIB_NAME})
target_include_directories(${RAL_LIB_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_compile_features(${RAL_LIB_NAME} PUBLIC cxx_std_17)
set_target_properties(${RAL_LIB_NAME} PROPERTIES
	CXX_EXTENSIONS OFF
	CXX_STANDARD 17
)
target_compile_definitions(${RAL_LIB_NAME} PRIVATE 
	$<$<CONFIG:Debug>:DEBUG>
	$<$<BOOL:${USE_WIN_CREATIVE_OPENAL}>:USE_CREATIVE_OPENAL>
)

#External libraries
find_package(openal-soft CONFIG REQUIRED)
target_link_libraries(${RAL_LIB_NAME} PUBLIC OpenAL::OpenAL)

#TODO: creative openal

#Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
	if(DOXYGEN_DOT_EXECUTABLE)
		set(USE_DOXYGEN_DOT "YES")
	endif()
	configure_file("${PROJECT_SOURCE_DIR}/Doxyfile.in" "${PROJECT_BINARY_DIR}/Doxyfile" @ONLY)
	add_custom_target(BuildDoxygenDocs ALL COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
		COMMENT "Doxygen, generating docs."
	VERBATIM)
	add_custom_command(TARGET BuildDoxygenDocs POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_BINARY_DIR}/docs/html" "${PROJECT_SOURCE_DIR}/docs"
	COMMENT "Copy docs into project directory.")
else()
	message(STATUS "Doxygen not found!")
endif()

#TODO package
#TODO installation