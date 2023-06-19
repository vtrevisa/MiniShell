#--STANDARD--
NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror -g3 -lreadline
VPATH	= $(addprefix $(SRC_D)/, $(DIRS))
HEADER	= ./Include/minishell.h

#--LIBFT--
LIB		= $(addprefix $(LPATH)/, libft.a)
LPATH	= ./Libft/

#--DIRS--
SRC_D	= ./src/
DIRS	= . builtins exec parser_lexer system 
OBJ_D	= ./objects

#--FILES--
SRC		= $(BTIN) $(EXEC) $(PRLX) $(SYST) 

BTIN	= echo.c change_dir.c pwd.c env.c export.c unset.c builtin_checker.c exit.c
EXEC	= child_and_pipes.c child.c path_search.c pipe_input.c
PRLX	= lexer.c lexer_utils.c lexer_utils_2.c args_str_treatment.c parser.c parse_redir.c \
			parse_redir_utils.c
SYST	= main.c read_line.c init.c  exec.c error_exit.c utils.c here-doc.c signals.c 

#--OBJECTS--
OBJ		= $(SRC:%.c=$(OBJ_D)/%.o)

#--COLORS--
WHITE	=	\e[00m
GREEN	=	\e[32m
RED		=	\e[91m
YELLOW	=	\e[033m
BLUE	=	\e[34m

NUMBER_OF_SRC_FILES	=	$(words $(SRC))
PROGRESS			=	0

all: $(NAME)

$(NAME): $(LIB) $(OBJ) $(OBJ_D)
	@echo "$(BLUE)Compiling $(WHITE)Minishell"
	@cc $(OBJ) $(LIB) $(CFLAGS) -o $@
	@echo "$(GREEN)Compiled $(WHITE)Minishell"

$(LIB):
	@echo "$(BLUE)Compiling $(WHITE)Libft"
	@$(MAKE)	-C $(LPATH) --no-print-directory

$(OBJ_D)/%.o: %.c Makefile | $(OBJ_D)
	@cc -c $< -o $@
	@echo -n "$(YELLOW)Compiling $(WHITE)$$(( $(PROGRESS) * 100 / $(NUMBER_OF_SRC_FILES)))%\r"
	$(eval PROGRESS=$(shell echo $$(($(PROGRESS)+1))))

$(OBJ_D):
	@mkdir -p $@

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' --suppressions=readline.supp ./minishell

clean:
	@echo "$(BLUE)Removing $(WHITE)Minishell objects"
	@rm -rf $(OBJ_D)
	@$(MAKE)	clean -C $(LPATH) --no-print-directory

fclean: clean
	@echo "$(BLUE)Removing $(WHITE)$(NAME)"
	@rm -rf $(NAME)
	@$(MAKE)	fclean -C $(LPATH) --no-print-directory

re: fclean all
