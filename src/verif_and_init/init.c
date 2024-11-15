/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:41:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/25 09:34:21 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	ph_init_epis(t_sympos *sympos)
{
	t_epis *epis;
	sympos->epis = ph_init_malloc(sympos, 1, sizeof(t_epis));
	epis = sympos->epis;
	epis->thread_ep = 0;

	ph_init_mtx(sympos, &epis->mtx_verif);
	epis->verif = ph_init_malloc(sympos, 1, sizeof(int));
	ph_modif_var(&epis->mtx_verif, epis->verif, 0);
	ph_init_mtx(sympos, &epis->mtx_printf);
	ph_init_mtx(sympos, &epis->mtx_id_dead);
	epis->id_dead = ph_init_malloc_mutex(sympos,
		&epis->mtx_id_dead, 1, sizeof(int));
	ph_modif_var(&epis->mtx_id_dead, epis->id_dead, 0);
	ph_init_mtx(sympos, &epis->mtx_phs_meals);
	epis->phs_meals = ph_init_malloc_mutex(sympos,
		&epis->mtx_phs_meals, 1, sizeof(int));
	ph_modif_var(&epis->mtx_phs_meals, epis->phs_meals, 0);
}

t_sympos	*ph_init_sympos(t_agalma *tmp)
{
	t_sympos	*sympos;

	sympos = NULL;
	sympos = ph_init_malloc(sympos, 1, sizeof(t_sympos));
	ph_init_epis(sympos);
	ph_init_philos(sympos, tmp);
	return (sympos);
}
