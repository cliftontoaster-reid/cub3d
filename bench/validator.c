/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:31:37 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/05 16:25:50 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/table.h"
#include "utils/reader.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

typedef struct s_size_stats
{
	int					width;
	int					height;
	int					count;
	double				total_ms;
	double				best_ms;
	double				worst_ms;
	struct s_size_stats	*next;
}						t_size_stats;

static t_size_stats	*find_or_create_stats(t_size_stats **head, int width,
		int height)
{
	t_size_stats	*curr;
	t_size_stats	*new;

	curr = *head;
	while (curr)
	{
		if (curr->width == width && curr->height == height)
			return (curr);
		curr = curr->next;
	}
	new = malloc(sizeof(t_size_stats));
	if (!new)
		return (NULL);
	new->width = width;
	new->height = height;
	new->count = 0;
	new->total_ms = 0.0;
	new->best_ms = 1e308;
	new->worst_ms = 0.0;
	new->next = *head;
	*head = new;
	return (new);
}

static void	free_stats_list(t_size_stats *head)
{
	t_size_stats	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

static char	*join_path(const char *a, const char *b)
{
	size_t	lena;
	size_t	lenb;
	int		need_sep;
	char	*out;

	lena = strlen(a);
	lenb = strlen(b);
	need_sep = (lena == 0 || a[lena - 1] == '/') ? 0 : 1;
	out = malloc(lena + need_sep + lenb + 1);
	if (!out)
		return (NULL);
	memcpy(out, a, lena);
	if (need_sep)
		out[lena] = '/';
	memcpy(out + lena + need_sep, b, lenb + 1);
	return (out);
}

static int	has_cub_suffix(const char *name)
{
	size_t	n;

	n = strlen(name);
	if (n < 4)
		return (0);
	return (strcmp(name + n - 4, ".cub") == 0);
}

static int	process_map_path(const char *path, double *elapsed_ms, int *width,
		int *height)
{
	char	*content;
	t_map	*map;
	clock_t	start;
	clock_t	end;

	start = clock();
	content = read_file(path);
	if (!content)
	{
		fprintf(stderr, "Failed to read file: %s\n", path);
		return (0);
	}
	map = read_map(content);
	if (!map)
	{
		fprintf(stderr, "Failed to parse map: %s\n", path);
		free(content);
		return (0);
	}
	*width = map->width;
	*height = map->height;
	free_map(map);
	free(content);
	end = clock();
	*elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
	return (1);
}

static void	print_progress(int current, int total)
{
	int	bar_width;
	int	pos;
	int	i;
	int	percent;

	bar_width = 50;
	percent = (int)((double)current / total * 100.0);
	pos = (int)((double)current / total * bar_width);
	printf("\r[");
	i = 0;
	while (i < bar_width)
	{
		if (i < pos)
			printf("=");
		else if (i == pos)
			printf(">");
		else
			printf(" ");
		i++;
	}
	printf("] %d/%d (%d%%) ", current, total, percent);
	fflush(stdout);
}

static int	count_cub_files(const char *dirpath)
{
	DIR				*dir;
	struct dirent	*ent;
	int				count;

	count = 0;
	dir = opendir(dirpath);
	if (!dir)
		return (0);
	while ((ent = readdir(dir)) != NULL)
	{
		if (ent->d_name[0] == '.')
			continue ;
		if (has_cub_suffix(ent->d_name))
			count++;
	}
	closedir(dir);
	return (count);
}

int	main(void)
{
	const char		*dirpath = "assets/maps/perf";
	DIR				*dir;
	struct dirent	*ent;
	char			*path;
	double			elapsed_ms;
	int				width;
	int				height;
	t_size_stats	*stats_list;
	t_size_stats	*stats;
	t_size_stats	*curr;
	int				total_count;
	int				total_files;
	int				processed;

	stats_list = NULL;
	total_count = 0;
	processed = 0;
	total_files = count_cub_files(dirpath);
	if (total_files == 0)
	{
		printf("No .cub files found in %s\n", dirpath);
		return (0);
	}
	printf("Found %d .cub files to process\n", total_files);
	dir = opendir(dirpath);
	if (!dir)
	{
		perror("opendir");
		return (1);
	}
	while ((ent = readdir(dir)) != NULL)
	{
		if (ent->d_name[0] == '.')
			continue ;
		if (!has_cub_suffix(ent->d_name))
			continue ;
		processed++;
		print_progress(processed, total_files);
		path = join_path(dirpath, ent->d_name);
		if (!path)
		{
			fprintf(stderr, "\nmalloc failed\n");
			closedir(dir);
			free_stats_list(stats_list);
			return (2);
		}
		if (process_map_path(path, &elapsed_ms, &width, &height))
		{
			stats = find_or_create_stats(&stats_list, width, height);
			if (!stats)
			{
				fprintf(stderr, "\nmalloc failed for stats\n");
				free(path);
				closedir(dir);
				free_stats_list(stats_list);
				return (2);
			}
			stats->count++;
			stats->total_ms += elapsed_ms;
			if (elapsed_ms < stats->best_ms)
				stats->best_ms = elapsed_ms;
			if (elapsed_ms > stats->worst_ms)
				stats->worst_ms = elapsed_ms;
			total_count++;
		}
		free(path);
	}
	closedir(dir);
	printf("\n");
	if (total_count == 0)
	{
		printf("No .cub maps processed from %s\n", dirpath);
		free_stats_list(stats_list);
		return (0);
	}
	printf("\n=== Summary by Map Size ===\n");
	curr = stats_list;
	while (curr)
	{
		printf("\nMap Size: %dx%d\n", curr->width, curr->height);
		printf("  Processed : %d map(s)\n", curr->count);
		printf("  Average   : %.5f ms\n", curr->total_ms / curr->count);
		printf("  Best      : %.5f ms\n", curr->best_ms);
		printf("  Worst     : %.5f ms\n", curr->worst_ms);
		curr = curr->next;
	}
	printf("\n=== Overall Summary ===\n");
	printf("  Total maps processed: %d\n", total_count);
	free_stats_list(stats_list);
	return (0);
}
