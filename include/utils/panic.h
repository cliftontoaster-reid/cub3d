/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:49:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 14:54:45 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/// @brief Prints an error message and exits the program using abort().
/// @param message The error message to print.
void	panic(const char *message, const char *file, int line);
