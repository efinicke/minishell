# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/13 16:30:59 by spayeur           #+#    #+#              #
#    Updated: 2022/02/07 14:16:09 by spayeur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 Informations                                 #
# **************************************************************************** #

MINISHELL	=	minishell

CC		=	@cc
CFLAGS		=	-Wall -Wextra -Werror
LIBFT		=	./libft
LIBFT_FLAGS	=	-lft -L ./libft
INCLUDE		=	./includes/minishell.h
INCLUDE_LIBFT	=	./libft/libft.a
SRC_DIR		=	./srcs

# **************************************************************************** #
#                                    C0l0r$                                    #
# **************************************************************************** #

# Regular Colors
BLACK			:= $(shell tput -Txterm setaf 0)
RED			:= $(shell tput -Txterm setaf 1)
GREEN			:= $(shell tput -Txterm setaf 2)
YELLOW			:= $(shell tput -Txterm setaf 3)
BLUE			:= $(shell tput -Txterm setaf 4)
MAGENTA			:= $(shell tput -Txterm setaf 5)
CYAN			:= $(shell tput -Txterm setaf 6)
WHITE			:= $(shell tput -Txterm setaf 7)

# Bold
BOLD			:= $(shell tput -Txterm bold)
BBLACK			= ${BOLD}${BLACK}
BRED			= ${BOLD}${RED}
BGREEN			= ${BOLD}${GREEN}
BYELLOW			= ${BOLD}${YELLOW}
BBLUE			= ${BOLD}${BLUE}
BMAGENTA		= ${BOLD}${MAGENTA}
BCYAN			= ${BOLD}${CYAN}
BWHITE			= ${BOLD}${WHITE}
END			:= $(shell tput -Txterm sgr0)

# Clear
CLEAR			:= $(shell tput -Txterm clear)
CLEAR_LINE		:= $(shell tput -Txterm el)

# **************************************************************************** #
#                                 Source files                                 #
# **************************************************************************** #

# ********************************** Shell *********************************** #

SRC_FILES_SHELL		=	minishell.c \
				pwd_var.c shlvl_var.c \
				envp_alloc.c envp_utils.c \
				signals.c

SRCS_SHELL		=	$(addprefix $(SRC_DIR)/shell/, $(SRC_FILES_SHELL))

# ********************************* Parsing ********************************** #

SRC_FILES_PARSING	=	00_call_and_return_cmd_lst.c \
				01_is_valid_quotes.c \
				02_fix_spaces.c \
				03_is_valid_syntax.c \
				04_is_valid_syntax2.c \
				05_replace_tilde.c \
				06_replace_env_var.c \
				07_replace_env_var2.c \
				08_remove_quotes.c \
				09_fill_cmds_in_struct.c \
				10_fill_lst.c \
				11_fill_file_and_type.c \
				12_fill_file_and_type2.c \
				13_fill_argv_and_argc.c \
				14_fill_argv_and_argc2.c \
				15_free_all.c \
				16_utils_str.c \
				17_utils_str2.c \
				18_utils_int_tab.c \
				19_utils_str_tab.c \
				20_utils_struct.c \
				21_utils_linked_list.c \
				22_utils_stderr.c

SRCS_PARSING		=	$(addprefix $(SRC_DIR)/parsing/, $(SRC_FILES_PARSING))

# ********************************* Builtins ********************************* #

SRC_FILES_ECHO		=	echo.c
SRC_FILES_CD		=	cd.c cd_without_argument.c cd_with_argument.c \
				cd_cdpath.c cd_slash_or_pwd.c cd_canonical_form.c \
				cd_canonical_form_steps.c cd_change_directory.c \
				cd_error.c
SRC_FILES_PWD		=	pwd.c pwd_accessors.c
SRC_FILES_EXPORT	=	export.c export_without_argument.c \
				export_with_argument.c export_with_argument_add.c \
				export_with_argument_replace.c
SRC_FILES_UNSET		=	unset.c unset_remove.c
SRC_FILES_ENV		=	env.c
SRC_FILES_EXIT		=	exit.c exit_code_validity.c

SRCS_ECHO		=	$(addprefix echo/, $(SRC_FILES_ECHO))
SRCS_CD			=	$(addprefix cd/, $(SRC_FILES_CD))
SRCS_PWD		=	$(addprefix pwd/, $(SRC_FILES_PWD))
SRCS_EXPORT		=	$(addprefix export/, $(SRC_FILES_EXPORT))
SRCS_UNSET		=	$(addprefix unset/, $(SRC_FILES_UNSET))
SRCS_ENV		=	$(addprefix env/, $(SRC_FILES_ENV))
SRCS_EXIT		=	$(addprefix exit/, $(SRC_FILES_EXIT))

SRCS_BUILTINS		=	$(addprefix $(SRC_DIR)/builtins/, $(SRCS_ECHO) $(SRCS_CD) \
				$(SRCS_PWD) $(SRCS_EXPORT) $(SRCS_UNSET) $(SRCS_ENV) $(SRCS_EXIT))

# **************************** Command_executions **************************** #

SRC_FILES_CMD_EXEC	=	execution.c basic_execution.c export_underscore.c \
				cmd_path.c cmd_utils.c cmd_error.c \
				here_doc.c open_io_files.c \
				builtins.c \
				free.c 

SRCS_CMD_EXEC		=	$(addprefix $(SRC_DIR)/command_execution/, $(SRC_FILES_CMD_EXEC))

# ********************************* Project ********************************** #

SRCS_PROJECT		=	$(SRCS_SHELL) $(SRCS_PARSING) $(SRCS_BUILTINS) $(SRCS_CMD_EXEC)

# **************************************************************************** #
#                                 Object files                                 #
# **************************************************************************** #

OBJS_PROJECT		=	$(SRCS_PROJECT:.c=.o)

# **************************************************************************** #
#                                    Rules                                     #
# **************************************************************************** #

%.o: %.c
			@printf "${BMAGENTA}%-35.35s\r${END}" $@
			$(CC) $(CFLAGS) -c $< -o $@

all:			$(MINISHELL)

start_msg:
			@echo "${BBLUE}Start compile ...${END}"

$(MINISHELL):		start_msg $(OBJS_PROJECT)
			@make -C $(LIBFT) >/dev/null
			$(CC) $(CFLAGS) -I $(INCLUDE) $(LIBFT_FLAGS) -o $(MINISHELL) \
			$(OBJS_PROJECT) $(INCLUDE_LIBFT) -lreadline
			@echo -n "$(CLEAR_LINE)"
			@echo "${BCYAN}$(MINISHELL) ${BGREEN}has been build ! ${END}"

clean:
			@make clean -C $(LIBFT) >/dev/null
			@echo "${BBLUE}Cleaning...${END}"
			@echo -n "${CYAN}"
			@echo -n `rm -vf $(OBJS_PROJECT) | wc -l`
			@echo " object file(s) ${BGREEN}has/have been removed.${END}"

fclean:			clean
			@make fclean -C $(LIBFT) >/dev/null
			-@rm $(MINISHELL) 2>/dev/null && \
			echo "${CYAN}$(MINISHELL)${END} ${BGREEN}has been removed.${END}" || true

re:			fclean all

.PHONY:			all clean fclean re
