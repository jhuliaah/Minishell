
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

# NAME = tokenizer_tests

# SRC_DIR = src
# TEST_DIR = tests

# SRCS = $(SRC_DIR)/tokenizer.c $(SRC_DIR)/tokenizer_utils.c
# TESTS = $(TEST_DIR)/tokenizer_test.c
# LIBFT = Libft42/libft.a

# CC = cc
# CFLAGS = -Wall -Wextra -Werror -g

# all: $(NAME)

# $(NAME): $(SRCS) $(TESTS) $(LIBFT)
# 	$(CC) $(CFLAGS) -I $(SRC_DIR) -I $(TEST_DIR) -I ./Libft42 $(SRCS) $(TESTS) $(LIBFT) -o $(NAME)

#  $(LIBFT):
# 	make -C Libft42

# clean:
# 	rm -f $(NAME)

# fclean: clean
# 	make fclean -C Libft42
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re

NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = Libft42

SRC = $(wildcard $(SRC_DIR)/*.c) \
      $(wildcard $(SRC_DIR)/builtins/*.c) \
      $(wildcard $(SRC_DIR)/env_variables/*.c) \
      $(wildcard $(SRC_DIR)/environment_yuri/*.c) \
      $(wildcard $(SRC_DIR)/error_mgmt/*.c) \
      $(wildcard $(SRC_DIR)/executor/*.c) \
      $(wildcard $(SRC_DIR)/memory_mgmt/*.c) \
      $(wildcard $(SRC_DIR)/parser/*.c) \
      $(wildcard $(SRC_DIR)/process_input/*.c) \
      $(wildcard $(SRC_DIR)/redirect/*.c) \
      $(wildcard $(SRC_DIR)/signals/*.c) \
      $(wildcard $(SRC_DIR)/tokenizer/*.c) \
      $(wildcard $(SRC_DIR)/utils/*.c) \
      $(wildcard $(SRC_DIR)/utils_yuri/*.c) \

OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g -I$(LIBFT_DIR)/includes -Isrc
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline -lncurses

# CFLAGS = -Wall -Wextra -Werror -g -Iincludes -I$(LIBFT_DIR)/includes -I/opt/homebrew/opt/readline/include -Isrc
# LDFLAGS = -L$(LIBFT_DIR) -lft -L/opt/homebrew/opt/readline/lib -lreadline -lncurses

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Minishell compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re