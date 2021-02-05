CC=gcc
CFLAGS=-O3 -Wall -std=c99 -DBUILD_DLL -D_XOPEN_SOURCE=500
LDFLAGS=-shared -static-libgcc -s
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=albom.dll

all: $(SOURCES) $(TARGET)

clean:
	-rm src/*.o
	-rm -r build

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -Wl,--out-implib=lib$(TARGET).a $(LDFLAGS)
	-mkdir build
	-mv $(TARGET) build
	-mv lib$(TARGET).a build
	-cd ..
