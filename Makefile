# Directories
SRC_DIR = src
UTIL_DIR = $(SRC_DIR)/Utils
BASE_DIR = $(SRC_DIR)/Base
GUI_DIR = $(SRC_DIR)/Interface
OBJ_DIR = ObjectFiles

.default: all

all: mineSweeper

clean:
	rm -f mineSweeper $(OBJ_DIR)/*.o
	rm -f mineSweeper mineSweeper

# Create Executable
mineSweeper: 	$(OBJ_DIR)/GenerateMineField.o \
				$(OBJ_DIR)/mineSweeper.o \
				$(OBJ_DIR)/GameFunctions.o \
				$(OBJ_DIR)/GameGUI.o

	g++ -Wall -Werror -std=c++17 -g -O -o mineSweeper $^ -lsfml-graphics -lsfml-window -lsfml-system

# Utils Rule: For files in the Utils folder
$(OBJ_DIR)/%.o: $(UTIL_DIR)/%.cpp | $(OBJ_DIR)
	g++ -Wall -Werror -std=c++17 -g -O -c $< -o $@

# Basic Rule: Files in the Base folder
$(OBJ_DIR)/%.o : $(BASE_DIR)/%.cpp | $(OBJ_DIR)
	g++ -Wall -Werror -std=c++17 -g -O -c $< -o $@

# Interface Rule: Files in the Base folder
$(OBJ_DIR)/%.o : $(GUI_DIR)/%.cpp | $(OBJ_DIR)
	g++ -Wall -Werror -std=c++17 -g -O -c $< -o $@

# Src Rule: Files in the main directory
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	g++ -Wall -Werror -std=c++17 -g -O -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)