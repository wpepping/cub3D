/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:13:24 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/25 12:41:42 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <linux/limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define FOV 1.047198 // 60 degrees in radians
# define TILE_SZ 20
# define MINI_SIZE 250
# define CHAR_HEIGHT 32
# define CUBE_SIZE 180
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 640
# define MOVE_SPEED 0.01
# define ENEMY_MOVE_SPEED 0.02
# define MOUSE_SENSITIVITY 0.001
# define ROTATE_SPEED 0.001
# define MS_BETWEEN_FRAMES 10
# define MOVEMENT_DELAY 10
# define DOOR_STEP 5
# define EPSILON 1e-6
# define M_PI 3.14159265358979323846
# define SQRT_2 1.4142
# define WINDOW_NAME "Cub3d"
# define MAP_ERROR "Map error"
# define OOM_ERROR "Out of memory error"
# define GUN_TEXTURE_BASE_NAME "textures/gun0.xpm"

# define EMPTY 48
# define WALL 49
# define NORTH 78
# define EAST 69
# define SOUTH 83
# define WEST 87
# define SPACE 32
# define DOOR 68
# define ENEMY 88

# ifndef REQUIRE_SPACE
#  define REQUIRE_SPACE false
# endif

# ifndef BONUS
#  define BONUS false
# endif

typedef enum e_door_state
{
	IDLE,
	OPENING,
	CLOSING
}					t_door_state;

typedef struct s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct s_door
{
	t_coord			coord;
	int				state;
	int				pos;
	long			last_move;
}					t_door;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
	int				nr_of_doors;
	t_door			*doors;
}					t_map;

typedef struct s_player
{
	t_coord			pos;
	double			dir;
	int				health;
	bool			is_shooting;
	int				gun_texture;
	long			gun_last_updated;
}					t_player;

typedef enum e_state
{
	WALK,
	ATTACK,
	DIE
}					t_state;

typedef enum e_game_state
{
	PLAYING,
	PAUSED,
	GAME_OVER
}					t_game_state;

typedef struct s_enemy
{
	t_coord			pos;
	t_state			state;
	int				frame;
	double			last_frame_time;
	t_coord			prev_pos;
	t_coord			target;
	bool			visible;
	int				size;
}					t_enemy;

typedef struct s_key_state
{
	bool			mv_up;
	bool			mv_dn;
	bool			mv_r;
	bool			mv_l;
	bool			rot_r;
	bool			rot_l;
	bool			run;
}					t_key_state;

typedef struct s_image
{
	void			*img_ptr;
	char			*buff;
	int				lsize;
	int				bpp;
	int				endian;
	int				width;
	int				height;
}					t_image;

typedef struct s_textures
{
	t_image			north;
	t_image			east;
	t_image			south;
	t_image			west;
	t_image			floor;
	t_image			ceiling;
	t_image			enemy[11];
	t_image			healthbar[9];
	t_image			gun[3];
	t_image			door;
	t_image			gameover;
}					t_textures;

typedef struct s_data
{
	t_map			*map;
	t_player		*player;
	t_game_state	game_state;
	t_enemy			*enemies;
	int				nr_of_enemies;
	t_textures		*textures;
	t_door			*active_door;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*imgbuff;
	int				lsize;
	int				bpp;
	int				endian;
	int				floor[3];
	int				ceiling[3];
	double			focal_len;
	long			last_render;
	long			last_move_time;
	long			last_strafe_time;
	int				mouse_x;
	t_key_state		key_state;
	double			sin_table[3600];
	double			cos_table[3600];
}					t_data;

typedef struct s_config
{
	char			*north;
	char			*east;
	char			*south;
	char			*west;
	char			*floor;
	char			*ceiling;
	char			*enemy;
	char			*door;
	int				map_start;
}					t_config;

typedef struct s_sprite_info
{
	int				screen_x;
	double			dir;
	int				min_x;
	int				max_x;
	int				len;
	int				middle;
}					t_sprite_info;

typedef struct s_hit
{
	double			dir;
	int				screen_x;
}					t_hit;

typedef struct s_sprite
{
	t_coord			pos;
	int				frame;
	int				height;
	int				width;
	bool			is_enemy;
	bool			is_collect;
	t_sprite_info	*info;
}					t_sprite;

typedef struct s_ray
{
	t_coord			coll;
	bool			is_horiz;
	bool			is_door;
	int				map_item;
	double			dist;
	double			dir;
}					t_ray;

// raytracing
t_ray				*cast_rays(t_map *map, t_player p);
double				get_horiz_coll(t_player p, t_ray *r, t_map *map);
double				get_vert_coll(t_player p, t_ray *r, t_map *map);

// Read map
int					read_map(t_data *data, char *fname);
int					read_map_content(t_map *map, int fd, int map_start);
int					get_map_dimensions(t_map *map, int fd);
int					read_to_eoln(int fd, char *value);
int					try_save(char **dest, char *src);
int					save_rgbs(char *str, int dest[3]);
int					is_valid_map(t_map *map, t_player *player);

// Render
void				render_frame(t_data *data);
void				draw_bonus(t_data *data);

// textures
int					load_textures(t_data *data, t_config *config);
int					load_bonus_textures(t_data *data, t_config *cfg);
int					load_image(void *mlx_ptr, t_image *img, char *fname);
void				unload_textures(void *mlx_ptr, t_textures *textures);

// movement
bool				should_move(bool direction, bool opposite);
bool				move_player(t_data *data, bool rev);
bool				strafe_player(t_data *data, bool left);
bool				rotate_player(t_data *data, bool left, double rotate_speed);

// Gun
bool				update_gun(t_player *player);

// Doors
bool				move_door(t_data *data, t_door *door);
void				activate_door(t_data *data, t_coord coord);
bool				is_door(t_map *map, t_coord coord);
bool				is_door_coll(t_map *map, t_coord coll, bool is_horiz);

// Events
int					handle_loop(t_data *data);
int					handle_close(t_data *data);
int					handle_mouse(void *data);
int					handle_mouse_move(int x, int y, t_data *data);
int					handle_key_press(int keycode, t_data *data);
int					handle_key_release(int keycode, t_data *data);
int					handle_mouse_click(int button, int x, int y, t_data *data);

// Clean up
void				cleanup(t_data *data);
void				free_map(char **map);
void				free_config(t_config *config);
void				clean_exit(t_data *data, char *message, int exit_status);

// Inits
void				init_data(t_data *data);
void				init_textures(t_textures *textures);
void				init_config(t_config *config);
void				init_trig_tables(double *sin_table, double *cos_table);
int					init_window(t_data *data);
void				init_map(t_map *map);
int					init_doors(t_map *map);
void				init_events(t_data *data);
int					init_enemies(t_data *data);
int					init_player(t_map *map, t_player *player);

// Utils
char				*file_ext(char *fname);
double				get_angle(char dir);
bool				ft_isnum(char *str);
long				currtime(void);
bool				is_wall(t_coord pos, t_map *map);
char				*ft_strdup2(char *s, size_t n);
int					get_map_item(t_coord pos, t_map *map);
int					get_dir(double angle);
bool				coord_equals(t_coord c, t_coord d);
t_coord				coord_add(t_coord c, t_coord d);
t_coord				pixel2grid(t_coord pixel_pos);
t_coord				get_gridpos_in_front(t_player *player);
int					max(int a, int b);
double				norm_angle(double angle);
double				deg_to_rad(double degrees);
double				radians_to_degrees(double radians);
int					nr_of_thing(t_map *map, int thing);

t_coord				get_offset(t_data *data);
int					init_line_vars(t_coord p1, t_coord p2, t_coord *dist,
						t_coord *step);

// render utils
double				norm_angle(double angle);
double				deg_to_rad(double degrees);
int					angle_to_index(double angle);
int					check_dir(double angle, bool is_horiz);
double				projected_wall_height(int focal_len, double dist);
double				get_dist(double angle, t_coord coll, t_player p);
double				get_dir_to(t_coord pos, t_coord target);

// enemy
void				update_enemy_frame(t_enemy *enemy);
int					move_enemies(t_data *data);
void				kill_enemy(t_data *data, t_coord pos);

// sprites
t_sprite			*get_sprite_coll(t_data *data, t_ray *rays,
						t_sprite *sprite);
void				put_sprite(t_data *data, t_sprite *sprite);

// minimap
void				draw_minimap(t_data *data, t_ray *rays);

// render
void				render_frame(t_data *data);

// render utils
void				set_pixel(t_data *data, int c[3], int x, int y);
void				put_pixel_from_img(t_data *data, t_image *src_img,
						t_coord src_coord, t_coord dest_coord);
t_image				*get_texture(t_textures *textures, t_ray *r);
int					get_tex_offset(t_ray r);
double				get_dist(double angle, t_coord coll, t_player p);

// environment
void				draw_walls(t_data *data, t_ray *rays, int i, int j);
void				draw_ceiling(t_data *data, int i, int j, bool is_texture);
void				draw_floor(t_data *data, int i, int j, bool is_texture);

// raytrace_utils
int					check_dir(double angle, bool is_horiz);
t_coord				get_ray_delta(t_ray *r, bool is_horiz);
t_coord				get_ray_delta_hori(t_ray *r);
t_coord				get_ray_delta_vert(t_ray *r);
double				projected_wall_height(int focal_len, double dist);
t_ray				update_ray(t_ray *r, double dist, bool is_horiz);

// game logic
void				set_game_state(t_data *data);
bool				enemy_obstructed(t_data *data, int i, double distance);
void				attack(t_data *data, int i);
void				draw_gameover(t_data *data);

#endif
