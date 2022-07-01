/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:12:45 by stapioca          #+#    #+#             */
/*   Updated: 2022/07/01 22:14:17 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arg(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (err_print(1));
	if (ft_get(av[1]) <= 0 || ft_get(av[2]) <= 0
		|| ft_get(av[3]) <= 0 || ft_get(av[4]) <= 0
		|| (ac == 6 && ft_get(av[5]) <= 0))
		return (err_print(2));
	return (0);
}

t_philo	*init_philo(int ac, char **av)
{
	t_philo	*dt;

	dt = malloc(sizeof(t_philo));
	if (!dt)
		return (err_print(3), NULL);
	dt->nb_of_ph = ft_get(av[1]);
	dt->time_to_die = ft_get(av[2]);
	dt->time_to_eat = ft_get(av[3]);
	dt->time_to_sleep = ft_get(av[4]);
	dt->nbr_lunch = 0;
	if (ac == 6)
		dt->nbr_lunch = ft_get(av[5]);
	dt->name = 0;
	dt->count_eat = 0;
	dt->stop = 0;
	dt->t_start = 0;
	dt->t_last_eat = 0;
	return (dt);
}

int	small_free(t_philo *dt, int code)
{
	err_print(code);
	free(dt);
	return (1);
}

int	semaph_init(t_philo *dt)
{
	sem_unlink("print");
	sem_unlink("fork");
	dt->sem_print = sem_open("print", O_CREAT, 0644, 1);
	if (dt->sem_print == SEM_FAILED)
		return (small_free(dt, 4));
	dt->sem_fork = sem_open("fork", O_CREAT, 0644, dt->nb_of_ph);
	if (dt->sem_fork == SEM_FAILED)
		return (small_free(dt, 4));
	dt->pid = malloc(sizeof(pid_t) * dt->nb_of_ph);
	if (!dt->pid)
	{
		sem_close(dt->sem_print);
		sem_close(dt->sem_fork);
		return (small_free(dt, 3));
	}
	return (0);
}
