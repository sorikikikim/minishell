CC = gcc
HEADER = libft.h
CFAGS = -Wall -Wextra -Werror
OPTION = -I $(HEADER)
NAME = libft.a
SRC = ft_isalnum.c ft_isdigit.c ft_itoa.c ft_memcpy.c ft_putchar_fd.c ft_putendl_fd.c \
	  ft_putstr_fd.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_substr.c \
	  ft_strlcpy.c
OBJECTS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	ar rc $@ $(OBJECTS)

%.o	: %.c	$(HEADER)
	$(CC) $(CFAGS) -o $@ -c $< -I $(HEADER)

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all
