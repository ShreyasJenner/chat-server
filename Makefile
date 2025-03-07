CXX=g++
CXXFLAGS=-Wall -Wextra -Iinclude
FLAGS=

SRC=src
OBJ=obj
BIN=bin

SERVER=$(BIN)/server
CLIENT=$(BIN)/client

SRCS=$(shell find $(SRC) -name '*.cpp')
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))


# build target
build: $(SERVER) $(CLIENT)

$(SERVER): $(OBJS)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(FLAGS)


$(CLIENT): $(OBJS)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(FLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BIN)

.PHONY: build clean
