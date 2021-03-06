/*
** fct_action.c for sokoban in /home/rectoria/delivery/Projets/Projet_my_sokoban
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Wed Dec 14 13:51:25 2016 Bastien
** Last update Mon Dec 19 12:49:38 2016 Bastien
*/

#include <curses.h>
#include <stdlib.h>
#include "sokoban.h"

void	victory(t_tab *tmap, t_player *player)
{
  int	i;
  int	j;

  i = -1;
  while (tmap->tmap[++i])
    {
      j = -1;
      while (tmap->tmap[i][++j])
	if (tmap->tmap[i][j] == 'X' && tmap->save[i][j] != 'O')
	  return ;
    }
  free_t_tab(tmap);
  free(player);
  clear();
  endwin();
  exit(0);
}

int	check_status(t_tab *tmap, t_player *player)
{
  victory(tmap, player);
  return (0);
}

void	check_hole(t_tab *tmap, t_player *player)
{
  if (tmap->save[player->y][player->x] == 'O')
    tmap->tmap[player->y][player->x] = 'O';
  else
    tmap->tmap[player->y][player->x] = ' ';
}

void	move_p(char **tmap, t_player *player, int newy, int newx)
{
  tmap[newy][newx] = 'P';
  tmap[player->y][player->x] = ' ';
}
