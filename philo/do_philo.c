/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:02:40 by vlad              #+#    #+#             */
/*   Updated: 2022/07/01 19:35:18 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

t_main	*protected_get_time(void *arg)
{
	t_main	*dt;

	dt = (t_main *)arg;
	pthread_mutex_lock(&dt->data->mutex_main);
	dt->philo->t_start = get_time();
	pthread_mutex_unlock(&dt->data->mutex_main);
	return (dt);
}

void	mutex_forks(void *arg)
{
	t_main	*dt;

	dt = (t_main *)arg;
	pthread_mutex_lock(&dt->data->mutex_main);
	if (dt->philo->nb_ph != dt->data->nb_of_ph)
	{
		pthread_mutex_unlock(&dt->data->mutex_main);
		pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->lf]);
		philo_print(dt, "has taken a fork");
		pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->rf]);
		philo_print(dt, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&dt->data->mutex_main);
		pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->rf]);
		philo_print(dt, "has taken a fork");
		pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->lf]);
		philo_print(dt, "has taken a fork");
	}
}

int	ft_eat(t_main *dt)
{
	int	i;

	i = 0;
	philo_print(dt, "is eating");
	pthread_mutex_lock(&dt->data->mutex_main);
	dt->philo->step++;
	dt->philo->t_start_eat = get_time();
	while ((get_time() - dt->philo->t_start_eat) < dt->data->time_to_eat)
	{
		if (dt->data->stop != 0)
		{
			pthread_mutex_unlock(&dt->data->mutex_main);
			return (i);
		}
		pthread_mutex_unlock(&dt->data->mutex_main);
		i++;
		usleep(300);
		pthread_mutex_lock(&dt->data->mutex_main);
	}
	pthread_mutex_unlock(&dt->data->mutex_main);
	return (i);
}

int	ft_sleep(t_main *dt)
{
	int	i;

	i = 0;
	philo_print(dt, "is sleeping");
	pthread_mutex_lock(&dt->data->mutex_main);
	dt->philo->t_start_sleep = get_time();
	while ((get_time() - dt->philo->t_start_sleep) < dt->data->time_to_sleep)
	{
		if (dt->data->stop != 0)
		{
			pthread_mutex_unlock(&dt->data->mutex_main);
			return (i);
		}
		pthread_mutex_unlock(&dt->data->mutex_main);
		i++;
		usleep(300);
		pthread_mutex_lock(&dt->data->mutex_main);
	}
	pthread_mutex_unlock(&dt->data->mutex_main);
	return (i);
}

void	*do_philo(void *arg)
{
	t_main		*dt;

	dt = (t_main *)arg;
	dt->philo->step = 0;
	dt->philo->end_eat = 0;
	if (dt->philo->nb_ph % 2 == 0)
		usleep(1000);
	protected_get_time(arg);
	pthread_mutex_lock(&dt->data->mutex_main);
	while (dt->data->stop == 0)
	{
		pthread_mutex_unlock(&dt->data->mutex_main);
		mutex_forks(arg);
		ft_eat(dt);
		pthread_mutex_unlock(&dt->data->mutex_forks[dt->philo->rf]);
		pthread_mutex_unlock(&dt->data->mutex_forks[dt->philo->lf]);
		protected_get_time(arg);
		ft_sleep(dt);
		philo_print(dt, "is thinking");
		pthread_mutex_lock(&dt->data->mutex_main);
	}
	pthread_mutex_unlock(&dt->data->mutex_main);
	return (NULL);
}
