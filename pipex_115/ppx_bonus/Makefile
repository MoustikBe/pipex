NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -c
RM			= rm -rf
SOURCES		= src_bonus/ppx_main src_bonus/ppx_split src_bonus/ppx_check src_bonus/ppx_path \
			  src_bonus/ppx_basic src_bonus/ppx_fd src_bonus/ppx_process

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