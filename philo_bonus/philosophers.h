/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:09:12 by stapioca          #+#    #+#             */
/*   Updated: 2022/07/01 22:15:31 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free, exit
# include <unistd.h>	// usleep, write, fork
# include <signal.h>	// kill
# include <pthread.h>	// pthread_create
# include <sys/time.h>	// gettimeofday
# include <sys/wait.h>	// waitpid
# include <semaphore.h>	// sem_open, sem_close ... sem_unlink

typedef struct s_philo
{
	int			nb_of_ph;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_lunch;
	int			name;
	int			count_eat;
	int			stop;
	long long	t_start;
	long long	t_last_eat;
	pid_t		*pid;
	pthread_t	monitor;
	sem_t		*sem_print;
	sem_t		*sem_fork;
}	t_philo;

int			check_arg(int ac, char **av);
t_philo		*init_philo(int ac, char **av);
int			small_free(t_philo *dt, int code);
int			semaph_init(t_philo *dt);

int			ft_get(const char *str);
long long	get_time(void);
void		ft_usleep(long long time);
int			err_print(int code);
void		ft_free(t_philo *dt);

void		philo_print(t_philo *dt, char *str);
int			do_philo(t_philo *dt);
int			do_kill(t_philo *dt);
#endif
