/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:10:57 by stapioca          #+#    #+#             */
/*   Updated: 2022/07/01 22:14:07 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_print(t_philo *dt, char *str)
{
	sem_wait(dt->sem_print);
	printf("%lld %d %s\n",
		get_time() - dt->t_start, dt->name, str);
	sem_post(dt->sem_print);
}

int	do_philo(t_philo *dt)
{
	sem_wait(dt->sem_fork);
	philo_print(dt, "has taken a fork");
	if (dt->nb_of_ph == 1)
		return (sem_post(dt->sem_fork), 1);
	sem_wait(dt->sem_fork);
	philo_print(dt, "has taken a fork");
	philo_print(dt, "is eating");
	dt->t_last_eat = get_time();
	ft_usleep(dt->time_to_eat);
	sem_post(dt->sem_fork);
	sem_post(dt->sem_fork);
	dt->count_eat++;
	philo_print(dt, "is sleeping");
	ft_usleep(dt->time_to_sleep);
	philo_print(dt, "is thinking");
	return (0);
}

int	do_kill(t_philo *dt)
{
	int	i;

	i = -1;
	while (++i < dt->nb_of_ph)
		kill(dt->pid[i], SIGKILL);
	return (0);
}
