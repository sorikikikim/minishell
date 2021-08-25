CC 				= gcc
RM				= rm -rf
CFLAGS 			= -Wall -Wextra -Werror
NAME 			= minishell

READLINE_LIB	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include

LIBFT		= libft.a
LIBFT_DIR	= libft

SRC_DIR 	= srcs
SRC 		= $(SRC_DIR)/minishell.c $(SRC_DIR)/utils.c $(SRC_DIR)/utils2.c $(SRC_DIR)/parse.c $(SRC_DIR)/exec.c \
	  	  	  $(SRC_DIR)/error_management.c $(SRC_DIR)/ft_cd.c $(SRC_DIR)/ft_exit.c \
			  $(SRC_DIR)/ft_env.c $(SRC_DIR)/ft_pwd.c $(SRC_DIR)/ft_export.c $(SRC_DIR)/export_utils.c \
			  $(SRC_DIR)/signal_handle.c $(SRC_DIR)/alloc_token.c $(SRC_DIR)/ft_copy_str.c $(SRC_DIR)/cmd_split.c $(SRC_DIR)/ft_word_len.c \
			  $(SRC_DIR)/ft_split_cnt.c $(SRC_DIR)/ft_split_cnt2.c\
			  $(SRC_DIR)/get_parse_size.c $(SRC_DIR)/get_parse_size2.c $(SRC_DIR)/redir_chk.c $(SRC_DIR)/ft_getenv.c \
			  $(SRC_DIR)/redirect.c $(SRC_DIR)/redirect_check.c \
			  $(SRC_DIR)/ft_echo.c $(SRC_DIR)/unset.c $(SRC_DIR)/non_builtin.c $(SRC_DIR)/non_builtin_exec.c \
			  $(SRC_DIR)/error_write.c $(SRC_DIR)/save_filename.c

OBJ_DIR 	= objs
OBJ 		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : 		$(NAME)

$(NAME) : 	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $@ $(OBJ) $(READLINE_LIB) $(READLINE_INC) \
			$(LIBFT)

$(LIBFT) :
			make -C $(LIBFT_DIR)
			cp $(LIBFT_DIR)/$(LIBFT) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $@ \
			$(READLINE_INC) 

clean :
			make clean -C $(LIBFT_DIR)
			$(RM) $(OBJ_DIR)

fclean : 	clean
			cd $(LIBFT_DIR); make fclean
			$(RM) $(NAME) $(LIBFT)

re : 		fclean all

.PHONY :	all clean fclean
