# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 18:05:12 by gmarquis          #+#    #+#              #
#    Updated: 2024/10/25 10:27:12 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c $\
src/test_file.c

SRC_ROUTINE = src/routine/epis.c $\
src/routine/even.c $\
src/routine/uneven.c $\
src/routine/utils_epis.c $\
src/routine/utils_routine.c

SRC_U = src/act.c $\
src/out.c $\
src/threading.c $\
src/utils.c

SRC_VI = src/verif_and_init/args_verif.c $\
src/verif_and_init/init_epis.c $\
src/verif_and_init/init_philos.c $\
src/verif_and_init/init_utils.c $\
src/verif_and_init/init.c

INCLUDES = -Iincludes

NAME = philo

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -MMD -MP -fPIC
PHFLAGS = -pthread
VALGRIND = valgrind --tool=helgrind
ARGS = 4 210 100 100 5
RM = rm -rf

OBJ_DIR = obj/
OBJ = $(SRC:.c=.o)
OBJ_PREF = $(addprefix $(OBJ_DIR), $(OBJ))
DEPENDENCIES = $(patsubst %.o,%.d,$(OBJ_PREF))

OBJ_ROUTINE_DIR = obj/src/routine/
OBJ_ROUTINE = $(SRC_ROUTINE:.c=.o)
OBJ_ROUTINE_PREF = $(addprefix $(OBJ_ROUTINE_DIR), $(notdir $(OBJ_ROUTINE)))
DEPENDENCIES_ROUTINE = $(patsubst %.o,%.d,$(OBJ_ROUTINE_PREF))

OBJ_U_DIR = obj/src/
OBJ_U = $(SRC_U:.c=.o)
OBJ_U_PREF = $(addprefix $(OBJ_U_DIR), $(notdir $(OBJ_U)))
DEPENDENCIES_U = $(patsubst %.o,%.d,$(OBJ_U_PREF))

OBJ_VI_DIR = obj/src/verif_and_init/
OBJ_VI = $(SRC_VI:.c=.o)
OBJ_VI_PREF = $(addprefix $(OBJ_VI_DIR), $(notdir $(OBJ_VI)))
DEPENDENCIES_VI = $(patsubst %.o,%.d,$(OBJ_VI_PREF))

all : $(NAME)

bonus : $(NAME)

v: $(NAME)
	clear
	-$(VALGRIND) ./$(word 1, $^) $(ARGS) 2> valgrind

$(OBJ_DIR)%.o : src/%.c 
	$(MK) -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(PHFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_ROUTINE_DIR)%.o : src/routine/%.c
	$(MK) -p $(OBJ_ROUTINE_DIR)
	$(CC) $(CFLAGS) $(PHFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_U_DIR)%.o : src/%.c 
	$(MK) -p $(OBJ_U_DIR)
	$(CC) $(CFLAGS) $(PHFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_VI_DIR)%.o : src/verif_and_init/%.c 
	$(MK) -p $(OBJ_VI_DIR)
	$(CC) $(CFLAGS) $(PHFLAGS) $(INCLUDES) -c $< -o $@

$(NAME) : $(OBJ_PREF) $(OBJ_ROUTINE_PREF) $(OBJ_U_PREF) $(OBJ_VI_PREF)
	$(CC) $(CFLAGS) $^ -o $@ $(PHFLAGS)

clean :
	$(RM) obj/

fclean : clean
	$(RM) $(NAME)

re : fclean
	make all

.PHONY : all bonus clean fclean re

-include $(DEPENDENCIES)
-include $(DEPENDENCIES_ROUTINE)
-include $(DEPENDENCIES_U)
-include $(DEPENDENCIES_VI)
