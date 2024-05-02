NAME		= so_long
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Imlx -Ilibft -c
RM			= rm -rf
MLXFLAGS	= -Lmlx -lmlx -framework OpenGL -framework AppKit

SOURCES		= sl_main \
			  algorythme/sl_algo \
			  checker/sl_main_check checker/sl_check_1 checker/sl_check_2 \
			  function_lib/sl_split function_lib/sl_strjoin function_lib/sl_utils \
			  get_next_line/get_next_line get_next_line/get_next_line_utils \
			  graph_mng/sl_grph_main graph_mng/sl_grph_input graph_mng/sl_grph_print graph_mng/sl_grph_utils \
			  utils/sl_copy_map	utils/sl_free utils/sl_put_info	  

OBJECTS     = $(SOURCES:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): cc src/

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

all : $(NAME)

re: fclean all

.PHONY: all clean fclean re