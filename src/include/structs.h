/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:27:44 by achoukri          #+#    #+#             */
/*   Updated: 2025/07/09 21:21:24 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "includes.h"

typedef struct s_data
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_p_must_eat;
	int					max_meals;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		state_lock;
	long				start_time;
	int					stop;
}	t_data;

typedef struct s_philo
{
	int					id;
	long				last_meal;
	int					eat_count;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*rules;
}	t_philo;

#endif
