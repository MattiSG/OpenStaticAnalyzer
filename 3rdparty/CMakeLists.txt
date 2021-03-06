include(ExternalProject)

# All the external static library names should follow this naming convention:
# Linux:
#   lib<name>.a
# Windows:
#   <name>.lib

file (MAKE_DIRECTORY ${COLUMBUS_3RDPARTY_INSTALL_DIR}/bin)
file (MAKE_DIRECTORY ${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib)
file (MAKE_DIRECTORY ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include)

########################### zlib #########################

ExternalProject_Add(zlib
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/zlib
    PATCH_COMMAND git clean -x -d -f
          COMMAND git reset --hard
          COMMAND git apply --ignore-whitespace ${CMAKE_CURRENT_SOURCE_DIR}/CMake/zlib.patch
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${COLUMBUS_3RDPARTY_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
)

# This extra rename step is needed on windows to rename the library to be compatible with the CMake library naming convention.
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  ExternalProject_Add_Step (zlib rename
    DEPENDEES BUILD INSTALL
    COMMAND ${CMAKE_COMMAND} -E rename ${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/zlibstatic$<$<CONFIG:Debug>:d>.lib ${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/z.lib
    LOG 1
  )
endif()


########################### boost ########################
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  if (COLUMBUS_64BIT)
    set (BOOST_ADDRESS_MODEL address-model=64)
  endif ()
endif ()  

ExternalProject_Add(boost
    DEPENDS zlib
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/boost
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ${COMMAND_PREFIX}bootstrap${SCRIPT_EXT}
    BUILD_COMMAND ${COMMAND_PREFIX}b2 --reconfigure --build-dir=${CMAKE_CURRENT_BINARY_DIR}/boost-prefix --prefix=${COLUMBUS_3RDPARTY_INSTALL_DIR} -j8 --with-filesystem --with-system --with-date_time --with-iostreams --with-graph --with-regex --with-thread --with-math --layout=system variant=$<$<CONFIG:Debug>:debug>$<$<CONFIG:Release>:release>  runtime-link=static architecture=x86  threading=multi ${BOOST_ADDRESS_MODEL} link=static  -sZLIB_INCLUDE=${COLUMBUS_3RDPARTY_INSTALL_DIR}/include -sZLIB_LIBPATH=${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib -sZLIB_BINARY=z -sNO_ZLIB=0 -sNO_BZIP2=1   headers
          COMMAND ${COMMAND_PREFIX}b2 --reconfigure --build-dir=${CMAKE_CURRENT_BINARY_DIR}/boost-prefix --prefix=${COLUMBUS_3RDPARTY_INSTALL_DIR} -j8 --with-filesystem --with-system --with-date_time --with-iostreams --with-graph --with-regex --with-thread --with-math --layout=system variant=$<$<CONFIG:Debug>:debug>$<$<CONFIG:Release>:release>  runtime-link=static architecture=x86  threading=multi ${BOOST_ADDRESS_MODEL} link=static  -sZLIB_INCLUDE=${COLUMBUS_3RDPARTY_INSTALL_DIR}/include -sZLIB_LIBPATH=${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib -sZLIB_BINARY=z -sNO_ZLIB=0 -sNO_BZIP2=1   install
    INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "No sepearate installation step is needed."
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
)

# This extra rename step is needed on windows to rename the libraries to be compatible with the CMake library naming convention.
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  set (BOOST_LIBRARY_NAMES_TO_RENAME
    iostreams
    graph
    date_time
    chrono
    math_c99
    math_c99f
    math_c99l
    math_tr1
    math_tr1f
    math_tr1l
    regex
    system
    filesystem
    thread
  )

  foreach (LIB ${BOOST_LIBRARY_NAMES_TO_RENAME})
    set (BOOST_RENAME_COMMAND ${BOOST_RENAME_COMMAND} COMMAND ${CMAKE_COMMAND} -E rename "${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/libboost_${LIB}.lib" "${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/boost_${LIB}.lib")
  endforeach()
  
  ExternalProject_Add_Step (boost rename
    DEPENDEES BUILD INSTALL
    ${BOOST_RENAME_COMMAND}
    LOG 1
  )
endif ()


########################### xerces-c #########################

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
  ExternalProject_Add( xerces-c
      SVN_REPOSITORY https://svn.apache.org/repos/asf/xerces/c/tags/Xerces-C_3_1_4
      BUILD_IN_SOURCE 1
      UPDATE_COMMAND ""
      CONFIGURE_COMMAND ./reconf
                COMMAND ./configure --disable-shared -disable-network --disable-transcoder-icu --prefix=${COLUMBUS_3RDPARTY_INSTALL_DIR}
      BUILD_COMMAND make -j8 all
      INSTALL_COMMAND make install
      LOG_DOWNLOAD 1
      LOG_UPDATE 1
      LOG_CONFIGURE 1
      LOG_BUILD 1
      LOG_INSTALL 1
  )

elseif (CMAKE_SYSTEM_NAME STREQUAL Windows)
  
  if (COLUMBUS_64BIT)
    set (XERCESC_BUILD_OUTPUT_DIR Win64)
  else()
    set (XERCESC_BUILD_OUTPUT_DIR Win32)
  endif ()
  
  ExternalProject_Add( xerces-c
      SVN_REPOSITORY https://svn.apache.org/repos/asf/xerces/c/tags/Xerces-C_3_1_4
      BUILD_IN_SOURCE 1
      UPDATE_COMMAND ""
      CONFIGURE_COMMAND ${CMAKE_COMMAND} -E echo "No configuration is required."
      BUILD_COMMAND msbuild projects/Win32/VC14/xerces-all/xerces-all.sln /m /t:XercesLib "/p:Configuration=Static $<CONFIG>" /p:Platform=${VS_PLATFORM} /p:PlatformToolset=${CMAKE_VS_PLATFORM_TOOLSET}
      INSTALL_COMMAND ${CMAKE_COMMAND} "-DCOPY_SOURCE=${CMAKE_CURRENT_BINARY_DIR}/xerces-c-prefix/src/xerces-c/src/xercesc/" "-DCOPY_TARGET=${COLUMBUS_3RDPARTY_INSTALL_DIR}/include/xercesc" -DCOPY_PATTERN=*.hpp -P ${CMAKE_CURRENT_SOURCE_DIR}/CMake/SearchAndCopyFiles.cmake
              COMMAND ${CMAKE_COMMAND} "-DCOPY_SOURCE=${CMAKE_CURRENT_BINARY_DIR}/xerces-c-prefix/src/xerces-c/src/xercesc/" "-DCOPY_TARGET=${COLUMBUS_3RDPARTY_INSTALL_DIR}/include/xercesc" -DCOPY_PATTERN=*.c -P ${CMAKE_CURRENT_SOURCE_DIR}/CMake/SearchAndCopyFiles.cmake
              COMMAND ${CMAKE_COMMAND} -E copy "Build/${XERCESC_BUILD_OUTPUT_DIR}/VC14/Static $<CONFIG>/xerces-c_static_3$<$<CONFIG:Debug>:d>.lib" ${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/xerces-c.lib
      LOG_DOWNLOAD 1
      LOG_UPDATE 1
      LOG_CONFIGURE 1
      LOG_BUILD 1
      LOG_INSTALL 1
  )
endif ()

########################### PMD #########################

set (PMD_PACKAGE_VERSION pmd-bin-5.2.3)
set (PMD_DIST_PACKAGE ${CMAKE_CURRENT_SOURCE_DIR}/PMD/pmd-dist/target/${PMD_PACKAGE_VERSION}.zip)
set (PMD_PACKAGE ${COLUMBUS_3RDPARTY_INSTALL_DIR}/PMD.zip)

add_custom_command (
  OUTPUT ${PMD_PACKAGE}
  COMMAND mvn${MVN_POSTFIX} package -DskipTests > ${CMAKE_CURRENT_BINARY_DIR}/PMD-build.log
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/PMD/pmd-dist/target/ ${CMAKE_COMMAND} -E remove_directory PMD
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/PMD/pmd-dist/target/ ${CMAKE_COMMAND} -E tar xf ${PMD_DIST_PACKAGE}
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/PMD/pmd-dist/target/ ${CMAKE_COMMAND} -E rename ${PMD_PACKAGE_VERSION} PMD
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/PMD/pmd-dist/target/ ${CMAKE_COMMAND} -E tar cf ${PMD_DIST_PACKAGE} --format=zip PMD
  COMMAND ${CMAKE_COMMAND} -E copy ${PMD_DIST_PACKAGE} ${PMD_PACKAGE}
  COMMENT "Building PMD"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/PMD
)

add_custom_target (
  PMD
  DEPENDS ${PMD_PACKAGE}
)

set_target_properties (PMD PROPERTIES FOLDER "ExternalProjectTargets/pmd")
