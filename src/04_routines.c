/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:29:59 by achoukri          #+#    #+#             */
/*   Updated: 2025/08/19 19:53:54 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/prototypes.h"

void	precise_sleep(t_philo *p, long duration)
{
	long	start;
	long	now;

	start = ft_now_ms();
	while (!should_stop(p))
	{
		now = ft_now_ms();
		if (now - start >= duration)
			break ;
		usleep(100);
	}
}

void	lock(pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
}

void	unlock(pthread_mutex_t *mutex)
{
	pthread_mutex_unlock(mutex);
}

int	should_stop(t_philo *p)
{
	int	stop;

	pthread_mutex_lock(&p->rules->state_lock);
	stop = p->rules->stop;
	pthread_mutex_unlock(&p->rules->state_lock);
	return (stop);
}

void	take_forks(t_philo *p)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (should_stop(p))
		return ;
	if (p->id % 2 == 0)
	{
		first_fork = p->right_fork;
		second_fork = p->left_fork;
	}
	else
	{
		first_fork = p->left_fork;
		second_fork = p->right_fork;
	}
	lock(first_fork);
	philo_log(p, "has taken a fork");
	lock(second_fork);
	philo_log(p, "has taken a fork");
	lock(&p->rules->state_lock);
	p->last_meal = ft_now_ms();
	unlock(&p->rules->state_lock);
}
