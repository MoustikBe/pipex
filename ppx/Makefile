NAME		= so_long
CC			= cc
RM			= rm -rf

SOURCES		= ppx_main ppx_split

OBJECTS     = $(SOURCES:%.c=%.o)

%.o: %.c
	$(CC) $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

all : $(NAME)

re: fclean all

.PHONY: all clean fclean re