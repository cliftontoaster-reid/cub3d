/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:35:40 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/04 11:20:49 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <sys/types.h>

char		*findlast_emptyline(const char *s);
bool		split_first(const char *s, char delimiter, char **out);

const char	**split_lines(const char *s, int *out_count);
void		free_string_array(const char **arr, int count);
