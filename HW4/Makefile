.PHONY: all clean

COMPILER = g++
CFLAGS = -std=c++17 -O3
TARGET = HW4
SRC = red_black_tree.cpp HW4.cpp
OBJ = red_black_tree.o HW4.o

all = $(TARGET)

$(TARGET): $(OBJ)
	$(COMPILER) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) errorOutput.tex

