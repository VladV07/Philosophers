/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:48:08 by vlad              #+#    #+#             */
/*   Updated: 2022/07/01 19:37:41 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

t_main	*check_stop(t_main *dt, int i)
{
	i = 0;
	dt->data->count_eat = 0;
	while (i < dt->data->nb_of_ph)
	{
		dt->data->time_die = get_time() - (dt->philo + i)->t_start;
		if (dt->data->time_to_die < (get_time() - (dt->philo + i)->t_start))
		{
			dt->data->time_die = get_time() - (dt->philo + i)->t_start;
			dt->data->nb_ph_die = i + 1;
			dt->data->stop = 1;
			break ;
		}
		if ((dt->philo + i)->step >= dt->data->steps_to_end && \
									dt->data->steps_to_end != 0)
			(dt->philo + i)->end_eat = 1;
		dt->data->count_eat = dt->data->count_eat + (dt->philo + i)->end_eat;
		if (dt->data->count_eat == dt->data->nb_of_ph)
		{
			dt->data->stop = 2;
			break ;
		}
		i++;
	}
	return (dt);
}

void	*monitor_death(void *arg)
{
	t_main		*dt;
	int			i;

	dt = (t_main *)arg;
	while (1)
	{
		usleep(333);
		pthread_mutex_lock(&dt->data->mutex_main);
		i = 0;
		dt->data->count_eat = 0;
		dt = check_stop(dt, i);
		if (dt->data->stop != 0)
		{
			if (dt->data->stop == 1)
				printf("%lld %d %s\n", get_time() - dt->data->t_start_main, \
					dt->philo->nb_ph, "died");
			pthread_mutex_unlock(&dt->data->mutex_main);
			return (NULL);
		}
		pthread_mutex_unlock(&dt->data->mutex_main);
	}
	return (NULL);
}
