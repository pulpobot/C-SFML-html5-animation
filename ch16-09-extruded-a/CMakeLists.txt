cmake_minimum_required(VERSION 3.8)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

#TODO: Add more platforms (Linux and MACOSX)
#build configuration
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})
get_filename_component(BUILDS_PATH ${CMAKE_CURRENT_SOURCE_DIR} PATH)
set(RELEASE_PATH ${BUILDS_PATH}/_builds)

#add compiler static flags
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

#CXX Standards
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
#source files
set(PROJECT_SOURCE_DIR "src/")
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}*.cpp")

#executable
set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${SOURCES})
set_target_properties(${EXECUTABLE_NAME}
        PROPERTIES
        CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RELEASE_PATH}
        RUNTIME_OUTPUT_DIRECTORY "${RELEASE_PATH}"
        )

#region dependencies
get_filename_component(REPO_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set(SHARED_DEPS ${REPO_FOLDER}/shared-deps/)
set(SFML_ROOT "${SHARED_DEPS}/SFML-2.4.2/")
set(RESOURCES_ROOT "${CMAKE_SOURCE_DIR}/res")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    #include the dir so it can be used by the compiler and the IDE
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

    #add any non-static.dll to a list to be copied to the same place as the executable
    file(GLOB_RECURSE SFML_SHARED_LIBRARIES "${SFML_ROOT}lib/*.dll")
endif()

set(MINGW_PATH "C:/MinGW/bin")
if (MINGW AND EXISTS "${MINGW_PATH}")
set(MINGW_SHARED_LIBRARIES "${MINGW_PATH}/libgcc_s_dw2-1.dll" "${MINGW_PATH}/libstdc++-6.dll")
message("-- Copying MinGW Shared Libraries")
else()
    message("-- Not able to copy MinGW Shared Libraries")
endif()

file(COPY ${SFML_SHARED_LIBRARIES} ${MINGW_SHARED_LIBRARIES} DESTINATION "${RELEASE_PATH}" USE_SOURCE_PERMISSIONS)

#copy resources folder if there's any
if (EXISTS "${RESOURCES_ROOT}")
    file(COPY "${RESOURCES_ROOT}" DESTINATION "${RELEASE_PATH}" USE_SOURCE_PERMISSIONS)
endif()
#endregion