cmake_minimum_required(VERSION 3.10)

project(Wasm2C2PSP C)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Define the executable target with your source files
add_executable(${PROJECT_NAME} src/main.c src/app.c)

# Include PSP specific directories
include_directories(${PSPDEV}/include)
link_directories(${PSPDEV}/lib)

# Include directories for w2c2
include_directories(w2c2/w2c2/)
include_directories(w2c2/wasi)
include_directories(./src/)

# Add subdirectory for w2c2/wasi (make sure there's a CMakeLists.txt there)
add_subdirectory(w2c2/wasi)

# Link libraries for the project
target_link_libraries(${PROJECT_NAME} PRIVATE
    pspdebug
    pspge
    pspdisplay
    pspctrl
    pspgu
    psprtc
    w2c2wasi
    raylib
    png
    z
    # GLUT
    # GLU
    # GL
    pspvfpu
    SDL2
    GL
    GLU
    # glut
    z
    pspvfpu
    psphprm
    pspsdk
    pspctrl
    pspumd
    psprtc
    psppower
    pspgum
    pspgu
    pspaudiolib
    pspaudio
    psphttp
    pspssl
    pspwlan
    pspnet_adhocmatching
    pspnet_adhoc
    pspnet_adhocctl
    m
    pspvram
)

# If PSP environment is set, create the PBP file
if(PSP)
    # Make sure create_pbp_file() is defined elsewhere (in your PSP toolchain or elsewhere)
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
        VERSION 01.00
    )
endif()
