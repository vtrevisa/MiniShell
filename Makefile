#--STANDARD--
NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror -g3 -lreadline
OBJ_D	= ./objects
HEADER	= ./Include/minishell.h

#--MANDATORY--
SRC_D	= ./src/
SRC		= display.c
OBJ		= $(addprefix $(OBJ_D)/, $(SRC:.c=.o))

#--LIBFT--
LIB		= $(addprefix $(LPATH)/, libft.a)
LPATH	= ./Libft/

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	cc $(OBJ) $(LIB) $(CFLAGS) -o $(NAME)

$(LIB): 
	$(MAKE)	-C $(LPATH)

$(OBJ_D)/%.o: $(SRC_D)/%.c
	mkdir -p $(OBJ_D)
	cc -c $< -o $@

clean:
	rm -rf $(OBJ_D)

fclean: clean
	rm -rf $(NAME)

re: fclean all