cmake_minimum_required(VERSION 3.23.1)
project(lvgl C CXX)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(SHARED_COMPONENTS_DIR /Users/seanalf/esp/shared-components/components)
list(
    APPEND
    SHARED_COMPONENTS_INCLUDE_DIRS
    ${SHARED_COMPONENTS_DIR}/alf_datetime/include
)
list(
    APPEND
    SHARED_COMPONENTS_SRCS
    ${SHARED_COMPONENTS_DIR}/alf_datetime/alf_datetime.c
)

set(APP_UI_ROOT_DIR /Users/seanalf/esp/ESP32/automated-door/components/app_ui)
set(APP_UI_PUBLIC_DIR ${APP_UI_ROOT_DIR}/public)
set(APP_PREFS_ROOT_DIR /Users/seanalf/esp/ESP32/automated-door/components/app_prefs)
set(TIMEZONE_ROOT_DIR /Users/seanalf/esp/ESP32/automated-door/components/timezone)

set(CONFIG_LV_BUILD_DEMOS OFF)
set(CONFIG_LV_BUILD_EXAMPLES OFF)

# set(CONFIG_LV_USE_THORVG_INTERNAL OFF)

# Set the correct FreeRTOS port for your system (e.g., Posix for WSL)
set(FREERTOS_PORT GCC_POSIX CACHE STRING "Port for FreeRTOS on Posix environment")

unset(USE_FREERTOS CACHE)

option(USE_FREERTOS "Enable FreeRTOS" OFF) # Turn this on to enable FreeRTOS

if(USE_FREERTOS)
    message(STATUS "FreeRTOS is enabled")

    # FreeRTOS integration when USE_FREERTOS is enabled
    add_library(freertos_config INTERFACE)
    target_include_directories(freertos_config SYSTEM INTERFACE ${PROJECT_SOURCE_DIR}/config)
    target_compile_definitions(freertos_config INTERFACE projCOVERAGE_TEST=0)

    # Add FreeRTOS as a subdirectory
    add_subdirectory(FreeRTOS)

    # FreeRTOS-specific include directories
    include_directories(${PROJECT_SOURCE_DIR}/FreeRTOS/include)
    include_directories(${PROJECT_SOURCE_DIR}/FreeRTOS/portable/ThirdParty/GCC/Posix)
    include_directories(${PROJECT_SOURCE_DIR}/config)

    # Add FreeRTOS sources
    file(GLOB FREERTOS_SOURCES
        "${PROJECT_SOURCE_DIR}/FreeRTOS/*.c"
        "${PROJECT_SOURCE_DIR}/FreeRTOS/portable/MemMang/heap_4.c"
        "${PROJECT_SOURCE_DIR}/FreeRTOS/portable/ThirdParty/GCC/Posix/*.c"
    )
else()
    message(STATUS "FreeRTOS is disabled")
    set(FREERTOS_SOURCES "") # No FreeRTOS sources if FreeRTOS is disabled
endif()

# Main include files of the project
include_directories(${PROJECT_SOURCE_DIR}/main/inc)

# Define options for LVGL with default values (OFF)
option(LV_USE_DRAW_SDL "Use SDL draw unit" OFF)
option(LV_USE_LIBPNG "Use libpng to decode PNG" OFF)
option(LV_USE_LIBJPEG_TURBO "Use libjpeg turbo to decode JPEG" OFF)
option(LV_USE_FFMPEG "Use libffmpeg to display video using lv_ffmpeg" OFF)
option(LV_USE_FREETYPE "Use freetype library" OFF)

# Set C and C++ standards
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Set the output path for the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

# Find and include SDL2 library
find_package(SDL2 REQUIRED)

# Add compile definitions based on the selected options
add_compile_definitions($<$<BOOL:${LV_USE_DRAW_SDL}>:LV_USE_DRAW_SDL=1>)
add_compile_definitions($<$<BOOL:${LV_USE_LIBPNG}>:LV_USE_LIBPNG=1>)
add_compile_definitions($<$<BOOL:${LV_USE_LIBJPEG_TURBO}>:LV_USE_LIBJPEG_TURBO=1>)
add_compile_definitions($<$<BOOL:${LV_USE_FFMPEG}>:LV_USE_FFMPEG=1>)

# Add LVGL subdirectory
add_subdirectory(lvgl)
target_include_directories(lvgl
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/auto-door-ui-app/src
    ${PROJECT_SOURCE_DIR}/auto-door-ui-app/src/pages
    ${PROJECT_SOURCE_DIR}/auto-door-ui-app/src/picker
    ${PROJECT_SOURCE_DIR}/auto-door-ui-app/src/picker/time_picker
    ${PROJECT_SOURCE_DIR}/auto-door-ui-app/src/picker/date_picker
    ${PROJECT_SOURCE_DIR}/auto-door-ui-app/src/popup
    ${SDL2_INCLUDE_DIRS}
    ${SHARED_COMPONENTS_INCLUDE_DIRS}
    ${APP_UI_PUBLIC_DIR}
    ${APP_PREFS_ROOT_DIR}
    ${TIMEZONE_ROOT_DIR}
)

set(ICONS_DIR ${PROJECT_SOURCE_DIR}/auto-door-ui-app/icons)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/auto-door-ui-app/src)
set(PAGES_DIR ${SOURCE_DIR}/pages)
set(PICKER_DIR ${SOURCE_DIR}/picker)
set(POPUP_DIR ${SOURCE_DIR}/popup)

list(APPEND ICONS_SRC
    ${ICONS_DIR}/add_device_icon.c
    ${ICONS_DIR}/check_icon.c
    ${ICONS_DIR}/connected_icon.c
    ${ICONS_DIR}/display_icon.c
    ${ICONS_DIR}/ex_icon.c
    ${ICONS_DIR}/gear_icon.c
    ${ICONS_DIR}/home_icon.c
    ${ICONS_DIR}/info_icon.c
    ${ICONS_DIR}/schedule_icon.c
    ${ICONS_DIR}/sync_icon.c
    ${ICONS_DIR}/timezone_icon.c
    ${ICONS_DIR}/undo_icon.c
    ${ICONS_DIR}/wifi_icon_lg.c
    ${ICONS_DIR}/wifi_icon1.c
    ${ICONS_DIR}/wifi_icon2.c
    ${ICONS_DIR}/wifi_icon3.c
    ${ICONS_DIR}/wifi_icon4.c
    ${ICONS_DIR}/wifi_error_icon.c
)

# Create the main executable, depending on the FreeRTOS option
add_executable(main
    ${APP_PREFS_ROOT_DIR}/auto_sleep_setting.c
    ${TIMEZONE_ROOT_DIR}/timezone.cpp
    ${PROJECT_SOURCE_DIR}/alf_hal.cpp
    ${PROJECT_SOURCE_DIR}/app_ui_prefs.cpp
    ${PROJECT_SOURCE_DIR}/events.c
    ${PROJECT_SOURCE_DIR}/main.c
    ${SOURCE_DIR}/app_ui.c
    ${SOURCE_DIR}/colors.c
    ${SOURCE_DIR}/content_area.c
    ${SOURCE_DIR}/events_priv.c
    ${SOURCE_DIR}/fixed_button.c
    ${SOURCE_DIR}/header.c
    ${SOURCE_DIR}/list_item.c
    ${SOURCE_DIR}/main_container.c
    ${SOURCE_DIR}/side_bar.c
    ${SOURCE_DIR}/string_helper.c
    ${SOURCE_DIR}/styles.c
    ${SOURCE_DIR}/timezone_manager.cpp
    ${SOURCE_DIR}/widgets.c
    ${SOURCE_DIR}/wifi_icon_manager.c
    ${PAGES_DIR}/add_device_settings_page.c
    ${PAGES_DIR}/auto_sleep_settings_page.c
    ${PAGES_DIR}/display_settings_page.c
    ${PAGES_DIR}/home_page.c
    ${PAGES_DIR}/page_navigation.c
    ${PAGES_DIR}/page.c
    ${PAGES_DIR}/schedule_page.c
    ${PAGES_DIR}/screen_brightness_page.c
    ${PAGES_DIR}/system_settings_page.c
    ${PAGES_DIR}/set_time_page.c
    ${PAGES_DIR}/timezone_settings_page.cpp
    ${PAGES_DIR}/wifi_settings_page.c
    ${PICKER_DIR}/picker.c
    ${PICKER_DIR}/date_picker/date_picker.c
    ${PICKER_DIR}/time_picker/time_picker.c
    ${POPUP_DIR}/popup.c
    ${ICONS_SRC}
    ${SHARED_COMPONENTS_SRCS}
)

# Define LVGL configuration as a simple include
target_compile_definitions(main PRIVATE LV_CONF_INCLUDE_SIMPLE)

if(MSVC)
    # target_link_libraries(main lvgl lvgl::examples lvgl::demos lvgl::thorvg ${SDL2_LIBRARIES})
    target_link_libraries(main lvgl ${SDL2_LIBRARIES})
else()
    # target_link_libraries(main lvgl lvgl::examples lvgl::demos lvgl::thorvg ${SDL2_LIBRARIES} m pthread)
    target_link_libraries(main lvgl ${SDL2_LIBRARIES} m pthread)
endif()

# Only link freertos_config if the FreeRTOS directory exists
if(USE_FREERTOS)
    target_link_libraries(main freertos_config)
endif()

# Custom target to run the executable
add_custom_target(run COMMAND ${EXECUTABLE_OUTPUT_PATH}/main DEPENDS main)

# Conditionally include and link SDL2_image if LV_USE_DRAW_SDL is enabled
if(LV_USE_DRAW_SDL)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
    find_package(SDL2_image REQUIRED)
    target_include_directories(lvgl PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(main ${SDL2_IMAGE_LIBRARIES})
endif()

# Conditionally include and link libpng if LV_USE_LIBPNG is enabled
if(LV_USE_LIBPNG)
    find_package(PNG REQUIRED)
    target_include_directories(lvgl PUBLIC ${PNG_INCLUDE_DIRS})
    target_link_libraries(main ${PNG_LIBRARIES})
endif()

# Conditionally include and link libjpeg-turbo if LV_USE_LIBJPEG_TURBO is enabled
if(LV_USE_LIBJPEG_TURBO)
    find_package(JPEG REQUIRED)
    target_include_directories(lvgl PUBLIC ${JPEG_INCLUDE_DIRS})
    target_link_libraries(main ${JPEG_LIBRARIES})
endif()

# Conditionally include and link FFmpeg libraries if LV_USE_FFMPEG is enabled
if(LV_USE_FFMPEG)
    target_link_libraries(main avformat avcodec avutil swscale z)
endif()

# Conditionally include and link FreeType if LV_USE_FREETYPE is enabled
if(LV_USE_FREETYPE)
    find_package(Freetype REQUIRED)
    target_include_directories(lvgl PUBLIC ${FREETYPE_INCLUDE_DIRS})
    target_link_libraries(main ${FREETYPE_LIBRARIES})
endif()

# On Windows, GUI applications do not show a console by default,
# which hides log output. This ensures a console is available for logging.
if(WIN32)
    if(MSVC)
        target_link_options(main PRIVATE "/SUBSYSTEM:CONSOLE")
    else()
        target_link_options(main PRIVATE "-mconsole")
    endif()
endif()

target_compile_options(main PRIVATE
    -pedantic-errors
    -Wall

    -Wdeprecated
    -Wdouble-promotion
    -Wempty-body
    -Wextra
    -Wformat
    -Wformat-security
    -Wuninitialized

    -Wmissing-prototypes
    -Wpointer-arith
    -Wmultichar
    -Wpedantic # ignored for now, we convert functions to pointers for properties table.
    -Wreturn-type
    -Wshadow
    -Wshift-negative-value
    -Wsizeof-pointer-memaccess
    -Wtype-limits
    -Wundef
    -Wuninitialized
    -Wunreachable-code
    -Wfloat-conversion
    -Wstrict-aliasing
)

# Apply additional compile options if the build type is Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug mode enabled")

    target_compile_options(lvgl PRIVATE
        -pedantic-errors
        -Wall

        # -Wclobbered
        -Wdeprecated
        -Wno-double-promotion
        -Wempty-body
        -Wextra
        -Wno-format
        -Wformat-security
        -Wuninitialized

        # -Wmissing-prototypes
        -Wpointer-arith
        -Wmultichar
        -Wno-pedantic # ignored for now, we convert functions to pointers for properties table.
        -Wreturn-type
        -Wshadow
        -Wshift-negative-value
        -Wsizeof-pointer-memaccess
        -Wtype-limits
        -Wundef
        -Wuninitialized
        -Wno-unreachable-code
        -Wfloat-conversion
        -Wstrict-aliasing
    )

    if(ASAN)
        message(STATUS "AddressSanitizer enabled")

        # Add AddressSanitizer flags
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address")
    else()
        message(STATUS "AddressSanitizer disabled")
    endif()
endif()
