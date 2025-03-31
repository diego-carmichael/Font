# 99% of this Makefile is copied from somewhere but I forget at this point

CC = g++

CFLAGS = -std=c++11
CFLAGS += -Iinclude

.PHONY: clean run compile all dirs

SRC  = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp) $(wildcard src/**/**/*.cpp) $(wildcard src/**/**/**/*.cpp) $(wildcard src/**/**/**/**/*.cpp)
OBJ  = $(SRC:.cpp=.o)
BIN = bin

APPNAME = Font

ifeq ($(OS),Windows_NT)

LDFLAGS = -lgdi32 -luser32 -ld2d1 -lcomdlg32 -ldwrite
ifeq ($(CC),gcc)
LDFLAGS += -lm
endif

endif

all: dirs compile

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

# All of this code probably doesn't work on all Windows systems, very hacky

ifeq ($(OS),Windows_NT)
dirs:
	if not exist "bin" mkdir $(BIN)
else
dirs:
	mkdir -p $(BIN)
endif

ifeq ($(OS),Windows_NT)
compile: $(OBJ)
	$(CC) -o $(BIN)/$(APPNAME).exe $^ $(LDFLAGS)
else
compile: $(OBJ)
	$(CC) -o $(BIN)/$(APPNAME) $^ $(LDFLAGS)
endif

ifeq ($(OS),Windows_NT)
# Jesus christ
clean:
	del /F /Q $(BIN)
	del /F /Q /S *.o
else
clean:
	rm -rf $(BIN) $(OBJ)
endif