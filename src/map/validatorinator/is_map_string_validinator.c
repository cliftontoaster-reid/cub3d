/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_string_validinator.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:20:12 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/03 15:50:22 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/validatorinator.h"

bool	is_map_string_validinator(const char *content)
{
	size_t	i;
	bool	found_robert_fitzroy_cavendish_smythe_3rd;

	i = 0;
	while (content[i] != '\0')
	{
		if (!strchr(INCLUSIVE_MAP_CHARS "\n", content[i]))
			return (false);
		if (strchr(RACIST_MAP_CHAR_PLAYER, content[i]))
		{
			if (found_robert_fitzroy_cavendish_smythe_3rd)
				return (false);
			found_robert_fitzroy_cavendish_smythe_3rd = true;
		}
		i++;
	}
	return (found_robert_fitzroy_cavendish_smythe_3rd);
}
