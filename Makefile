NAME  = pipex
B_NAME  = pipex_bonus

LIB_DIR = libft

FLAGS = -Wall -Wextra -Werror

M_HEADER = mandatory/pipex.h
B_HEADER = bonus/pipex_bonus.h

M_SRC =	mandatory/check_file.c mandatory/close_fd.c mandatory/execution.c mandatory/get_sec_path.c \
		mandatory/parce_cmd.c mandatory/pipex.c

B_SRC = bonus/pipex_bonus.c bonus/parce_cmd_bonus.c  bonus/check_file_bonus.c \
		bonus/execution_bonus.c bonus/close_fd_bonus.c bonus/execution_heredoc_bonus.c \
		bonus/get_sec_path_bonus.c  bonus/apply_heredoc_bonus.c bonus/ft_strcmp_bonus.c
 

M_OBJECT = $(M_SRC:.c=.o)
B_OJBECT = $(B_SRC:.c=.o)

bonus/%.o: bonus/%.c $(B_HEADER)
	cc $(FLAGS) -Ilibft -c $< -o $@

%.o: %.c $(M_HEADER) 
	cc $(FLAGS) -Ilibft -c $< -o $@


all: $(LIB_DIR) $(NAME) 

bonus: $(LIB_DIR) $(B_NAME)

$(LIB_DIR):
	make -C $(LIB_DIR)

$(B_NAME): $(B_OJBECT) $(LIB_DIR)/libft.a
	cc $(FLAGS) $(B_OJBECT) -o $@ -Llibft -lft

$(NAME): $(M_OBJECT) $(LIB_DIR)/libft.a
	cc $(FLAGS) $(M_OBJECT) -o $@ -Llibft -lft

clean:
	make -C $(LIB_DIR) clean
	rm -rf $(M_OBJECT) $(B_OJBECT)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -rf $(NAME) $(B_NAME)

re: fclean all

.PHONY: clean $(LIB_DIR)