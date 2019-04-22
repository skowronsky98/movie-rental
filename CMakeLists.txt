cmake_minimum_required(VERSION 3.13)
project(PPProjekt C)

set(CMAKE_C_STANDARD 99)

add_executable(PPProjekt main.c node_list.c node_list.h file_clients.c movies.c node_list_movie.c)