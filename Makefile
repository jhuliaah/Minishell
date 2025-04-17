
# NAME		=	tokenizer

# LIBFT		=	Libft42/libft.a

# ARQUIVOS	=	main.c utils.c verifications.c sorting.c 
				
# OBJETOS		=	$(ARQUIVOS:%.c=%.o)

# CFLAGS		=	-Wall -Werror -Wextra

# %.o: %.c
# 	cc -c $< -o $@

# all: $(NAME)

# $(NAME): $(OBJETOS) $(LIBFT)
# 	cc $^ -o $@

# $(LIBFT):
# 	make -C Libft42

# clean:
# 	rm -f $(OBJETOS)

# fclean: clean
# 	make fclean -C Libft42
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re

# Makefile

NAME = tokenizer_tests

SRC_DIR = src
TEST_DIR = tests

SRCS = $(SRC_DIR)/tokenizer.c $(SRC_DIR)/tokenizer_utils.c
TESTS = $(TEST_DIR)/tokenizer_test.c
LIBFT = Libft42/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(SRCS) $(TESTS) $(LIBFT)
	$(CC) $(CFLAGS) -I $(SRC_DIR) -I $(TEST_DIR) -I ./Libft42 $(SRCS) $(TESTS) $(LIBFT) -o $(NAME)

 $(LIBFT):
	make -C Libft42

clean:
	rm -f $(NAME)

fclean: clean
	make fclean -C Libft42
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

