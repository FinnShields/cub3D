/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:03:33 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/13 10:39:37 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_BONUS_H
# define VECTOR_BONUS_H

# include <stdlib.h>

# define MALLOC_ERROR 1

typedef struct s_vector_text
{
	char	**text;
	size_t	used_nodes;
	size_t	max_nodes;
}	t_vector;

//vector_expand.c
t_vector	*vector_new(size_t size);
int			vector_add_back(t_vector *old, char *new_data);
void		free_vector(t_vector *vector);

//vector_decrease.c
char		*extract_array(t_vector *vector, size_t array_index);

//vector_copy.c
t_vector	*copy_vector(t_vector *vector);

#endif