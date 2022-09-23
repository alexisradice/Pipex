NAME = pipex
NAME_BONUS = pipex_bonus

SRCS_FILES = 	pipex.c \
				parsing.c \
				childs.c \

SRCS_FILES_BONUS = 	pipex_bonus.c \
					parsing_bonus.c \
					childs_bonus.c \
					childs_bonus.c \

SRCS_PATH = src/
SRCS_PATH_BONUS = bonus/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))
SRCS_BONUS = $(addprefix $(SRCS_PATH_BONUS), $(SRCS_FILES_BONUS))

CC = gcc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g

INCL = -I./includes -I./libft/includes
LIBFT_PATH = libft/
LIBFT = libft/libft.a

OBJS= $(SRCS:%.c=%.o)
OBJS_BONUS= $(SRCS_BONUS:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCL) -o $@ -c $<

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

$(LIBFT):
	$(MAKE) -C libft all

clean:
	$(RM) $(OBJS)

clean_bonus:
	$(RM) $(OBJS_BONUS)

fclean:	clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

fclean_bonus:	clean_bonus
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(RM) $(NAME_BONUS)
	
re:	fclean all

re_bonus:	fclean_bonus bonus

.PHONY:	all bonus clean clean_bonus fclean fclean_bonus re re_bonus