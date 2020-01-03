project(Rtype)
cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INCLUDE_CLIENT
  ./Client/Components/
  ./Client/include/
  ./Client/Systems/Headers/
  ./Client/Components/
)

set(SOURCES_CLIENT
  ./Client/main.cpp
  ./Client/Components/Factory.cpp
  ./Client/Systems/Graphical/systemEvent.cpp
  ./Client/Systems/Graphical/systemDraw.cpp
  ./Client/Systems/Graphical/systemPlayerActions.cpp
  ./Client/Systems/Audio/systemSound.cpp
  ./Client/Systems/Audio/SoundLib.cpp
  ./Client/Systems/Graphical/GraphicalLib.cpp
  ./Client/Components/ComponentTypeList.cpp
  ./Client/ClientGame.cpp
  ./Client/preGameWaitRoom.cpp
  ./Client/introMainMenu.cpp
  ./Client/Levels.cpp
  ./Client/Start.cpp
  ./Client/ClientGameNetwork.cpp
)

set(INCLUDE_SERVER
  ./Server/System/systemApplyDmg.hpp
  ./Server/System/systemHorizalMove.hpp
  ./Server/System/systemHitbox.hpp
  ./Server/System/systemSpawn.hpp
  ./Server/Components/ComponentTypeList.hpp
  ./Server/Components/Factory.hpp
  ./Server/Mobs/IMob.hpp
  ./Server/include/Client.hpp
  ./Server/include/Game.hpp
  ./Server/include/Room.hpp
  ./Server/include/Server.hpp
  ./Server/include/Session.hpp
  ./Server/include/Thread.hpp
)

set(SOURCES_SERVER
  ./Server/src/main.cpp
  ./Server/System/systemApplyDmg.cpp
  ./Server/System/systemHorizalMove.cpp
  ./Server/System/systemHitbox.cpp
  ./Server/System/systemSpawn.cpp
  ./Server/Components/ComponentTypeList.cpp
  ./Server/Components/Factory.cpp
  ./Server/src/Client.cpp
  ./Server/src/Game.cpp
  ./Server/src/Room.cpp
  ./Server/src/Server.cpp
  ./Server/src/Session.cpp
  ./Server/src/Socket.cpp
  ./Server/src/Thread.cpp
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include_directories(${CMAKE_INCLUDE_PATH} Client/include)
include_directories(${CMAKE_INCLUDE_PATH} Client/Systems/Headers)
include_directories(${CMAKE_INCLUDE_PATH} Client/Components)
include_directories(${CMAKE_INCLUDE_PATH} Server/System)
include_directories(${CMAKE_INCLUDE_PATH} Server/Components)
include_directories(${CMAKE_INCLUDE_PATH} Server/include)
include_directories(${CMAKE_INCLUDE_PATH} Server/Mobs)

add_executable(r-type_client ${SOURCES_CLIENT} ${INCLUDE_CLIENT})
target_link_libraries(r-type_client ${CONAN_LIBS} -g3 -std=c++2a -lboost_system -lboost_serialization -lpthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio)

add_executable(r-type_server ${SOURCES_SERVER} ${INCLUDE_SERVER})
target_link_libraries(r-type_server ${CONAN_LIBS} -g3 -std=c++2a -lboost_system -lboost_serialization -lpthread -ldl)
