NAME = libftprintf.a
AR = ar
ARFLAGS = -rcs
CC = gcc
CFLAGS = -Wall -Werror -Wextra
CFLAGS += #-g -fsanitize=address
INC = -I src -I lib/inc
LIB = -L lib -lft
SRC_DIR = src
OBJ_DIR = obj

SRC = \
	conversions/char\
	conversions/float\
	conversions/int\
	conversions/str_ptr_mod\
	conversions/uint\
	conversions/utils\
	ft_printf\
	parse

OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ) lib/libft.a
	@ar -x lib/libft.a && mv *.o $(OBJ_DIR)
	@$(AR) $(ARFLAGS) $@ $(OBJ) $(OBJ_DIR)/*.o
	@ranlib $(NAME)
	@rm "__.SYMDEF SORTED"

lib/libft.a:
	@make -C lib
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< 

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C lib/

fclean: clean
	@rm -f $(NAME)
	@make fclean -C lib/

re: fclean all
