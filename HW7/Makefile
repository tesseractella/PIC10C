.PHONY: all clean

COMPILER = g++
CFLAGS = -std=c++20 -O3
TARGET = HW7
SRC = HW7.cpp
OBJ = HW7.o

all = $(TARGET)

$(TARGET): $(OBJ)
	$(COMPILER) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) errorOutput.tex
