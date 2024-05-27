/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_rgb_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:15 by skorbai           #+#    #+#             */
/*   Updated: 2024/05/15 14:36:42 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	convert_rgb(int *asset, char **strs)
{
	size_t	i;
	char	*re_converted;
	size_t	len;
	bool	result;

	i = 0;
	result = true;
	while (i < 3)
	{
		asset[i] = ft_atoi(strs[i]);
		re_converted = ft_itoa(asset[i]);
		if (re_converted == NULL)
			return (error_msg("Malloc failure"));
		len = ft_strlen(strs[i]);
		if (ft_strncmp(re_converted, strs[i], len) != 0)
			result = false;
		free(re_converted);
		i++;
	}
	if (result == false)
		error_msg("Invalid RGB configuration");
	return (result);
}
