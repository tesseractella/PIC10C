.PHONY: all clean

COMPILER = g++
CFLAGS = -std=c++20 -O3
TARGET = HW6P2
SRC = HW6P2.cpp
OBJ = HW6P2.o

all = $(TARGET)

$(TARGET): $(OBJ)
	$(COMPILER) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) errorOutput.tex
