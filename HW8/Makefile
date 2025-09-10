.PHONY: all clean

COMPILER = g++
CFLAGS = -std=c++20 -O3
TARGET = HW8
SRC = HW8.cpp
OBJ = HW8.o

all = $(TARGET)

$(TARGET): $(OBJ)
	$(COMPILER) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) errorOutput.tex

