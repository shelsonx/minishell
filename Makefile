NAME			= minishell
LIBFT			= libft.a

CC 				= cc
CF 				= -g -Wall -Wextra -Werror
CFI 			= -I $(INCLUDE)
CREADLINE		= -lreadline

LIBFT_PATH 		= ./libs/libft/
SRC_PATH 		= ./sources/
OBJ_PATH		= ./obj/
INCLUDE 		= ./includes/

SRC				= main.c\
				  prompt.c\
				  parser.c parser_utils.c\
				  exec.c pipes.c paths.c command.c children_process.c \
				  ht_utils.c ht_functions.c free_ht.c linkedlist_utils.c \
				  here_doc.c exec_builtins.c\
				  utils_pipes.c\
				  signals.c\
				  exit_program.c exit_program_utils.c\
				  exit_utils.c \
				  get_token.c lexical_analyzer.c lexical_resources.c lexical_utils.c \
				  env.c pwd.c echo.c exit.c cd.c export.c export_utils.c unset.c \
				  export_utils_2.c fds_utils.c export_utils_3.c \
				  expander.c quotes.c quotes_utils.c\
				  builtins.c linked_list_env_utils.c \
				  fd_in.c fd_out.c linked_list_funcs.c overflow_buckets.c \
				  redirects_utils.c builtins_utils.c exec_utils.c exec_utils_2.c exit_status.c\
				  simple_command.c redirection.c sort_queue.c 

VPATH 			:= $(SRC_PATH)\
				$(SRC_PATH)prompt\
				$(SRC_PATH)execute\
				$(SRC_PATH)utils\
				$(SRC_PATH)exit_program\
				$(SRC_PATH)lexer\
				$(SRC_PATH)parser\
				$(SRC_PATH)builtins\
				$(SRC_PATH)expander\
				$(SRC_PATH)redirects\

OBJ				= $(addprefix $(OBJ_PATH), $(notdir $(SRC:.c=.o)))

RM 				= rm -rf

$(OBJ_PATH)%.o: %.c
				mkdir -p $(OBJ_PATH)
				$(CC) $(CF) $(CFI) -c $< -o $@

$(NAME):		$(OBJ)
				make -C $(LIBFT_PATH) $(LIBFT)
				$(CC) -g $(CF) -I $(INCLUDE) -o $(NAME) $(OBJ) -L $(LIBFT_PATH) -lft $(CREADLINE)
				@echo "$(GREEN)$(NAME) created$(DEFAULT)"

all:			$(NAME)

re:				fclean all

clean:
				make -C $(LIBFT_PATH) clean
				$(RM) $(OBJ) $(OBJDIR)
				$(RM) $(OBJ_PATH)
				@echo "$(YELLOW)object files deleted$(DEFAULT)"

fclean:			clean
				make -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)
				@echo "$(RED)all deleted$(DEFAULT)"

install:		
				sudo apt-get install -y libreadline-dev valgrind

leak:							
				valgrind --suppressions=readline.supp --leak-check=full --trace-children-skip='*/bin/*,*/sbin/*' \
					--track-origins=yes --show-leak-kinds=all ./$(NAME)

.PHONY:			all clean fclean re bonus rebonus

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m