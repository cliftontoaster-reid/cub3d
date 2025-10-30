/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:49:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/10/30 17:00:47 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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