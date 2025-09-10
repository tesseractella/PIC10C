.PHONY: all clean

COMPILER = g++
CFLAGS = -std=c++20 -O3
TARGET = HW5
SRC = HW5.cpp
OBJ = HW5.o

all = $(TARGET)

$(TARGET): $(OBJ)
	$(COMPILER) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) errorOutput.tex
