# Parts of this Makefile (especially the explanations) are based on this
# StackOverflow answer:
# https://stackoverflow.com/a/31610364

# Specify the name of the executable that will be compiled:
EXECUTABLE = karplus_strong_example

# Specify source code directory:
SRC_DIR = src
# Get a list of all the source files:
SRC = $(wildcard $(SRC_DIR)/*.cpp)

# Specify where to put the object (.o) files:
OBJ_DIR = obj
# Get a list of the object files that correspond to the source files:
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# From the object file list, get the dependency file list to handle automatic
# recompilation when a header file is modified:
DEP = $(OBJ:.o=.d)

# Required flags to enable the automatic dependency generation by the compiler:
CPPFLAGS = -MMD -MP

# C++ compiler flags:
CXXFLAGS  = -std=c++11 -L/usr/lib -Wall -I.

# Libraries to link (linker flags):
LDFLAGS = -ljack -llo -lyaml-cpp -lsndfile -lrtmidi

# Tell make that these target are not real files:
.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

# The build directory is custom so we need to tell make how to do it, also it
# must exist before trying to compile:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

# Create obj directory if it doesn't exist:
$(OBJ_DIR):
	mkdir $@

# On clean, remove obj directory and executable
clean:
	$(RM) -r $(OBJ_DIR) $(EXECUTABLE) *.o

-include $(DEP)
