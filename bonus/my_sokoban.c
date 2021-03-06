/*
** my_sokoban.c for my_sokoban in /home/rectoria/delivery/Projets/Projet_my_sokoban
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Mon Dec 12 10:10:22 2016 Bastien
** Last update Tue Dec 20 17:33:47 2016 Bastien
*/

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sokoban.h"

void	find_player(char **tmap, t_player *player)
{
  int	i;
  int	j;

  i = -1;
  while (tmap[++i] != NULL)
    {
      j = -1;
      while (tmap[i][++j] != '\0')
	if (tmap[i][j] == 'P')
	  {
	    player->y = i;
	    player->x = j;
	    return ;
	  }
    }
}

void	get_winfo(t_tab *tmap, t_winfo *winfo)
{
  const struct winsize element;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &element);
  winfo->y = (element.ws_row) / 2 - tmap->height / 2;
  winfo->x = (element.ws_col) / 2 - tmap->width / 2;
}

void	init_ncurses()
{
  initscr();
  noecho();
  curs_set(0);
  timeout(200);
  keypad(stdscr, TRUE);
}

void		sokoban(t_tab *tmap, t_player *player, t_game *ginfo)
{
  int		ch;

  init_ncurses();
  menu1(tmap, player, ginfo);
  while (check_status(tmap, player) == 0)
    {
      display(tmap, tmap->tmap, ginfo);
      ch = getch();
      if (ch == ' ')
	{
	  my_reset(tmap->tmap, tmap->save, player);
	  init_ginfo(ginfo);
	}
      else if (ch == KEY_UP)
	move_up(tmap, tmap->tmap, player, ginfo);
      else if (ch == KEY_DOWN)
	move_down(tmap, tmap->tmap, player, ginfo);
      else if (ch == KEY_LEFT)
	move_left(tmap, tmap->tmap, player, ginfo);
      else if (ch == KEY_RIGHT)
	move_right(tmap, tmap->tmap, player, ginfo);
      else if (ch == 'p')
	menu2(tmap, player, ginfo);
    }
}

int		main(int ac, char **av)
{
  t_tab		*tmap;
  t_player	*player;
  int		fd;
  char		c;
  t_game	ginfo;

  c = '0';
  if (ac != 2)
    return (84);
  if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0')
    usage();
  if ((fd = open(av[1], O_RDONLY)) == -1)
    return (84);
  while (read(fd, &c, 1) != 0)
    isamap(c);
  if ((player = malloc(sizeof(t_player))) == NULL)
    return (84);
  tmap = str_to_t_tab(av[1]);
  find_player(tmap->tmap, player);
  check_arg(tmap, player);
  init_ginfo(&ginfo);
  sokoban(tmap, player, &ginfo);
  return (0);
}
