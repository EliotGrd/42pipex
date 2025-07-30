# Folders
LP = srcs/libft/
PP = srcs/printf/
GP = srcs/gnl/
INC = includes

# Source files
SRCS = \
	$(LP)ft_atof.c $(LP)ft_atoi.c $(LP)ft_bzero.c $(LP)ft_calloc.c $(LP)ft_isalnum.c $(LP)ft_isalpha.c \
	$(LP)ft_isascii.c $(LP)ft_isdigit.c $(LP)ft_iswspace.c $(LP)ft_isprint.c $(LP)ft_itoa.c $(LP)ft_memchr.c \
	$(LP)ft_memcmp.c $(LP)ft_memcpy.c $(LP)ft_memmove.c $(LP)ft_memset.c $(LP)ft_putchar_fd.c \
	$(LP)ft_putendl_fd.c $(LP)ft_putnbr_fd.c $(LP)ft_putstr_fd.c $(LP)ft_split.c $(LP)ft_strchr.c \
	$(LP)ft_strdup.c $(LP)ft_striteri.c $(LP)ft_strjoin.c $(LP)ft_strlcat.c $(LP)ft_strlcpy.c \
	$(LP)ft_strlen.c $(LP)ft_strmapi.c $(LP)ft_strncmp.c $(LP)ft_strnstr.c $(LP)ft_strrchr.c \
	$(LP)ft_strtrim.c $(LP)ft_substr.c $(LP)ft_tolower.c $(LP)ft_toupper.c $(LP)ft_strcmp.c\
	$(PP)ft_printf.c $(PP)ft_putnbr_base.c $(PP)ft_utils.c \
	$(GP)get_next_line_bonus.c $(GP)get_next_line_utils_bonus.c

BONUS = \
	$(LP)ft_lstadd_back_bonus.c $(LP)ft_lstmap_bonus.c $(LP)ft_lstadd_front_bonus.c \
	$(LP)ft_lstclear_bonus.c $(LP)ft_lstnew_bonus.c $(LP)ft_lstsize_bonus.c \
	$(LP)ft_lstdelone_bonus.c $(LP)ft_lstiter_bonus.c $(LP)ft_lstlast_bonus.c

# Objects
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Output
NAME = libft.a
RM = rm -f

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

bonus: $(OBJS) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

