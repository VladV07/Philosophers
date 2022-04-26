/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:06:33 by stapioca          #+#    #+#             */
/*   Updated: 2022/04/26 21:42:59 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*print1(void *buf)
{
	t_philo	*ph;

	ph = (t_philo *)buf;
	usleep(100);
	pthread_mutex_lock(&ph->mutex);
	printf("1nb_of_ph = %d\n", ph->nb_of_ph); //
	printf("1time_to_die = %d\n", ph->time_to_die); //
	printf("1time_to_eat = %d\n", ph->time_to_eat); //
	printf("1time_to_sleep = %d\n", ph->time_to_sleep); //
	//printf("nb = %s\n", (char *)buf);
	pthread_mutex_unlock(&ph->mutex);
	return (NULL);
}

void	*print2(void *buf)
{
	t_philo	*ph;

	ph = (t_philo *)buf;
	usleep(100);
	pthread_mutex_lock(&ph->mutex);
	printf("2nb_of_ph = %d\n", ph->nb_of_ph); //
	printf("2time_to_die = %d\n", ph->time_to_die); //
	printf("2time_to_eat = %d\n", ph->time_to_eat); //
	printf("2time_to_sleep = %d\n", ph->time_to_sleep); //
	//printf("nb = %s\n", (char *)buf);
	pthread_mutex_unlock(&ph->mutex);
	return (NULL);
}

void	*print3(void *buf)
{
	t_philo	*ph;

	ph = (t_philo *)buf;
	usleep(100);
	pthread_mutex_lock(&ph->mutex);
	printf("3nb_of_ph = %d\n", ph->nb_of_ph); //
	printf("3time_to_die = %d\n", ph->time_to_die); //
	printf("3time_to_eat = %d\n", ph->time_to_eat); //
	printf("3time_to_sleep = %d\n", ph->time_to_sleep); //
	//printf("nb = %s\n", (char *)buf);
	pthread_mutex_unlock(&ph->mutex);
	return (NULL);
}

int	main(int argc, char **args)
{
	t_philo			*ph;
	int				i;

	if (argc == 5)
	{
		ph = malloc(sizeof(t_philo));
		if (ph == NULL)
			return (0);
		ph->nb_of_ph = ft_atoi(args[1]);
		ph->time_to_die = ft_atoi(args[2]);
		ph->time_to_eat = ft_atoi(args[3]);
		ph->time_to_sleep = ft_atoi(args[4]);
		pthread_mutex_init(&ph->mutex, NULL);
		ph->pt = malloc(sizeof(ph->pt) * ph->nb_of_ph);
		i = 0;
		while (i < ph->nb_of_ph)
		{
			pthread_create(&ph->pt[i], NULL, print1, ph);
			i++;
		}
		//pthread_create(&ph->pt[0], NULL, print1, ph);
		//pthread_create(&ph->pt[1], NULL, print2, ph);
		//pthread_create(&ph->pt[2], NULL, print3, ph);
		//pthread_create(&t2, NULL, print, (void *)321);
		printf("nb_of_ph = %d\n", ph->nb_of_ph); //
		printf("time_to_die = %d\n", ph->time_to_die); //
		printf("time_to_eat = %d\n", ph->time_to_eat); //
		printf("time_to_sleep = %d\n", ph->time_to_sleep); //
		while (i >= 0)
		{
			pthread_join(ph->pt[i], NULL);
			i--;
		}
		/*pthread_join(ph->pt[0], NULL);
		pthread_join(ph->pt[1], NULL);
		pthread_join(ph->pt[2], NULL);*/
		//pthread_join(t2, NULL);
		free(ph->pt);
		free(ph);
	}
	else
		write(1, "Wrong args.\n", 12);
	return (0);
}
