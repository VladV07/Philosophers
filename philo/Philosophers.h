/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:09:12 by stapioca          #+#    #+#             */
/*   Updated: 2022/07/01 01:36:26 by stapioca         ###   ########.fr       */
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
	long long int	t_start_eat;
	long long int	t_start_sleep;
	long long int	step;
	int				end_eat;
	pthread_mutex_t	mutex_philo;
}	t_philo;

typedef struct s_stract
{
	int				nb_of_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_times_each_ph_must_eat;
	pthread_mutex_t	mutex_forks[202];
	pthread_mutex_t	mutex_main;
	pthread_mutex_t	mutex_philo;
	long long int	t_start_main;
	int				stop;
	int				nb_ph_die;
	int				time_die;
	long long int	steps_to_end;
	int				count_eat;
	pthread_t		monitor;
}	t_data;

typedef struct s_philosopher_args
{
	t_philo		*philo;
	t_data		*data;
}	t_main;

int			ft_get(const char *str);
long long	get_time(void);
void		philo_print(t_main *dt, char *str);
t_main		*protected_get_time(void *arg);
void		mutex_forks(void *arg);
int			ft_eat(t_main *dt);
int			ft_sleep(t_main *dt);
void		*do_philo(void *arg);
void		*monitor_death(void *arg);

#endif