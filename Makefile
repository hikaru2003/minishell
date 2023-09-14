# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 11:51:36 by snemoto           #+#    #+#              #
#    Updated: 2023/08/22 15:39:50 by snemoto          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# Variables																	   #
# **************************************************************************** #

NAME	= minishell
SRCS	= $(shell echo *.c)
OBJDIR	= obj/
OBJS	= $(SRCS:%.c=$(OBJDIR)%.o)

CC		= cc
CFLAGS	= -Wall -Wextra -Werror $(INCLUDE)
# CFLAGS	= -Wall -Wextra -Werror -fsanitize=address $(INCLUDE)
LIBS	= -lreadline

# **************************************************************************** #
# General Rules																   #
# **************************************************************************** #

all:	$(OBJDIR) $(NAME)

$(OBJDIR):
		mkdir -p obj

$(OBJDIR)%.o: %.c
		$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJS)

clean:
		rm -rf $(OBJDIR)

fclean:	clean
		rm -f $(NAME)

re:		fclean all

bonus:	all

.PHONY: all clean fclean re bonus

# **************************************************************************** #
# Platform Compatibility													   #
# **************************************************************************** #

OS := $(shell uname -s)

ifeq ($(OS),Linux)

endif

ifeq ($(OS),Darwin)
		RLDIR 	= $(shell brew --prefix readline)
		INCLUDE += -I$(RLDIR)/include
		LIBS	+= -L$(RLDIR)/lib
endif
