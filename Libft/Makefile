NAME	= libft.a

SRC	= ./Src/ft_atoi.c ./Src/ft_bzero.c ./Src/ft_calloc.c ./Src/ft_isalnum.c ./Src/ft_isalpha.c \
	./Src/ft_isascii.c ./Src/ft_isdigit.c ./Src/ft_isprint.c ./Src/ft_itoa.c ./Src/ft_memchr.c \
	./Src/ft_memcmp.c ./Src/ft_memcpy.c ./Src/ft_memmove.c ./Src/ft_memset.c ./Src/ft_split.c\
	./Src/ft_putchar_fd.c ./Src/ft_putendl_fd.c ./Src/ft_putnbr_fd.c ./Src/ft_putstr_fd.c \
	./Src/ft_strchr.c ./Src/ft_strdup.c ./Src/ft_striteri.c ./Src/ft_strjoin.c ./Src/ft_strlcat.c\
	./Src/ft_strlcpy.c ./Src/ft_strlen.c ./Src/ft_strmapi.c ./Src/ft_strncmp.c ./Src/ft_strnstr.c \
	./Src/ft_strrchr.c ./Src/ft_strtrim.c ./Src/ft_substr.c ./Src/ft_tolower.c ./Src/ft_toupper.c\
	./Src/ft_lstnew.c ./Src/ft_lstadd_front.c ./Src/ft_lstsize.c ./Src/ft_lstlast.c \
	./Src/ft_lstadd_back.c ./Src/ft_lstdelone.c ./Src/ft_lstclear.c ./Src/ft_lstiter.c ./Src/ft_lstmap.c\
	./Src/Ft_printf/ft_printf.c ./Src/Ft_printf/printpointer_fd.c ./Src/Ft_printf/utils.c \
	./Src/Ft_printf/handlechar.c ./Src/Ft_printf/handlestr.c ./Src/Ft_printf/handlepointer.c \
	./Src/Ft_printf/handleints.c ./Src/Ft_printf/handleunsigned.c ./Src/Ft_printf/handlehex.c \
	./Src/Get_next_line/get_next_line_utils.c ./Src/Get_next_line/get_next_line.c ./Src/Fractol/ft_atof.c
	
OBJS	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -I./Include/ -D BUFFER_SIZE=1

all:	$(NAME)

${NAME}: $(OBJS)
	@ar -rcs $(NAME) $(OBJS) 

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re
