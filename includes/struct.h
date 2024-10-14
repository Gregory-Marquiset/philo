/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:41:17 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/14 22:39:46 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

		//		episkopos		//

typedef struct s_printf
{
	pthread_mutex_t	mtx_verif;
	int				*verif;
	pthread_mutex_t	mtx_printf;			//	mute printf
}				t_printf;

typedef struct s_e_kinesis
{
	int				*id_dead;		//	l'id du philo mort
	int				*phs_meals;		//	indique l'etat des repas des philos
	int				*phs_states;	//	indique si les philo son assis a la table
}				t_e_kinesis;

typedef struct s_e_mtx
{
	pthread_mutex_t	mtx_id_dead;		//	mute id_dead
	pthread_mutex_t	mtx_phs_meals;		//	mute phs_meals
	pthread_mutex_t	mtx_phs_states;		//	mute phs_states
}				t_e_mtx;

typedef struct s_e_agalma
{
	int				n_philos;		//	Number of philosophers and fork from 1 to n
	unsigned long	tt_die;			//	(in milliseconds) time max beatween each philosophermeal
	unsigned long	tt_eat;			//	(in milliseconds) time needed by a philosopher for eating a meal
	unsigned long	tt_sleep;		//	(in milliseconds) time spend sleeping
	int				n_meal;			//	n meal for each philo, when reached program stop, if ndef infinit loop until 1 philo die
	unsigned long	st_time;
}				t_e_agalma;

typedef struct s_epis
{
	t_e_agalma		*agal;			//	varible immuable
	t_e_mtx			*mtx;			//	mutex
	t_e_kinesis		*kine;			//	variable modifiable
	t_printf		*use_printf;
	pthread_t		thread_ep;
}				t_epis;

		//		philo		//

typedef struct s_p_kinesis
{
	unsigned long	*last_meal;		//	Le moment où le philosophe a mangé pour la dernière fois, utilisé pour vérifier s'il a faim ou implémenter des règles supplémentaires (comme la gestion de la famine)
	int				*count_meal;	//	Nombre de repas pris, utilisé pour limiter le nombre de fois qu'un philosophe mange ou pour collecter des statistiques
	int				*phs_meals;		//	Pointeur de int que les philos incremente l'orsqu'il ont manger tout leurs repas
	pthread_mutex_t	*mtx_phs_meals;
	int				*phs_states;	//	Pointeur de int que les philos incremente l'orsqu'ils ont join la table
	pthread_mutex_t	*mtx_phs_states;
	int				*id_dead;
	pthread_mutex_t	*mtx_id_dead;
}				t_p_kinesis;

typedef struct s_philo
{
	int				id;				//	Un id unique par philosophe, utilisé pour les distinguer l'rs de l'affichage ou la gestion des ressources
	pthread_t		thread_ph;		//	Le thread associé à chaque philosophe, permettant de gérer leur exécution simultanée
	pthread_mutex_t	*lf_fork;		//	Pointeurs vers les mutexes représentant les baguettes à gauche et à droite du philosophe
	pthread_mutex_t	rg_fork;		//	Ils sont utilisés pour synchroniser l'accès aux baguettes
	t_p_kinesis		*kine;			//	variable modifiable
	t_epis			*epis;			//	acces direct a l'episkopos
}				t_philo;

		//		symposium		//

typedef struct s_sympos
{
	t_epis	*epis;
	t_philo	*philos;
}				t_sympos;

#endif
