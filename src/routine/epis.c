/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/25 09:45:20 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	*ph_routine_epis(void *tmp)
{
	t_epis	*epis;
	int		dead;
	int		meal;

	epis = (t_epis *)tmp;
	dead = 0;
	meal = 0;
	while (dead == 0 && meal == 0)
	{
		if (epis->agal->n_meal > 0)
		{
			meal = ph_with_target_meals(epis);
			if (meal == 1)
				ph_modif_var(&epis->mtx->mtx_id_dead, epis->kine->id_dead, -1);
			dead = ph_check_id_dead(epis);
		}
		else
			dead = ph_without_target_meals(epis);
	}
	if (dead != 0)
		ph_speaking_for_dead(epis, dead, LPRO_DIED);
	return (NULL);
}
