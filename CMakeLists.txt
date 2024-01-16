cmake_minimum_required(VERSION 3.10)
project(simple-im-ibus)

find_package(PkgConfig REQUIRED)
# libibus-1.0-dev
pkg_check_modules(IBus REQUIRED ibus-1.0)
if(IBus_FOUND)
  include_directories(${IBus_INCLUDE_DIRS})
  link_directories(${IBus_LIBRARY_DIRS})
else()
endif(IBus_FOUND)

add_executable(${PROJECT_NAME} main.cpp module.cpp)
target_link_libraries(${PROJECT_NAME} ${IBus_LIBRARIES})
  
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.xml.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.xml"
  @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.xml" DESTINATION "${CMAKE_INSTALL_DATADIR}/ibus/component")
install(DIRECTORY icons DESTINATION "${CMAKE_INSTALL_DATADIR}/ibus-simpleim" FILES_MATCHING PATTERN "*.png")
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}/ibus-simpleim)