NAME = pipex

SRCS_FILES = 	pipex.c \
				parsing.c \
				childs.c \

SRCS_PATH = src/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

CC = gcc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g

INCL = -I./includes -I./libft/includes
LIBFT_PATH = libft/
LIBFT = libft/libft.a

OBJS= $(SRCS:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCL) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

$(LIBFT):
	$(MAKE) -C libft all

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)
	
re:	fclean all

.PHONY:	all clean fclean re