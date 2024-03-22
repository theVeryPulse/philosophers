NAME := philo_bonus
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -g
FILES := main_bonus.c \

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
