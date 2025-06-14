/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elikavak <elikavak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:35:20 by elikavak          #+#    #+#             */
/*   Updated: 2025/06/10 16:35:20 by elikavak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		p_thread;
	long long		philo_death_time;
	int				time_to_die;
	int				number_of_eat;
	int				someone_dead;
	long long		last_meal_time;
	struct s_data	*data;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	long			num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_of_eat;
	long long		start_time;
	int				dead_flag;
	pthread_mutex_t	mutex_flag;
	pthread_mutex_t	mutex_text;
	pthread_mutex_t	*forks;
}					t_data;

int			ft_isdigit(char *str);
void		*life_process(void *phil);
long long	present(void);
void		print_text(t_philo *phil, long long time, int num, char *str);
int			initialize_simulation(int argc, char **argv, t_data *data);
void		assign_philosophers(t_data *data);
void		setup_mutexes(t_data *data);
void		allocate_and_initialize_forks(t_data *data);
long		ft_atoi(char *str);
void		ft_run_philos(t_data *data);
void		*one_philo(void *data);

#endif
