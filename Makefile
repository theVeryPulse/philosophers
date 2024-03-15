NAME := philo
CC := cc
CFLAGS := -Wall -Wextra -Werror -lpthread
FILES := main.c\
	check_input.c \
	forks_philos.c \
	free_and_exit.c \
	ft_atoi.c \
	ft_isdigit.c \
	ft_isspace.c \
	routine_part1.c \
	routine_part2.c \
	time.c
INC_DIR := inc
SRC_DIR := src
OBJ_DIR := build

SRC_FILES := $(addprefix $(SRC_DIR)/, $(FILES))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@ 

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $^ -o $@ $(CFLAGS)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all, clean, fclean, re
