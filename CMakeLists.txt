cmake_minimum_required(VERSION 3.7)

project(SmartHome LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS
  Core Quick Network Positioning Location OpenGL Sql Multimedia LinguistTools Svg
  REQUIRED)

set(TS_FILES
    translations/SmartHome_en_US.ts
    translations/SmartHome_de_DE.ts
    translations/SmartHome_pl_PL.ts
    translations/SmartHome_ru_RU.ts)

set(SOURCES
    main.cpp
    src/datetime/DateTimeSource.cpp
    src/datetime/DateTimeSource.h
    src/location/LocationSource.cpp
    src/location/LocationSource.h
    src/weather/WeatherSource.cpp
    src/weather/WeatherSource.h
    src/weather/WeatherInfo.h
    src/weather/WeatherForecastModel.cpp
    src/weather/WeatherForecastModel.h
    src/network/NetworkManager.cpp
    src/network/NetworkManager.h
    src/alarm/AlarmManager.cpp
    src/alarm/AlarmManager.h
    src/alarm/AlarmData.cpp
    src/alarm/AlarmData.h
    src/alarm/AlarmObserver.cpp
    src/alarm/AlarmObserver.h
    src/alarm/DateUtils.cpp
    src/alarm/DateUtils.h
    src/database/DbManager.cpp
    src/database/DbManager.h
    src/database/Alarm.h
    src/database/Settings.h
    src/settings/SettingsManager.cpp
    src/settings/SettingsManager.h
    src/settings/theme/AbstractTheme.h
    src/settings/theme/LightTheme.cpp
    src/settings/theme/LightTheme.h
    src/settings/theme/DarkTheme.cpp
    src/settings/theme/DarkTheme.h
    src/settings/model/WallpaperModel.cpp
    src/settings/model/WallpaperModel.h
    src/settings/model/ThemeModel.cpp
    src/settings/model/ThemeModel.h
    src/settings/model/LanguageModel.cpp
    src/settings/model/LanguageModel.h
    )

if(ANDROID)
    add_library(${PROJECT_NAME} SHARED
      ${SOURCES}
      qml.qrc
      resources.qrc
      translations.qrc
      ${TS_FILES}
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND cp ${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}
                 android-build/libs/arm64-v8a/
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
else()
    add_executable(${PROJECT_NAME}
      ${SOURCES}
      qml.qrc
      resources.qrc
      translations.qrc
      ${TS_FILES}
    )
endif()

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt5::Core Qt5::Quick Qt5::Network Qt5::Positioning Qt5::Location
  Qt5::OpenGL Qt5::Multimedia Qt5::Sql Qt5::Svg)

if(RASPBERRY_PI)
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mfloat-abi=hard --sysroot=~/raspberry/sysroot -Wl,-O1 -Wl,-rpath,/usr/local/Qt-5.12.5/lib -Wl,-rpath-link,~/raspberry/sysroot/opt/vc/lib -Wl,-rpath-link,~/raspberry/sysroot/usr/lib/arm-linux-gnueabihf -Wl,-rpath-link,~/raspberry/sysroot/lib/arm-linux-gnueabihf")
  install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${PROJECT_NAME})
endif()
