SRC=src/sonus.c src/graphics.c src/state.c src/callback.c src/node.c src/resources.c

OBJ=$(SRC:.c=.o)
CFLAGS=-g -Werror -Wextra -Wall `pkg-config --cflags sdl2 SDL2_ttf portaudio-2.0`
LDFLAGS=`pkg-config --libs sdl2 SDL2_ttf portaudio-2.0` -lm
TARGET=sonus
CC=gcc
LD=gcc

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(LD) $^ -o $@ $(LDFLAGS)

.c.o:
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	$(RM) $(TARGET) $(OBJ)
