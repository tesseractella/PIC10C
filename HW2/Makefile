.PHONY: all clean

COMPILER = g++
CFLAGS = -std=c++17 -O3
TARGET = HW2
SRC = hashtable.cpp HW2.cpp
OBJ = hashtable.o HW2.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(COMPILER) $(CFLAGS) -c $@ $^

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) errorOutput.tex
