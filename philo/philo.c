/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:06:33 by stapioca          #+#    #+#             */
/*   Updated: 2022/07/01 19:31:08 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	philo_print(t_main *dt, char *str)
{
	pthread_mutex_lock(&dt->data->mutex_main);
	if (dt->data->stop == 0)
		printf("%lld %d %s\n", get_time() - dt->data->t_start_main, \
					dt->philo->nb_ph, str);
	pthread_mutex_unlock(&dt->data->mutex_main);
}

t_data	init_main(int argc, char **args, t_data dt)
{
	int	i;

	pthread_mutex_init(&dt.mutex_main, NULL);
	dt.nb_of_ph = ft_get(args[1]);
	dt.time_to_die = ft_get(args[2]);
	dt.time_to_eat = ft_get(args[3]);
	dt.time_to_sleep = ft_get(args[4]);
	if (argc == 6)
		dt.steps_to_end = ft_get(args[5]);
	dt.stop = 0;
	dt.count_eat = 0;
	i = 0;
	while (i < dt.nb_of_ph)
	{
		pthread_mutex_init(&dt.mutex_forks[i], NULL);
		i++;
	}
	return (dt);
}

t_philo	get_nb_forks(t_philo philos, t_data dt, int i)
{
	philos.nb_ph = i + 1;
	if (philos.nb_ph != dt.nb_of_ph)
	{
		philos.lf = i;
		philos.rf = i + 1;
	}
	else
	{
		philos.lf = i;
		philos.rf = 0;
	}
	return (philos);
}

void	mondeath_join_dest(t_philo philos[202], t_main ph[202], t_data dt)
{
	int	i;

	usleep(1100);
	pthread_create(&dt.monitor, NULL, monitor_death, &ph[dt.nb_of_ph]);
	i = dt.nb_of_ph;
	pthread_join(dt.monitor, NULL);
	if (dt.nb_of_ph == 1)
		pthread_detach(philos[0].pt);
	while (--i >= 0)
	{
		pthread_join(philos[i].pt, NULL);
	}
	i = 0;
	while (i < dt.nb_of_ph)
	{
		pthread_mutex_destroy(&dt.mutex_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&dt.mutex_main);
}

int	main(int argc, char **args)
{
	t_data		dt;
	t_main		ph[202];
	t_philo		philos[202];
	int			i;

	if (argc == 5 || argc == 6)
	{
		dt.t_start_main = get_time();
		dt = init_main(argc, args, dt);
		i = 0;
		while (i < dt.nb_of_ph)
		{
			philos[i] = get_nb_forks(philos[i], dt, i);
			ph[i].philo = &philos[i];
			ph[i].data = &dt;
			pthread_create(&philos[i].pt, NULL, do_philo, &ph[i]);
			i++;
		}
		ph[dt.nb_of_ph].data = &dt;
		ph[dt.nb_of_ph].philo = &philos[0];
		mondeath_join_dest(philos, ph, dt);
	}
	else
		write(1, "Wrong args.\n", 12);
	return (0);
}
