project (HELLO)
add_subdirectory(src bin)

set (CMAKE_INSTALL_PREFIX /tmp)
install (FILES COPYRIGHT README DESTINATION share/doc/cmake/hello2)
install (PROGRAMS runhello.sh DESTINATION bin)
install (DIRECTORY doc/ DESTINATION share/doc/cmake/hello2)