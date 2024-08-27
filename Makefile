# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 18:05:12 by gmarquis          #+#    #+#              #
#    Updated: 2024/08/26 22:55:31 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = args_verif.c $\
init.c $\
main.c $\
out.c $\
test_file.c $\
time.c $\

NAME = philo

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3
PHFLAGS = -pthread
RM = rm -rf

OBJS_DIR = objs/
OBJS = $(notdir $(SRCS:>C=.o))
OBJS_PREF = $(addprefix $(OBJS_DIR), $(OBJS:.c=.o))
DEPENDENCIES = $(patsubst %.o,%.d,$(OBJS_PREF))

all : $(NAME)

bonus : $(NAME)

$(OBJS_DIR)%.o : %.c 
	$(MK) -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(PHFLAGS) -c $< -o $@

$(NAME) : $(OBJS_PREF)
	$(CC) $(CFLAGS) $^ -o $@ $(PHFLAGS)

clean :
	$(RM) objs/

fclean : clean
	$(RM) $(NAME)

re : fclean
	make all

.PHONY : all bonus clean fclean re

-include $(DEPENDENCIES)
