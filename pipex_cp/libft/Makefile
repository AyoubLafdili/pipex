NAME = libft.a

HEADER = libft.h

SRC_DIR = src

FUN = $(SRC_DIR)/ft_atoi.c $(SRC_DIR)/ft_lstclear.c \
	$(SRC_DIR)/ft_memchr.c $(SRC_DIR)/ft_memset.c \
	$(SRC_DIR)/ft_strlcpy.c $(SRC_DIR)/ft_strrchr.c \
	$(SRC_DIR)/ft_memcmp.c $(SRC_DIR)/ft_strchr.c \
	$(SRC_DIR)/ft_strlen.c $(SRC_DIR)/ft_tolower.c \
	$(SRC_DIR)/ft_split.c $(SRC_DIR)/ft_strmapi.c  \
	$(SRC_DIR)/ft_calloc.c $(SRC_DIR)/ft_isdigit.c \
	$(SRC_DIR)/ft_memcpy.c $(SRC_DIR)/ft_strdup.c \
	$(SRC_DIR)/ft_strncmp.c $(SRC_DIR)/ft_toupper.c \
	$(SRC_DIR)/ft_isprint.c $(SRC_DIR)/ft_memmove.c \
	$(SRC_DIR)/ft_strlcat.c $(SRC_DIR)/ft_strnstr.c \
	$(SRC_DIR)/ft_substr.c $(SRC_DIR)/ft_strjoin.c \
	$(SRC_DIR)/ft_putchar.c $(SRC_DIR)/ft_putstr.c \
	$(SRC_DIR)/ft_putnbr.c $(SRC_DIR)/ft_putunbr.c \
	$(SRC_DIR)/ft_lstsize.c $(SRC_DIR)/ft_lstlast.c \
	$(SRC_DIR)/ft_lstiter.c $(SRC_DIR)/ft_lstmap.c \
	$(SRC_DIR)/ft_putstr_fd.c $(SRC_DIR)/ft_printf.c \
	$(SRC_DIR)/ft_strtrim.c $(SRC_DIR)/ft_putchar_fd.c \
	$(SRC_DIR)/ft_lstadd_back.c $(SRC_DIR)/ft_isalpha.c \
	$(SRC_DIR)/ft_putendl_fd.c $(SRC_DIR)/ft_isascii.c \
	$(SRC_DIR)/ft_striteri.c $(SRC_DIR)/ft_putnbr_fd.c \
	$(SRC_DIR)/ft_puthexa.c  $(SRC_DIR)/ft_putaddress.c \
	$(SRC_DIR)/ft_lstnew.c $(SRC_DIR)/ft_lstadd_front.c \
	$(SRC_DIR)/get_next_line.c $(SRC_DIR)/ft_isalnum.c \
	$(SRC_DIR)/ft_bzero.c $(SRC_DIR)/ft_itoa.c \
	$(SRC_DIR)/ft_lstdelone.c

REMOVE = rm -rf
COMPILER = cc
SOBJECT = $(FUN:.c=.o)

FLAGS = -Wall -Wextra -Werror

%.o: %.c $(HEADER)
	$(COMPILER) -I. $(FLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(SOBJECT)
	ar -rc $(NAME) $(SOBJECT) 

clean:
	$(REMOVE) $(SOBJECT)

fclean: clean
	$(REMOVE) $(NAME)

re:  fclean all
