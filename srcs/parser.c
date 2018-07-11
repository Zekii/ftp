/*
** parser.c for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Fri May  6 23:25:43 2016 Tony
** Last update Sun May 15 23:22:51 2016 Tony
*/

#include "myftp.h"
#include "error.h"

void	serialize(char *path)
{
  int	i;

  i = 0;
  while (path[i] != '\0')
    ++i;
  path[i] = '\r';
  path[i + 1] = '\n';
  path[i + 2] = '\0';
}

void	assemble(char *path)
{
  int	i;

  i = 0;
  while (path[i] != '\r' && path[i] != '\0')
    ++i;
  path[i] = '\0';
}

int	compare(char *cmd, char *request)
{
  int	i;

  i = 0;
  while (cmd[i] != '\0')
    {
      if (cmd[i] != request[i])
	return (FAILURE);
      ++i;
    }
  if (request[i] == ' ' || request[i] == '\0')
    return (SUCCESS);
  return (FAILURE);
}

char	*param(char *request)
{
  int	i;

  i = 0;
  while (request[i] != '\0' && request[i] != ' ')
    ++i;
  if (request[i] == ' ')
    ++i;
  return (request + i);
}

void		adapt(char *pasv)
{
  int		i;

  i = 0;
  while (pasv[i] != '\0')
    {
      if (pasv[i] == '.')
	pasv[i] = ',';
      ++i;
    }
}
