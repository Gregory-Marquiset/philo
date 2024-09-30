# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 18:05:12 by gmarquis          #+#    #+#              #
#    Updated: 2024/09/30 22:34:53 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c $\
test_file.c $\

SRC_U = src/act_utils.c $\
src/act.c $\
src/args_verif.c $\
src/epis_utils.c $\
src/init_epis.c $\
src/init_philos.c $\
src/init_utils.c $\
src/init.c $\
src/out.c $\
src/philo_utils.c $\
src/threading_utils.c $\
src/threading.c $\
src/utils.c

NAME = philo

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -MMD -MP -fPIC
PHFLAGS = -pthread
VALGRIND = valgrind --tool=helgrind --history-level=full 
ARGS = 4 450 200 200 
RM = rm -rf

OBJ_DIR = obj/
OBJ = $(notdir $(SRC:>C=.o))
OBJ_PREF = $(addprefix $(OBJ_DIR), $(OBJ:.c=.o))
DEPENDENCIES = $(patsubst %.o,%.d,$(OBJ_PREF))

OBJ_U_DIR = obj/src/
OBJ_U = $(notdir $(SRC_U:>C=.o))
OBJ_U_PREF = $(addprefix $(OBJ_U_DIR), $(OBJ_U:.c=.o))
DEPENDENCIES_U = $(patsubst %.o,%.d,$(OBJ_U_PREF))

all : $(NAME)

bonus : $(NAME)

v: $(NAME)
	clear
	-$(VALGRIND) ./$(word 1, $^) $(ARGS) 2> valgrind

$(OBJ_DIR)%.o : %.c 
	$(MK) -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(PHFLAGS) -c $< -o $@

$(OBJ_U_DIR)%.o : src/%.c 
	$(MK) -p $(OBJ_U_DIR)
	$(CC) $(CFLAGS) $(PHFLAGS) -c $< -o $@

$(NAME) : $(OBJ_PREF) $(OBJ_U_PREF)
	$(CC) $(CFLAGS) $^ -o $@ $(PHFLAGS)

clean :
	$(RM) obj/

fclean : clean
	$(RM) $(NAME)

re : fclean
	make all

.PHONY : all bonus clean fclean re

-include $(DEPENDENCIES)
-include $(DEPENDENCIES_U)
