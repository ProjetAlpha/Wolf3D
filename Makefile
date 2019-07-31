NAME = wolf3d

SRC_PATH =		./src
WIN_DIR =	/window/
REND_DIR =	/render/
EVENT_DIR =	/event/
PHYS_DIR = /physics/
PARSE_DIR = /parsing/
ERROR_DIR = /error/
UTIL_DIR = /utils/
SRC = $(SRC_PATH)$(WIN_DIR)window_manager.c\
			$(SRC_PATH)$(ERROR_DIR)display.c\
			$(SRC_PATH)$(UTIL_DIR)init_struct.c\
			$(SRC_PATH)$(PARSE_DIR)command.c\
			$(SRC_PATH)$(PARSE_DIR)set_map.c\
			$(SRC_PATH)main.c

BIN_PATH =		./bin
BIN = $(patsubst $(SRC_PATH)%.c,./bin/%.o,$(SRC))

INCLUDE_PATH = include
FW_PATH = ./frameworks
CC = gcc
CFLAGS += -Wall -Wextra -Werror -g -fsanitize=address -O2 -I./$(INCLUDE_PATH)\
														  -I./libft/includes/\
														  -I$(FW_PATH)/SDL2_image.framework/Headers/\
														  -I$(FW_PATH)/SDL2_ttf.framework/Headers/\
														  -I$(FW_PATH)/SDL2.framework/Headers/

LIBSDL2 = -framework SDL2 -F $(FW_PATH) -framework SDL2_image -framework SDL2_ttf -rpath $(FW_PATH)
LIBFT = libft
LIBRARIES = $(LIBSDL2) $(LIBFT)/$(LIBFT).a

all:	directory $(NAME)

$(NAME): $(BIN)
		make -C $(LIBFT)
		$(CC) $(CFLAGS) $(BIN) -o $(NAME) $(LIBRARIES)

$(BIN_PATH)/%.o : $(SRC_PATH)/%.c
		$(CC) $(CFLAGS) -c $< -o $@

$(BIN_PATH)/$(SRC_PATH_1)/%.o : $(SRC_PATH)/$(SRC_PATH_1)/%.c
		$(CC) $(CFLAGS) -c $< -o $@

directory:
		@mkdir $(BIN_PATH) 2> /dev/null || true
		@mkdir $(BIN_PATH)/$(WIN_DIR) 2> /dev/null || true
		@mkdir $(BIN_PATH)/$(REND_DIR) 2> /dev/null || true
		@mkdir $(BIN_PATH)/$(EVENT_DIR) 2> /dev/null || true
		@mkdir $(BIN_PATH)/$(PHYS_DIR) 2> /dev/null || true
		@mkdir $(BIN_PATH)/$(PARSE_DIR) 2> /dev/null || true
		@mkdir $(BIN_PATH)/$(ERROR_DIR) 2> /dev/null || true
		@mkdir $(BIN_PATH)/$(UTIL_DIR) 2> /dev/null || true

clean:
		rm -rf $(BIN_PATH)
		make clean -C $(LIBFT)

fclean:	clean
		rm -rf $(NAME)
		make fclean -C $(LIBFT)

re:		fclean all

norme:
		@norminette $(SRC_PATH)
		@norminette $(INCLUDE_PATH)
		@norminette $(LIBFT)

.PHONY: all, clean, fclean, re, directory, norme
