
NAME = pipex

SRC_PATH = srcs/
BON_PATH = srcs_bonus/
LIBFT_PATH = libft/
LIBFT_AR = $(LIBFT_PATH)libft.a

SRC = error_h.c main.c parsing.c split_cmd.c
SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
DPD = $(SRC:.c=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCS = includes/pipex.h
INC = -Iincludes -I$(LIBFT_PATH)/includes

PURPLE = \033[0;35m
NC = \033[0m

all: $(LIBFT_AR) $(NAME)

$(NAME): $(OBJ) $(INCS)
	@echo "\n$(PURPLE)  Compiling Pipex...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_AR) $(INC) -o $(NAME)
	@echo "\n$(PURPLE)  Ready ✓$(NC)\n"

-include $(DPD)

%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT_AR):
	@echo "\n$(PURPLE)  Compiling LIBFT...$(NC)"
	@make -s -C $(LIBFT_PATH)
	@echo "\n$(PURPLE)  Done ✓$(NC)"

clean:
	@echo "\n$(PURPLE)  Cleaning object files... $(NC)"
	@rm -rf $(OBJ) $(OBJ_BON)
	@rm -rf $(DPD) $(OBJ_DPD)
	@make -s clean -C $(LIBFT_PATH)
	@echo "\n$(PURPLE)  Done ✓$(NC)"

fclean: clean
	@echo "\n$(PURPLE)  Cleaning Pipex...$(NC)"
	@$(RM) $(NAME)
	@$(RM) $(NAME_BON)
	@make -s fclean -C $(LIBFT_PATH)
	@echo "\n$(PURPLE)  Done ✓$(NC)"

re: fclean all

.PHONY: all clean fclean re
