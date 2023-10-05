/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shikim <shikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:08:31 by shikim            #+#    #+#             */
/*   Updated: 2023/10/05 17:19:01 by shikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	calculate_side_dist(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		if (ray->delta_dist_x == NO_VALUE)
			ray->side_dist_x = NO_VALUE;
		else
			ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		if (ray->delta_dist_x == NO_VALUE)
			ray->side_dist_x = NO_VALUE;
		else
			ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		if (ray->delta_dist_y == NO_VALUE)
			ray->side_dist_y = NO_VALUE;
		else
			ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		if (ray->delta_dist_y == NO_VALUE)
			ray->side_dist_y = NO_VALUE;
		else
			ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
	// printf("side_dist_x: %f side_dist_y: %f ", ray->side_dist_x, ray->side_dist_y);
	return ;
}

void	 find_wall(t_ray *ray, t_map *map_info)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map_info->map[ray->map_y][ray->map_x] == '1')
		{
			ray->hit = 1;
		}
	}
	ray->hit = 0;
	return ;
}

void	calculate_distance_to_wall(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = (ray->map_x - player->pos_x + \
		(1 - ray->step_x) / 2) / ray->ray_dir_x;
	}
	else
	{
		ray->perp_wall_dist = (ray->map_y - player->pos_y + \
		(1 - ray->step_y) / 2) / ray->ray_dir_y;
	}
	return ;
}

void	calculate_wall_height(t_ray *ray)
{
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
	return ;
}