NAME = libftprintf.a
AR = ar
ARFLAGS = -rcs
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I src -I lib
LIB = -L lib -lft
SRC_DIR = src
OBJ_DIR = obj

SRC = \
	conversions/char\
	conversions/string\
	conversions/pointer\
	conversions/int\
	conversions/uint\
	parse\
	ft_printf\
	main\

OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)
	@./libftprintf.a

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIB) -o $(NAME)
#	@$(AR) $(ARFLAGS) $@ $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< 

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
