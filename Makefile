#--STANDARD--
NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror -g3 -lreadline
OBJ_D	= ./objects
HEADER	= ./Include/minishell.h

#--MANDATORY--
SRC_D	= ./src/
SRC		= main.c read_line.c init.c lexer.c lexer_utils.c lexer_utils_2.c exec.c child_and_pipes.c echo.c change_dir.c pwd.c env.c export.c unset.c error_exit.c utils.c pipe_input.c args_str_treatment.c path_search.c child.c builtin_checker.c parser.c parse_redir.c parse_redir_utils.c here-doc.c
OBJ		= $(addprefix $(OBJ_D)/, $(SRC:.c=.o))

#--LIBFT--
LIB		= $(addprefix $(LPATH)/, libft.a)
LPATH	= ./Libft/

all: $(NAME)

$(NAME): $(LIB) $(OBJ) $(HEADER)
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
