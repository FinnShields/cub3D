/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_copy_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:40:35 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/13 10:40:09 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector	*copy_vector(t_vector *vector)
{
	t_vector	*copy;
	size_t		i;
	char		*copy_of_line;

	copy = vector_new(vector->used_nodes);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < vector->used_nodes)
	{
		copy_of_line = ft_strdup(vector->text[i]);
		if (copy_of_line == NULL)
			return (NULL);
		if (vector_add_back(copy, copy_of_line) == MALLOC_ERROR)
		{
			free_vector(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}
