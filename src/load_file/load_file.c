/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikim <shikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:11:50 by shikim            #+#    #+#             */
/*   Updated: 2023/09/19 20:20:58 by shikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_map	*load_file(char *map_path)
{
	t_map	*map_info;
	int		fd;

	printf("2. Loading file...\n");
	fd = open_file(map_path);
	map_info = init_map_info();
	get_texture(map_info, fd);
	// get_map(map_info, fd);
	close(fd);
	printf("✔️ Loading done...\n");
	return (map_info);
}