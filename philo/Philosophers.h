/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:09:12 by stapioca          #+#    #+#             */
/*   Updated: 2022/06/01 20:56:03 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				nb_ph;
	int				lf;
	int				rf;
	pthread_t		pt;
	long long int	t_start;
}	t_philo;

typedef struct s_stract
{
	int				nb_of_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_times_each_ph_must_eat;
	pthread_mutex_t	mutex_forks[200];
	pthread_mutex_t	mutex_main;
	long long int	t_start_main;
	int				stop;
	pthread_t		monitor;
}	t_data;

typedef struct s_philosopher_args
{
	t_philo		*philo;
	t_data		*data;
}	t_main;

int			ft_atoi(const char *str);
long long	get_time(void);

#endif