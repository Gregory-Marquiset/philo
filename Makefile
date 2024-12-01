# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 18:05:12 by gmarquis          #+#    #+#              #
#    Updated: 2024/11/27 09:25:15 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/act.c \
      src/main.c \
      src/out.c \
      src/test_file.c \
      src/threading.c \
      src/utils.c

SRC_ROUTINE = src/routine/epis.c \
	  src/routine/philos.c \
	  src/routine/utils_routine.c

SRC_VI = src/verif_and_init/args_verif.c \
         src/verif_and_init/init_philos.c \
         src/verif_and_init/init_utils.c \
         src/verif_and_init/init.c

INCLUDES = -Iincludes

NAME = philo

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -MMD -MP -fPIC
PHFLAGS = -pthread
VALGRIND = valgrind --tool=helgrind --history-level=full
ARGS = 200 130 60 60
RM = rm -rf

OBJ_DIR = obj/
DEP_DIR = dep/
OBJ = $(SRC:.c=.o)
OBJ_ROUTINE = $(SRC_ROUTINE:.c=.o)
OBJ_VI = $(SRC_VI:.c=.o)

OBJ_PREF = $(addprefix $(OBJ_DIR), $(OBJ))
OBJ_ROUTINE_PREF = $(addprefix $(OBJ_DIR), $(OBJ_ROUTINE))
OBJ_VI_PREF = $(addprefix $(OBJ_DIR), $(OBJ_VI))

DEPENDENCIES = $(patsubst $(OBJ_DIR)%.o,$(DEP_DIR)%.d,$(OBJ_PREF) $(OBJ_ROUTINE_PREF) $(OBJ_VI_PREF))

all : $(NAME)

v: $(NAME)
	clear
	-$(VALGRIND) ./$(NAME) $(ARGS) 2> valgrind

$(OBJ_DIR)%.o : %.c
	@$(MK) -p $(dir $@) $(DEP_DIR)$(dir $<)
	$(CC) $(CFLAGS) $(PHFLAGS) $(INCLUDES) -c $< -o $@ -MMD -MF $(DEP_DIR)$*.d

$(NAME) : $(OBJ_PREF) $(OBJ_ROUTINE_PREF) $(OBJ_VI_PREF)
	$(CC) $(CFLAGS) $^ -o $@ $(PHFLAGS)

clean :
	$(RM) $(OBJ_DIR) $(DEP_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re v

-include $(DEPENDENCIES)

