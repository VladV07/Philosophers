/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_do_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:02:40 by vlad              #+#    #+#             */
/*   Updated: 2022/06/27 20:19:21 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	protected_get_time(void *arg)
{
	t_main	*dt;

	dt = (t_main *)arg;
	pthread_mutex_lock(&dt->data->mutex_main);
	dt->philo->t_start = get_time();
	pthread_mutex_unlock(&dt->data->mutex_main);
}

void	mutex_forks(void *arg)
{
	t_main	*dt;

	dt = (t_main *)arg;
	if (dt->philo->nb_ph != dt->data->nb_of_ph)
	{
		pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->lf]);
		philo_print(dt, "do_philo: Phil has taken a l fork.");
		pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->rf]);
		philo_print(dt, "do_philo: Phil has taken a r fork.");
	}
	else
	{
		pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->rf]);
		philo_print(dt, "do_philo: Phil has taken a r fork.");
		pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->lf]);
		philo_print(dt, "do_philo: Phil has taken a l fork.");
	}
}

void	ft_eat(t_main *dt)
{
	philo_print(dt, "do_philo: Phil eat.");
	usleep(dt->data->time_to_eat * 1000);
}

void	ft_sleep(t_main *dt)
{
	philo_print(dt, "do_philo: Phil sleep.");
	usleep(dt->data->time_to_sleep * 1000);
}

void	*do_philo(void *arg)
{
	t_main		*dt;

	dt = (t_main *)arg;
	dt->philo->step = 0;
	dt->philo->end_eat = 0;
	if (dt->philo->nb_ph % 2 == 0)
		usleep(2000);
	while (dt->data->stop == 0)
	{
		protected_get_time(arg);
		mutex_forks(arg);
		ft_eat(dt);
		pthread_mutex_unlock(&dt->data->mutex_forks[dt->philo->rf]);
		pthread_mutex_unlock(&dt->data->mutex_forks[dt->philo->lf]);
		protected_get_time(arg);
		ft_sleep(dt);
		philo_print(dt, "do_philo: Philo thinking.");
		pthread_mutex_lock(&dt->data->mutex_main);
		dt->philo->step++;
		pthread_mutex_unlock(&dt->data->mutex_main);
		pthread_mutex_lock(&dt->data->mutex_main);
		if (dt->data->stop == 0)
			printf("%lld %d %s %lld\n", get_time() - dt->data->t_start_main, \
						dt->philo->nb_ph, "do_philo: step= ", dt->philo->step);
		pthread_mutex_unlock(&dt->data->mutex_main);
	}
	return (NULL);
}
