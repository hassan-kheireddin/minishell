CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

NAME = minishell
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INC_DIR = inc

SRC = main.c \
      signal/signal.c \
	  executer/builtins.c executer/cd.c executer/echo.c \
	  executer/exec.c executer/exit.c executer/export_handlers.c \
	  executer/export.c executer/get_cmd.c  \
	  executer/pwd.c executer/unset.c executer/env.c \
      parsing/ft_strtrim_all.c parsing/fill_node.c parsing/get_params.c\
      parsing/ft_cmdtrim.c parsing/expand_vars.c parsing/heredoc.c parsing/utils.c\
      parsing/ft_cmdsubsplit.c parsing/parse_args.c parsing/handle_redi.c parsing/expand_path.c\
      prompt/prompt_utils.c prompt/prompt.c \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "\033[0;92m$(NAME) is up to date!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re