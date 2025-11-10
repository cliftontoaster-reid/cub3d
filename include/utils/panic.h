/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:49:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/10 15:19:38 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map/validatorinator.h"

#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_PINK "\033[35m"
#define ANSI_UNDER "\033[4m"
#define ANSI_ITA "\033[3m"
#define ANSI_RESET "\033[0m"

/// @brief Prints an error message and exits the program using abort().
/// @param message The error message to print.
void	panic(const char *message, const char *file, int line);

/// @brief Prints a TODO message then exits the program using abort().
/// @param message The TODO message to print.
/// @param file The source file where the TODO was found.
/// @param line The line number where the TODO was found.
void	todo(const char *message, const char *file, int line);

/// @brief Prints a number to stderr.
/// @param n The number to print.
void	perrornbr(int n);

void	useful_perror(int errnum, const char *msg);

void	print_map_with_marker(int row, int col, t_floodfillinator *ffi,
			const char *msg);

void	print_map_with_marker_simple(int row, int col, t_map *map,
			const char *msg);