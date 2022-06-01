/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:06:33 by stapioca          #+#    #+#             */
/*   Updated: 2022/06/01 21:58:00 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"
/*
void	ph_print(t_philo *ph, char *str)
{
	pthread_mutex_lock(&ph->mutex_main);
	if (!ph->stop)
		printf("%d %s\n", ph->nb_ph, str);
	pthread_mutex_unlock(&ph->mutex_main);
}
*/

void	*monitor_death(void *arg)
{
	t_main		*dt;
	int			i;

	dt = (t_main *)arg;
	while (1)
	{
		i = 0;
		while (i < dt->data->nb_of_ph)
		{
			//pthread_mutex_lock(&ph->mutex_main);
			if (dt->data->stop == 1)
			{
				printf("monitor_death: DEATH, stop = %d\n", dt->data->stop);
				//pthread_mutex_unlock(&ph->mutex_main);
				return (NULL);
			}
			//printf("monitor_death: ph[ %d ], stop = %d\n", (ph0 + i)->nb_ph, (ph0 + i)->stop);
			i++;
			//pthread_mutex_unlock(&ph->mutex_main);
		}
	}
	return (NULL);
}

void	ft_eat(t_main *dt)
{
	printf("%lld %d do_philo: Phil eat.\n",dt->data->t_start_main - get_time(), dt->philo->nb_ph);
	usleep(dt->data->time_to_eat * 1000);
}

void	ft_sleep(t_main *dt)
{
	printf("%lld %d do_philo: Phil sleep.\n",dt->data->t_start_main - get_time(), dt->philo->nb_ph);
	usleep(dt->data->time_to_sleep * 1000);
}

void	*do_philo(void *arg)
{
	t_main		*dt;

	dt = (t_main *)arg;

	if (dt->philo->nb_ph % 2 == 0)
		usleep(2500);

	while (dt->data->stop != 1)
	{

		printf("do_philo: Phil %d\n", dt->philo->nb_ph);

		//printf("do_philo: get_time= %lld ,Phil %d \n", get_time(), ph->nb_ph); //
		if (dt->philo->nb_ph != dt->data->nb_of_ph)
		{

			pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->lf]);
			printf("%lld %d do_philo: Phil has taken a l fork.\n",dt->data->t_start_main - get_time(), dt->philo->nb_ph);
			pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->rf]);
			printf("%lld %d do_philo: Phil has taken a r fork.\n",dt->data->t_start_main - get_time(), dt->philo->nb_ph);
		}
		else
		{
			printf("do_philo: ph->nb_ph == ph->nb_of_ph\n");
			pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->rf]);
			printf("%lld %d do_philo: Phil has taken a r fork.\n",dt->data->t_start_main - get_time(), dt->philo->nb_ph);
			pthread_mutex_lock(&dt->data->mutex_forks[dt->philo->lf]);
			printf("%lld %d do_philo: Phil has taken a l fork.\n",dt->data->t_start_main - get_time(), dt->philo->nb_ph);
		}
		//pthread_mutex_unlock(&ph->mutex_main);
		dt->philo->t_start = get_time();
		ft_eat(dt);
		pthread_mutex_unlock(&dt->data->mutex_forks[dt->philo->rf]);
		pthread_mutex_unlock(&dt->data->mutex_forks[dt->philo->lf]);
		ft_sleep(dt);
		printf("%lld %d do_philo: Phil thinking....\n",dt->data->t_start_main - get_time(), dt->philo->nb_ph);
		//pthread_mutex_lock(&ph->mutex);
		//pthread_mutex_lock(&ph->mutex_main);
		printf("do_philo: g_t - t_s= %lld,Phil %d \n", get_time() - dt->philo->t_start, dt->philo->nb_ph); //
		//pthread_mutex_unlock(&ph->mutex_main);
		if ((get_time() - dt->philo->t_start) >= (dt->data->time_to_die))
		{

			printf("do_philo: Phil %d die(\n", dt->philo->nb_ph);

			dt->data->stop = 1;

			printf("do_philo: Phil STOP= %d\n", dt->data->stop);
			//pthread_mutex_unlock(&ph->mutex_main);
		}

	}
	printf("\n");
	//pthread_mutex_unlock(&ph->mutex_main);
	//pthread_mutex_unlock(&ph->mutex_main);
	//pthread_mutex_lock(&ph->mutex_main);
	//pthread_mutex_unlock(&ph->mutex_main);
	//pthread_mutex_unlock(&ph->mutex);

	return (NULL);
}

int	main(int argc, char **args)
{
	t_data		dt;
	t_main		ph[200];
	t_philo		philos[200];
	int			i;

	if (argc == 5)
	{
		i = 0;
		pthread_mutex_init(&dt.mutex_main, NULL);
		dt.t_start_main = get_time();
		dt.nb_of_ph = ft_atoi(args[1]);
		dt.time_to_die = ft_atoi(args[2]);
		dt.time_to_eat = ft_atoi(args[3]);
		dt.time_to_sleep = ft_atoi(args[4]);

		printf("///////////////////////////////////////////////////////////////////////////////\n"); //
		while (i < dt.nb_of_ph + 1)
		{
			//ph[i] = malloc(sizeof(t_philo));
			//if (ph[i] == NULL)
			//	return (0);
			philos[i].nb_ph = i + 1;
			if (philos[i].nb_ph != dt.nb_of_ph)
			{
				philos[i].lf = i;
				philos[i].rf = i + 1;
			}
			else
			{
				philos[i].lf = i;
				philos[i].rf = 0;
			}
			ph[i].philo = &philos[i];
			ph[i].data = &dt;
			pthread_mutex_init(&dt.mutex_forks[i], NULL);

			printf("%lld main: pthread_mutex_init Phil %d\n",dt.t_start_main - get_time(), philos[i].nb_ph); //

			if (i == dt.nb_of_ph)
				pthread_create(&dt.monitor, NULL, monitor_death, &ph[i]);
			else
				pthread_create(&philos[i].pt, NULL, do_philo, &ph[i]);

			i++;
		}

		i = dt.nb_of_ph + 1;
		if (pthread_join(dt.monitor, NULL) != 0)
			printf("main: ERROR pthread_join != 0, i=%d\n", i);
		else
			printf("main: DONE pthread_join, i=%d\n", i);

		while (--i >= 0)
		{
			if (pthread_join(philos[i].pt, NULL) != 0)
				printf("main: ERROR pthread_join != 0, i=%d\n", i);
			else
				printf("main: DONE pthread_join, i=%d\n", i);
		}

		/*i = 0;
		while (i < ft_atoi(args[1]) + 1)
		{
			free(ph[i]);
			i++;
		}*/
	}
	else
		write(1, "Wrong args.\n", 12);
	return (0);
}
