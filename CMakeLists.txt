cmake_minimum_required(VERSION 3.6)
project(ASTRO)

set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/osx/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(SOURCE 
    Globals.cpp             
    Main.cpp 
    Application.cpp 
    Enemy_Mech.cpp 
    ModuleEnemies.cpp 
    ModuleInput.cpp 
    ModuleRender.cpp 
    ModuleTextures.cpp 
    Enemy.cpp 
    Enemy_RedBird.cpp       
    ModuleAudio.cpp         
    ModuleFadeToBlack.cpp   
    ModuleParticles.cpp     
    ModuleSceneIntro.cpp    
    ModuleWindow.cpp
    Enemy_BrownShip.cpp     
    ModuleCollision.cpp     
    ModuleFonts.cpp         
    ModulePlayer.cpp        
    ModuleSceneSpace.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARY})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)
