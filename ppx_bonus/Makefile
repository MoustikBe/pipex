NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -c
RM			= rm -rf
SOURCES		= src_bonus/ppx_main src_bonus/ppx_split src_bonus/ppx_check src_bonus/ppx_join src_bonus/ppx_path

OBJECTS     = $(SOURCES:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

all : $(NAME)

re: fclean all

.PHONY: all clean fclean re