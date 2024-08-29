/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:00:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/30 01:46:53 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	ft_atoi_safe(char *str)
{
	long (result) = 0;
	int (i) = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			ft_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			ft_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX)
		ft_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
	else if (result < 1)
		ft_quit_philo(NULL, 2, LERR_ARGS_H0, CERR_ARGS_H0);
	return ((int)result);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < (n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	ft_program_run_helper(int flag)
{
	if(flag == 1)
		ft_quit_philo(NULL, 2, LERR_ARGS_H2, CERR_ARGS_H1);
	else if(flag == 2)
		ft_quit_philo(NULL, 2, LERR_ARGS_H3, CERR_ARGS_H1);
}

t_sympos	*ft_args_verif_and_make_sympos(int argc, char ** argv)
{
	t_epís	tmp;

	if (argc == 2)
	{
		if (!ft_strncmp(argv[1], "--help", 7))
			ft_program_run_helper(1);
		else if (!ft_strncmp(argv[1], "--help++", 9))
			ft_program_run_helper(2);
	}
	if (argc < 5 || argc > 6)
		ft_quit_philo(NULL, 2, LERR_ARGS_H1, CERR_ARGS_H1);
	tmp.n_philos = ft_atoi_safe(argv[1]);
	tmp.time_to_die = (size_t)ft_atoi_safe(argv[2]);
	tmp.time_to_eat = (size_t)ft_atoi_safe(argv[3]);
	tmp.time_to_sleep = (size_t)ft_atoi_safe(argv[4]);
	if (argv[5])
		tmp.n_meal = ft_atoi_safe(argv[5]);
	else
		tmp.n_meal = 0;
	return(ft_init_sympos(&tmp));
}
