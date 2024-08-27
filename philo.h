/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:16:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/27 17:42:56 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

	//		STRUCT			//

typedef enum s_state
{
	WAITING,
	THINK,
	EAT,
	SLEEP,
	DEAD,
}			t_state;

typedef struct s_philo
{
	int				id;					//	Un id unique par philosophe, utilisé pour les distinguer l'rs de l'affichage ou la gestion des ressources
	pthread_t		thread;				//	Le thread associé à chaque philosophe, permettant de gérer leur exécution simultanée
	pthread_mutex_t	left_chopstick;	//	Pointeurs vers les mutexes représentant les baguettes à gauche et à droite du philosophe
	pthread_mutex_t	*right_chopstick;	//	Ils sont utilisés pour synchroniser l'accès aux baguettes
	time_t			last_meal;			//	Le moment où le philosophe a mangé pour la dernière fois, utilisé pour vérifier s'il a faim ou implémenter des règles supplémentaires (comme la gestion de la famine)
	int				count_meal;			//	Nombre de repas pris, utilisé pour limiter le nombre de fois qu'un philosophe mange ou pour collecter des statistiques
	t_state			state;				//	Indique l'état actuel du philosophe (penser, manger, dormir), utile pour le débogage et affichages précis
}				t_philo;

typedef struct s_utils
{
	int		n_philos;		//	Number of philosophers and fork from 1 to n
	size_t	time_to_die;	//	(in milliseconds) time max beatween each philosophermeal
	size_t	time_to_eat;	//	(in milliseconds) time needed by a philosopher for eating a meal
	size_t	time_to_sleep;	//	(in milliseconds) time spend sleeping
	int		n_meal;			//	n meal for each philo, when reached program stop, if ndef infinit loop until 1 philo die
}				t_utils;

typedef struct s_college
{
	t_utils	*utils;
	t_philo	**philos;
}				t_college;


	//			files			//

		//	args_verif.c	//
void	ft_argsverif_and_makecollege(int argc, char **argv, t_college *college);

		//		init.c		//
void	ft_init_college(t_utils utils, t_college *college);

		//		out.c		//
void	ft_exit(int fd_out, char *message, int error_code);
void	ft_leave_table(t_college *college, int fd_out, char *message,
	int error_code);

		//	test_file.c		//
void	ft_print_college(t_college *college);

		//		time.c		//
void	ft_sleep(size_t inter);
void	ft_philo_thinking(int id, size_t time);
void	ft_philo_sleeping(int id, size_t time);
void	ft_philo_died(t_college *college, int id, size_t time);

#endif
