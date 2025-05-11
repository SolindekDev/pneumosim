CC = clang
CCPP = clang++

OS := $(shell uname)
ifeq ($(OS), Linux)
	CFLAGS = -Wall -Wextra -O2 -I include -Wno-unused-parameter -Wno-unused-private-field -Icimgui/imgui -Icimgui -Icimgui/imgui/backends
	LDFLAGS = imgui_bridge.cpp cimgui/cimgui.cpp cimgui/imgui/*.cpp cimgui/imgui/backends/imgui_impl_sdl2.cpp cimgui/imgui/backends/imgui_impl_opengl3.cpp -Lcimgui/cimgui.so -Icimgui/imgui -Icimgui -Icimgui/imgui/backends -lSDL2 -lSDL2_ttf -lSDL2_image -lm -lGL -lGLEW 
else ifeq ($(OS), Darwin)
	CFLAGS = -Wall -Wextra -O2 $(shell pkg-config sdl2 sdl2_image sdl2_ttf --cflags) -I include -Wno-unused-parameter -Wno-unused-private-field
	LDFLAGS = $(shell pkg-config sdl2 sdl2_image sdl2_ttf --libs) -lm
else
	$(error Unsupported operating system: $(OS))
endif

SRC_DIRS = ./core ./pneum ./gui ./components
SRC_FILES = $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))
OBJ_FILES = $(SRC_FILES:.c=.o)

TARGET = pneumosim

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CCPP) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

.PHONY: all clean