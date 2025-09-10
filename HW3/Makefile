.PHONY: all clean

COMPILER = g++
CFLAGS = -std=c++17 -O3
TARGET = HW3
SRC = binary_search_tree.cpp HW3.cpp
OBJ = binary_search_tree.o HW3.o

all = $(TARGET)

$(TARGET): $(OBJ)
	$(COMPILER) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) errorOutput.tex
