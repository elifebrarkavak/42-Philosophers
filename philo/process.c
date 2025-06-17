/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elikavak <elikavak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:35:31 by elikavak          #+#    #+#             */
/*   Updated: 2025/06/10 16:35:31 by elikavak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	phil_life_cont(t_philo *phil)
{
	static int	written = 0;
	long long	current_time;

	current_time = present();
	if (!phil->someone_dead && (current_time - phil->last_meal_time)
		>= phil->data->time_to_die)
	{
		phil->someone_dead = 1;
		pthread_mutex_lock(&phil->data->mutex_flag);
		phil->data->dead_flag = 1;
		pthread_mutex_unlock(&phil->data->mutex_flag);
		pthread_mutex_lock(&phil->data->mutex_text);
		if (!written)
		{
			printf("%lld %d is died\n",
				current_time - phil->data->start_time, phil->id);
			written = 1;
		}
		pthread_mutex_unlock(&phil->data->mutex_text);
		return (1);
	}
	return (0);
}

static int	ft_eat(t_philo *phil)
{
	long long	start_time;

	if (phil->someone_dead)
	{
		return (0);
	}
	phil->last_meal_time = present();
	phil->philo_death_time = phil->last_meal_time + phil->data->time_to_die;
	print_text(phil, phil->last_meal_time, phil->id, "is eating\n");
	start_time = present();
	while (!phil->someone_dead)
	{
		if (present() - start_time >= phil->data->time_to_eat)
			break ;
		usleep(1000);
		if (phil_life_cont(phil))
			return (0);
	}
	phil->number_of_eat++;
	return (!phil->someone_dead);
}

static int	ft_sleep(t_philo *phil)
{
	long long	start_time;

	start_time = present();
	print_text(phil, present(), phil->id, "is sleeping\n");
	while (!phil->someone_dead)
	{
		if (present() - start_time >= phil->data->time_to_sleep)
			break ;
		usleep(1000);
		if (phil_life_cont(phil))
			return (0);
	}
	return (!phil->someone_dead);
}

static void	philosopher_routine(t_philo *phil,
	pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	while (phil->number_of_eat != phil->data->num_of_eat && !phil->someone_dead)
	{
		print_text(phil, present(), phil->id, "is thinking\n");
		if (phil_life_cont(phil))
			break ;
		pthread_mutex_lock(first_fork);
		print_text(phil, present(), phil->id, "has taken a fork\n");
		if (phil_life_cont(phil))
		{
			pthread_mutex_unlock(first_fork);
			break ;
		}
		pthread_mutex_lock(second_fork);
		print_text(phil, present(), phil->id, "has taken a fork\n");
		if (!ft_eat(phil))
		{
			pthread_mutex_unlock(second_fork);
			pthread_mutex_unlock(first_fork);
			break ;
		}
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		if (phil->someone_dead || !ft_sleep(phil) || phil_life_cont(phil))
			break ;
	}
}

void	*life_process(void *philo)
{
	t_philo			*phil;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	phil = (t_philo *)philo;
	phil->last_meal_time = present();
	if (phil->data->num_of_philos == 1)
	{
		one_philo(phil->data);
		return (NULL);
	}
	if (phil->id % 2 == 0)
		usleep(1000);
	if (phil->left_fork < phil->right_fork)
	{
		first_fork = phil->left_fork;
		second_fork = phil->right_fork;
	}
	else
	{
		first_fork = phil->right_fork;
		second_fork = phil->left_fork;
	}
	philosopher_routine(phil, first_fork, second_fork);
	return (0);
}
