# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 18:05:12 by gmarquis          #+#    #+#              #
#    Updated: 2024/08/29 22:23:29 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c $\
test_file.c $\

SRCS_U = srcs/args_verif.c $\
srcs/init.c $\
srcs/mutex_ft.c $\
srcs/out.c $\
srcs/routine.c $\
srcs/time.c

NAME = philo

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
PHFLAGS = -pthread
RM = rm -rf

OBJS_DIR = objs/
OBJS = $(notdir $(SRCS:>C=.o))
OBJS_PREF = $(addprefix $(OBJS_DIR), $(OBJS:.c=.o))
DEPENDENCIES = $(patsubst %.o,%.d,$(OBJS_PREF))

OBJS_U_DIR = objs/srcs/
OBJS_U = $(notdir $(SRCS_U:>C=.o))
OBJS_U_PREF = $(addprefix $(OBJS_U_DIR), $(OBJS_U:.c=.o))
DEPENDENCIES_U = $(patsubst %.o,%.d,$(OBJS_U_PREF))

all : $(NAME)

bonus : $(NAME)

$(OBJS_DIR)%.o : %.c 
	$(MK) -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(PHFLAGS) -c $< -o $@

$(OBJS_U_DIR)%.o : srcs/%.c 
	$(MK) -p $(OBJS_U_DIR)
	$(CC) $(CFLAGS) $(PHFLAGS) -c $< -o $@

$(NAME) : $(OBJS_PREF) $(OBJS_U_PREF)
	$(CC) $(CFLAGS) $^ -o $@ $(PHFLAGS)

clean :
	$(RM) objs/

fclean : clean
	$(RM) $(NAME)

re : fclean
	make all

.PHONY : all bonus clean fclean re

-include $(DEPENDENCIES)
-include $(DEPENDENCIES_U)
