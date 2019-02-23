NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I src -I lib
LIB = -L lib -lft
SRC_DIR = src
OBJ_DIR = obj

SRC = \

OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIB) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< 

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
