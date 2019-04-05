NAME = libftprintf.a
AR = ar
ARFLAGS = -rcs
CC = gcc
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -g -fsanitize=address
INC = -I src -I lib/inc
LIB = -L lib -lft
SRC_DIR = src
OBJ_DIR = obj

SRC = \
	conversions/char\
	conversions/int\
	conversions/mod\
	conversions/pointer\
	conversions/string\
	conversions/uint\
	conversions/utils\
	ft_printf\
	main\
	parse

OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)
#	@./libftprintf.a

$(NAME): $(OBJ)
#	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIB) -o $(NAME)
	@$(AR) $(ARFLAGS) $@ $(OBJ) lib/obj/*.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< 

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
