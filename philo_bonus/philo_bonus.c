/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:14:40 by stapioca          #+#    #+#             */
/*   Updated: 2022/07/01 22:16:14 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *tmp)
{
	t_philo	*dt;

	dt = (t_philo *)tmp;
	while (1)
	{
		if (dt->nbr_lunch)
			if (dt->count_eat == dt->nbr_lunch)
				break ;
		if (get_time() - dt->t_last_eat > dt->time_to_die)
		{
			dt->stop = 1;
			sem_wait(dt->sem_print);
			printf("%lld %d is died\n",
				get_time() - dt->t_start, dt->name);
			break ;
		}
	}
	if (dt->stop)
		exit (1);
	else
		exit (0);
}

int	philo_life(t_philo *dt)
{
	if (pthread_create(&dt->monitor, NULL, &monitor, dt))
		return (err_print(6));
	if (dt->name % 2 == 1)
		usleep(500);
	while (1)
	{
		if (dt->nbr_lunch)
			if (dt->count_eat == dt->nbr_lunch)
				break ;
		if (do_philo(dt))
			break ;
	}
	if (pthread_join(dt->monitor, NULL))
		return (err_print(7));
	return (0);
}

int	start_game(t_philo *dt)
{
	int	i;
	int	status;

	i = -1;
	dt->t_start = get_time();
	while (++i < dt->nb_of_ph)
	{
		dt->pid[i] = fork();
		if (dt->pid[i] == -1)
			return (err_print(5));
		if (dt->pid[i] == 0)
		{
			dt->name = i + 1;
			dt->t_last_eat = dt->t_start;
			if (philo_life(dt))
				return (0);
		}
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
			return (do_kill(dt));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*dt;

	if (check_arg(argc, argv))
		return (1);
	dt = init_philo(argc, argv);
	if (semaph_init(dt))
		return (1);
	if (start_game(dt))
		return (1);
	ft_free(dt);
	return (0);
}
