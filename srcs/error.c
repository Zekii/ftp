/*
** error.c for  in /home/truong_g/rendu/PSU_2015_myftp/srcs
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Mon May  2 17:48:59 2016 Tony
** Last update Wed May 11 14:37:05 2016 Tony
*/

#include <stdio.h>
#include <stdlib.h>
#include "myftp.h"
#include "error.h"

int		error_handler(char *err)
{
  fprintf(stderr, "%s\n", err);
  return (FAILURE);
}

int		perror_handler(char *err)
{
  perror(err);
  return (FAILURE);
}

int		close_server(t_server *serv, char *err)
{
  if (serv->_clt != 0)
    if (close(serv->_clt) == -1)
      return (perror_handler(ERR_CLOSE));
  if (close(serv->_srv) == -1)
    return (perror_handler(ERR_CLOSE));
  return (error_handler(err));
}

int		check_usage(int ac, char **av)
{
  if (ac != 3)
    return (error_handler(ERR_USAGE));
  if (atoi(av[1]) <= PORT_MIN || atoi(av[1]) > PORT_MAX)
    return (error_handler(ERR_PORT));
  return (SUCCESS);
}
