set(this server)
project(${this})

set(BOOST_ROOT /home/fume/projects/cpp/boost_1_80_0)

if(DEFINED BOOST_ROOT)
    message("BOOST_ROOT is defined as ${BOOST_ROOT}")
elseif(DEFINED ENV{BOOST_ROOT})
    message("BOOST_ROOT is defined from env as ${BOOST_ROOT}")
else()
    message( FATAL_ERROR "BOOST_ROOT is not setted. Try flag -D BOOST_ROOT=<path to boost root>" )
endif()

set(CMAKE_CXX_STANDARD 17)
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package (Boost REQUIRED COMPONENTS system ) 

FILE(GLOB_RECURSE SOURCES "src/*.cpp")
FILE(GLOB_RECURSE HEADERS "include/*.h")

if (Boost_FOUND) 
    include_directories (SYSTEM ${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы
    add_executable (${this} ${SOURCES} ${HEADERS}) # Создаем исполняемый файл для нашего проекта
    target_link_libraries (${this} ${Boost_LIBRARIES}) # подключаем библиотеку
    target_include_directories(${this} PRIVATE ../external/)
    target_include_directories(${this} PRIVATE "include/")
endif ()
