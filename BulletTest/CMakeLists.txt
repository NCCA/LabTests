cmake_minimum_required(VERSION 3.3.1)
# Name of the project
set(PROJECT_NAME HelloBullet)
project(${PROJECT_NAME})

# Find Bullet Physics
find_package(Bullet REQUIRED)
#the file(GLOB...) allows for wildcard additions of our src dir
set(SOURCES ${PROJECT_SOURCE_DIR}/main.cpp  
)
# use C++ 11
set(CMAKE_CXX_STANDARD 11)





# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.

add_definitions(-O2 -D_FILE_OFFSET_BITS=64 -fPIC) 
add_definitions     ( ${BULLET_DEFINITIONS} )
include_directories ( ${BULLET_INCLUDE_DIRS} )
link_directories    ( ${BULLET_LIBRARY_DIRS} )
LINK_LIBRARIES(
 BulletDynamics BulletCollision LinearMath
)


# add exe and link libs this must be after the other defines
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS}  )

