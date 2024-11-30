/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:00:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/30 08:48:00 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static int	ph_atoi_safe(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			ph_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			ph_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX)
		ph_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
	else if (result < 1)
		ph_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
	return ((int)result);
}

static int	ph_strncmp(const char *s1, const char *s2, unsigned long n)
{
	unsigned long	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < (n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	ph_program_run_helper(char *argv_1)
{
	if (!ph_strncmp(argv_1, "--help", 7))
		ph_quit_philo(NULL, 2, LERR_ARGS_H3, CERR_ARGS_H1);
}

t_sympos	*ph_args_verif_and_make_sympos(int argc, char **argv)
{
	t_agalma	tmp;

	if (argc == 2)
		ph_program_run_helper(argv[1]);
	if (argc < 5 || argc > 6)
		ph_quit_philo(NULL, 2, LERR_ARGS_H1, CERR_ARGS_H1);
	tmp.n_philos = ph_atoi_safe(argv[1]);
	tmp.tt_die = (unsigned long)ph_atoi_safe(argv[2]);
	tmp.tt_eat = (unsigned long)ph_atoi_safe(argv[3]);
	tmp.tt_sleep = (unsigned long)ph_atoi_safe(argv[4]);
	if (tmp.n_philos > 200 || tmp.tt_die < 60 || tmp.tt_eat < 60
		|| tmp.tt_sleep < 60)
		ph_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
	if (argv[5])
		tmp.n_meal = ph_atoi_safe(argv[5]);
	else
		tmp.n_meal = -1;
	tmp.tt_start = 0;
	tmp.tt_think = 0;
	return (ph_init_sympos(&tmp));
}
