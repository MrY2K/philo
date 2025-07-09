/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:29:59 by achoukri          #+#    #+#             */
/*   Updated: 2025/07/09 23:13:58 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/prototypes.h"

int	check_should_stop(t_philo *p)
{
	int	should_stop;

	pthread_mutex_lock(&p->rules->state_lock);
	should_stop = p->rules->stop;
	pthread_mutex_unlock(&p->rules->state_lock);
	return (should_stop);
}

void	philo_pick_forks(pthread_mutex_t *first,
				pthread_mutex_t *second, t_philo *p)
{
	pthread_mutex_lock(first);
	philo_log(p, "has taken a fork");
	pthread_mutex_lock(second);
	philo_log(p, "has taken a fork");
}

void	philo_eat_and_release_forks(t_philo *p, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(&p->rules->state_lock);
	p->last_meal = ft_now_ms();
	p->eat_count++;
	pthread_mutex_unlock(&p->rules->state_lock);
	philo_log(p, "is eating");
	usleep(p->rules->time_to_eat * 1000);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

int	check_meal_limit_reached(t_philo *p)
{
	int	current_eat_count;

	if (p->rules->number_of_times_each_p_must_eat > 0)
	{
		pthread_mutex_lock(&p->rules->state_lock);
		current_eat_count = p->eat_count;
		pthread_mutex_unlock(&p->rules->state_lock);
		if (current_eat_count >= p->rules->number_of_times_each_p_must_eat)
			return (1);
	}
	return (0);
}

void	*philo_life(void *arg)
{
    t_philo			*p;
    pthread_mutex_t	*first;
    pthread_mutex_t	*second;

    p = (t_philo *)arg;
    if (handle_one_philo(arg) == -1)
        return (NULL);
    setup_fork_order(p, &first, &second);
        if (p->id % 2 == 0)
        usleep(p->rules->time_to_eat * 750);  // 75% of eating time instead of 50%
        
    while (!check_should_stop(p))
    {
        philo_log(p, "is thinking");
        usleep(1000);  // 1ms thinking time        
        philo_pick_forks(first, second, p);
        philo_eat_and_release_forks(p, first, second);
        if (check_should_stop(p))
            break;
        philo_log(p, "is sleeping");
        usleep(p->rules->time_to_sleep * 1000);
    }
    return (NULL);
}