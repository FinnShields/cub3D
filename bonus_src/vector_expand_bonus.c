/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_expand_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:04:40 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/13 10:40:21 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_bonus.h"

void	free_vector(t_vector *vector)
{
	size_t	i;

	i = 0;
	while (i < vector->used_nodes)
	{
		free(vector->text[i]);
		i++;
	}
	free(vector->text);
	free(vector);
}

t_vector	*vector_new(size_t size)
{
	t_vector	*new_vector;

	new_vector = (t_vector *)malloc(sizeof(t_vector));
	if (new_vector == NULL)
		return (NULL);
	new_vector->text = (char **)malloc((size + 1) * sizeof(char *));
	if (new_vector->text == NULL)
		return (NULL);
	new_vector->max_nodes = size;
	new_vector->used_nodes = 0;
	new_vector->text[0] = NULL;
	return (new_vector);
}

static char	**vector_array_realloc(char ***old_text, size_t node_max)
{
	char	**new_text;
	size_t	i;

	i = 0;
	new_text = (char **)malloc(sizeof(char *) * ((node_max * 2) + 1));
	if (new_text == NULL)
		return (NULL);
	while (i < node_max)
	{
		new_text[i] = (char *)(*old_text)[i];
		i++;
	}
	new_text[i] = NULL;
	free(*old_text);
	return (new_text);
}

static int	expand_vector(t_vector *old)
{
	old->text = vector_array_realloc(&old->text, old->max_nodes);
	if (old->text == NULL)
	{
		return (MALLOC_ERROR);
	}
	old->max_nodes *= 2;
	return (0);
}

int	vector_add_back(t_vector *old, char *new_data)
{
	if (old->used_nodes == old->max_nodes)
	{
		if (expand_vector(old) == MALLOC_ERROR)
		{
			free_vector(old);
			free(new_data);
			return (MALLOC_ERROR);
		}
	}
	old->text[old->used_nodes] = new_data;
	old->used_nodes++;
	old->text[old->used_nodes] = NULL;
	return (0);
}
