cmake_minimum_required(VERSION 3.12)

project(need-for-ce
        VERSION 0.1.0
        DESCRIPTION "A simple car game"
        LANGUAGES CXX)

include(GNUInstallDirs)
add_definitions(-D_GNU_SOURCE)
add_executable(need-for-ce NeedForCE.cpp gioco.cpp livello.cpp levelgenerator.cpp player.cpp oggetto.cpp mappa.cpp)
target_link_libraries(NeedForCE -lncurses)

target_include_directories(NeedForCE PRIVATE .)

install(TARGETS need-for-ce RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${PROJECT_SOURCE_DIR}/Uninstall.cmake")
