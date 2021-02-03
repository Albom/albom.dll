CC=gcc
CFLAGS=-O3 -Wall -std=c99 -DBUILD_DLL
LDFLAGS=-shared -static-libgcc -s
SOURCES=src/mymath.c src/filters.c src/forward.c src/integer.c src/ionogram.c src/myfiles.c src/mytime.c src/s_old_file.c src/v_old_file.c src/c_old_file.c src/kd_old_file.c src/s_new_file.c src/seans3.c src/seans3c3.c src/h_file.c src/iv_file.c src/rd_file.c
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
