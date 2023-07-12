cmake_minimum_required(VERSION 3.2)
project(Concordo VERSION 0.1 LANGUAGES CXX )
set ( CMAKE_CXX_FLAGS "-Wall" )
include_directories( include )
add_executable( program
src/main.cpp
src/usuario.cpp
src/servidor.cpp
src/gerenciador.cpp
src/sistema.cpp
src/canal.cpp
src/mensagem.cpp)