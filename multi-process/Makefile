NAME := philo_bonus
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -O3
FILES := main_bonus.c \
	ft_atoi.c \
	ft_isdigit.c \
	input_bonus.c \
	philo_actions.c \
	philo_process.c \
	safe_operations.c \
	time_bonus.c \
	utils.c \
	wait_philo_death.c

INC_DIR := inc
SRC_DIR := src
OBJ_DIR := build

SRC_FILES := $(addprefix $(SRC_DIR)/, $(FILES))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@ $(CFLAGS) -I$(INC_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $^ -o $@ $(CFLAGS) -I$(INC_DIR)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all, clean, fclean, re
