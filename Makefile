# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 18:05:12 by gmarquis          #+#    #+#              #
#    Updated: 2024/12/04 08:39:21 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = src/mandatory/act.c \
      src/mandatory/main.c \
      src/mandatory/out.c \
      src/mandatory/test_file.c \
      src/mandatory/threading.c \
      src/mandatory/utils.c

SRCM_ROUTINE = src/mandatory/routine/epis.c \
	  src/mandatory/routine/philos.c \
	  src/mandatory/routine/sleep_think.c \
	  src/mandatory/routine/eat.c

SRCM_VI = src/mandatory/verif_and_init/args_verif.c \
         src/mandatory/verif_and_init/init_philos.c \
         src/mandatory/verif_and_init/init_utils.c \
         src/mandatory/verif_and_init/init.c

INCLUDES = -Iincludes

NAME = philo

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -MMD -MP -fPIC
#-fsanitize=thread (ralenti beaucoup le programme et creer des erreur, a ne pas combiner avec valgrind)
PHFLAGS = -pthread
#valgrind --tool=helgrind --history-level=full
ARGS = 199 210 60 60 25
RM = rm -rf

OBJM_DIR = obj/
DEPM_DIR = dep/
OBJM = $(SRCM:.c=.o)
OBJM_ROUTINE = $(SRCM_ROUTINE:.c=.o)
OBJM_VI = $(SRCM_VI:.c=.o)

OBJM_PREF = $(addprefix $(OBJM_DIR), $(OBJM))
OBJM_ROUTINE_PREF = $(addprefix $(OBJM_DIR), $(OBJM_ROUTINE))
OBJM_VI_PREF = $(addprefix $(OBJM_DIR), $(OBJM_VI))

DEPENDENCIESM = $(patsubst $(OBJM_DIR)%.o,$(DEPM_DIR)%.d,$(OBJM_PREF) $(OBJM_ROUTINE_PREF) $(OBJM_VI_PREF))

all : $(NAME)

$(OBJM_DIR)%.o : %.c
	@$(MK) -p $(dir $@) $(DEPM_DIR)$(dir $<)
	$(CC) $(CFLAGS) $(PHFLAGS) $(INCLUDES) -c $< -o $@ -MMD -MF $(DEPM_DIR)$*.d

$(NAME) : $(OBJM_PREF) $(OBJM_ROUTINE_PREF) $(OBJM_VI_PREF)
	$(CC) $(CFLAGS) $^ -o $@ $(PHFLAGS)

clean :
	$(RM) $(OBJM_DIR) $(DEPM_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re v

-include $(DEPENDENCIESM)

