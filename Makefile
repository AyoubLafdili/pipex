NAME  = pipex
B_NAME  = pipex_bonus

ARCHIVE = libft/libft.a

FLAGS = -Wall 
M_HEADER = mandatory/pipex.h
B_HEDER = bonus/pipex.h

M_SRC =

B_SRC = bonus/pipex_bonus.c bonus/parce_cmd_bonus.c bonus/_free_mem_bonus.c bonus/check_file_bonus.c \
		bonus/execution_bonus.c bonus/close_fd.c
 

M_OBJECT = $(M_SRC:.c=.o)
B_OJBECT = $(B_SRC:.c=.o)

bonus/%.o: bonus/%.c $(B_HEADER)
	cc $(FLAGS) -Ilibft -c $< -o $@

%.o: %.c $(M_HEADER)
	cc $(FLAGS) -Ilibft -c $< -o $@


all: $(ARCHIVE) $(NAME) 

bonus: $(ARCHIVE) $(B_NAME)

$(ARCHIVE):
	make -C libft

$(NAME): $(M_OBJECT) $(ARCHIVE) 
	cc $(FLAGS) $(M_OBJECT) -o $@ -Llibft -lft

$(B_NAME): $(B_OJBECT)
	cc $(FLAGS) $(B_OJBECT) -o $@ -Llibft -lft

clean:
	make -C libft clean
	rm -rf $(M_OBJECT) $(B_OJBECT)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME) $(B_NAME)

re: fclean all

.PHONY: clean $(ARCHIVE)