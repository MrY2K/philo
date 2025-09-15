/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:15:19 by achoukri          #+#    #+#             */
/*   Updated: 2025/05/02 22:27:54 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//error handling:
void	ft_error_msg(const char *msg);

void	ft_error_msg(const char *msg)
{
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
}
