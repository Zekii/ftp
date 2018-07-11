/*
** main.c for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Mon May  2 17:26:40 2016 Tony
** Last update Sun May 15 23:36:46 2016 Tony
*/

#include <signal.h>
#include "myftp.h"
#include "error.h"

t_server	g_serv;

void		signal_handler(int signal)
{
  if (g_serv._clt != 0)
    close(g_serv._clt);
  if (g_serv._data != 0)
    close(g_serv._data);
  close(g_serv._srv);
  exit(signal);
}

int		main(int ac, char **av)
{
  signal(SIGINT, signal_handler);
  if (check_usage(ac, av) == FAILURE)
    return (FAILURE);
  if (server(&g_serv, atoi(av[1]), av[2]) == FAILURE)
    return (FAILURE);
  return (0);
}
