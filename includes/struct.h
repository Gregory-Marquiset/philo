/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:41:17 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/24 21:26:05 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_state
{
	GET_READY,
	READY,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}			t_state;

typedef struct s_epís
{
	int				n_philos;		//	Number of philosophers and fork from 1 to n
	size_t			time_to_die;	//	(in milliseconds) time max beatween each philosophermeal
	size_t			time_to_eat;	//	(in milliseconds) time needed by a philosopher for eating a meal
	size_t			time_to_sleep;	//	(in milliseconds) time spend sleeping
	int				n_meal;			//	n meal for each philo, when reached program stop, if ndef infinit loop until 1 philo die
	int				start_time;
	pthread_t		thread_ep;
	pthread_mutex_t	mprintf;		//	pour mute printf
	int				*id_dead;		//	l'id du philo mort
	int				*philos_states;	//	indique l'etat des philos en fonction de la struct enum
	int				*philos_meals;	//	indique l'etat des repas des philos
	int				end_sympos;		//	0 si il faut terminer le symposium
}				t_epís;

typedef struct s_philo
{
	int				id;				//	Un id unique par philosophe, utilisé pour les distinguer l'rs de l'affichage ou la gestion des ressources
	pthread_t		thread_ph;		//	Le thread associé à chaque philosophe, permettant de gérer leur exécution simultanée
	pthread_mutex_t	lf_fork;		//	Pointeurs vers les mutexes représentant les baguettes à gauche et à droite du philosophe
	pthread_mutex_t	*rg_fork;		//	Ils sont utilisés pour synchroniser l'accès aux baguettes
	time_t			last_meal;		//	Le moment où le philosophe a mangé pour la dernière fois, utilisé pour vérifier s'il a faim ou implémenter des règles supplémentaires (comme la gestion de la famine)
	int				count_meal;		//	Nombre de repas pris, utilisé pour limiter le nombre de fois qu'un philosophe mange ou pour collecter des statistiques
	int				*philo_state;	//	Pointeur vair un tableau de l'epis qui contient l'etat du philos
	int				*philo_meal;	//	Pointeur vair un tableau de l'epis qui contient l'etat des repas
	t_epís			*epís;
}				t_philo;

typedef struct s_sympos
{
	t_epís	*epís;
	t_philo	*philos;
}				t_sympos;

#endif