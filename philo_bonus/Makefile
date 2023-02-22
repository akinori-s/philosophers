# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/05 19:45:54 by asasada           #+#    #+#              #
#    Updated: 2022/11/05 19:45:54 by asasada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	:= ./
SRCS	:=	main_bonus.c \
			inputs_bonus.c \
			utils_bonus.c \
			philo_bonus.c \
			init_vars.c

SRCS	:= $(addprefix $(SRCS_DIR), $(SRCS))
OBJS	:= $(SRCS:.c=.o)

HEADERS :=	./philo_bonus.h
NAME	:=	./philo_bonus

INCLDIR			:= -I ./

CC		:= cc
RM		:= rm -f
CFLAGS	:= -Wall -Wextra -Werror

all:		$(NAME)

$(OBJS):	$(SRCS_DIR)%.o : $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) $(INCLDIR) -c $< -o $@

$(NAME):	$(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

clean:
	$(RM) $(OBJS) $(B_OBJS)

fclean:	clean
	$(RM) $(NAME) $(B_NAME)

re:		fclean all

bonus:	all

do:		all clean

norm:
	norminette ./*.c ./*.h

address:	$(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread -fsanitize=address

.PHONY:	all clean fclean re bonus do norm
