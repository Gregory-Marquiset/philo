# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 18:05:12 by gmarquis          #+#    #+#              #
#    Updated: 2024/10/25 11:07:47 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/act.c \
      src/main.c \
      src/out.c \
      src/test_file.c \
      src/threading.c \
      src/utils.c

SRC_ROUTINE = src/routine/epis.c
              #src/routine/uneven.c \
              #src/routine/utils_routine.c

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
VALGRIND = valgrind --tool=helgrind
ARGS = 20 220 100 100 5
RM = rm -rf

OBJ_DIR = obj/
OBJ = $(SRC:.c=.o)
OBJ_ROUTINE = $(SRC_ROUTINE:.c=.o)
OBJ_VI = $(SRC_VI:.c=.o)

OBJ_PREF = $(addprefix $(OBJ_DIR), $(OBJ))
OBJ_ROUTINE_PREF = $(addprefix $(OBJ_DIR), $(OBJ_ROUTINE))
OBJ_VI_PREF = $(addprefix $(OBJ_DIR), $(OBJ_VI))

DEPENDENCIES = $(OBJ_PREF:.o=.d) $(OBJ_ROUTINE_PREF:.o=.d) $(OBJ_VI_PREF:.o=.d)

all : $(NAME)

v: $(NAME)
	clear
	-$(VALGRIND) ./$(NAME) $(ARGS) 2> valgrind

$(OBJ_DIR)%.o : %.c
	@$(MK) -p $(dir $@)
	$(CC) $(CFLAGS) $(PHFLAGS) $(INCLUDES) -c $< -o $@

$(NAME) : $(OBJ_PREF) $(OBJ_ROUTINE_PREF) $(OBJ_VI_PREF)
	$(CC) $(CFLAGS) $^ -o $@ $(PHFLAGS)

clean :
	$(RM) obj/

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re v

-include $(DEPENDENCIES)

