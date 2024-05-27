/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_decrease_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:59:22 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/13 11:56:53 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_bonus.h"

static void	rearrange_vector(t_vector *vector, size_t index, char **new_text)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < index)
	{
		new_text[i] = vector->text[i];
		i++;
	}
	j = i + 1;
	while (j < vector->used_nodes)
	{
		new_text[i] = vector->text[j];
		i++;
		j++;
	}
	free(vector->text);
	vector->text = new_text;
	vector->used_nodes = vector->used_nodes - 1;
	vector->text[vector->used_nodes] = NULL;
	vector->max_nodes = vector->max_nodes - 1;
}

char	*extract_array(t_vector *vector, size_t array_index)
{
	char	**new_text;
	char	*extracted_array;

	if (array_index >= vector->used_nodes)
		return (NULL);
	new_text = (char **)malloc(sizeof(char *) * (vector->max_nodes - 1));
	if (new_text == NULL)
		return (NULL);
	extracted_array = vector->text[array_index];
	rearrange_vector(vector, array_index, new_text);
	return (extracted_array);
}
