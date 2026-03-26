CXX = g++
CXXFLAGS = -O0 -s
TARGET = exp
SRC = expenditure.cpp main.cpp manager.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^