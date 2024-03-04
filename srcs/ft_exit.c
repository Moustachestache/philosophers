/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjochum <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:02:16 by mjochum           #+#    #+#             */
/*   Updated: 2023/10/15 12:03:39 by mjochum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_exit(int status, t_vars *vars)
{
	size_t	i;

	i = 0;
	while (i < vars->nphilos)
	{
		pthread_detach(vars->philo[i]->pthread);
		free(vars->philo[i]);
		free(vars->fork[i]);
		i++;
	}
	free(vars->philo);
	free(vars->fork);
	free(vars);
	printf("exited with exit code %i\n", status);
}
