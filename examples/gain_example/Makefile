EXECUTABLE = gain_example

# path(s) to include files
CFLAGS  = -std=c++11 -Wall -I.

# libraries to link
LDFLAGS = -ljack -llo -lyaml-cpp

SRC_DIR = src
OBJ_DIR = obj

# all sources and dependencies
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	mkdir $@

clean:
	$(RM) -r $(OBJ_DIR) $(EXECUTABLE)

-include $(DEP)
