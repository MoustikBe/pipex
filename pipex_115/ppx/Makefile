NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -c
RM			= rm -rf
SOURCES		= src/ppx_main src/ppx_split src/ppx_check  src/ppx_path

OBJECTS     = $(SOURCES:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)
	@echo "\033[33;32mCompilation finish with no problem ✅"

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)
	@echo "\033[33;36mAll the file his delete correctly ✅"

all : $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
