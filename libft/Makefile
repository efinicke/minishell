# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 13:02:00 by spayeur           #+#    #+#              #
#    Updated: 2022/02/07 13:30:29 by spayeur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	ft_isalpha.c ft_isdigit.c ft_isspace.c \
			ft_itoa.c ft_ullitoa.c ft_atoi.c \
			ft_strlcpy.c ft_strjoin.c ft_strdup.c \
			ft_strlen.c ft_strncmp.c ft_strnstr.c \
			ft_split.c
			
OBJS		=	${SRCS:.c=.o}

NAME		=	libft.a
 
CC		=	@cc
RM		=	@rm -f

CFLAGS		=	-Wall -Wextra -Werror

all:		${NAME}

${OBJS}:	libft.h

$(NAME):	${OBJS}
		@ar rc ${NAME} ${OBJS}

clean:
		${RM} ${OBJS} ${B_OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re
