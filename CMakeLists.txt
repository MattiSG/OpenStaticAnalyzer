cmake_minimum_required (VERSION 3.8.0)

# Disable other configurations than Release and Debug
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)

# Set the default build type to release
if (NOT CMAKE_BUILD_TYPE )
  set (CMAKE_BUILD_TYPE Release CACHE STRING "Build Type: Release or Debug" FORCE)
endif()

project (OSA VERSION 1.0.0)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXECUTABLE_OUTPUT_PATH})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXECUTABLE_OUTPUT_PATH})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${LIBRARY_OUTPUT_PATH})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG  ${LIBRARY_OUTPUT_PATH})
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
set (CMAKE_SUPPORT_FOLDER_NAME CMakeSupportTargets)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

include (BuildInfo)
include (UtilityFunctions)
include (PlatformOptions)
include (CodebaseOptions)
include (cotire)

add_subdirectory (cl/DuplicatedCodeFinder)
add_subdirectory (cl/FindBugs2Graph)
add_subdirectory (cl/GenericConfig)
add_subdirectory (cl/GraphDump)
add_subdirectory (cl/GraphMerge)
add_subdirectory (cl/JAN2ChangePath)
add_subdirectory (cl/JAN2Lim)
add_subdirectory (cl/JANFilter)
add_subdirectory (cl/JANLink)
add_subdirectory (cl/LIM2Metrics)
add_subdirectory (cl/MetricHunter)
add_subdirectory (cl/PMD2Graph)
add_subdirectory (cl/OpenStaticAnalyzerJava)

add_subdirectory (wrapper/AbstractWrapperLib)
add_subdirectory (wrapper/AnalyzerWrapperConfig)
add_subdirectory (wrapper/AntWrapper)
add_subdirectory (wrapper/EnvironmentSetup)
add_subdirectory (wrapper/exewrapper)
add_subdirectory (wrapper/JarWrapper)
add_subdirectory (wrapper/JavacWrapper)
add_subdirectory (wrapper/WrapperEnvironmentConfig)

add_subdirectory (lib/common)
add_subdirectory (lib/controller)
add_subdirectory (lib/csi)
add_subdirectory (lib/genealogy)
add_subdirectory (lib/graph)
add_subdirectory (lib/graphsupport)
add_subdirectory (lib/io)
add_subdirectory (lib/java)
add_subdirectory (lib/lim)
add_subdirectory (lib/lim2graph)
add_subdirectory (lib/limmetrics)
add_subdirectory (lib/rul)
add_subdirectory (lib/strtable)
add_subdirectory (lib/threadpool)

add_subdirectory (java/lib/revision)
add_subdirectory (java/lib/graphlib)
add_subdirectory (java/lib/graphsupportlib)
add_subdirectory (java/cl/JAN)
add_subdirectory (java/wrapper/JColumbusAntWrapper)


add_subdirectory (3rdparty)
add_subdirectory (OpenStaticAnalyzer)

