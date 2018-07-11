/*
** utils.c for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Tue May 10 19:28:01 2016 Tony
** Last update Sun May 15 18:18:59 2016 Tony
*/

#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "myftp.h"
#include "error.h"

void	current(char *root, char *current, char *path, char *cmd)
{
  strcpy(cmd, root);
  if (path[0] != '/')
    strcat(cmd, current);
  strcat(cmd, "/");
  strcat(cmd, path);
}

int		valid_fld(char *root, char *path, char *cmd, char *fcmd)
{
  char          rpath[DEFAULT];
  DIR           *dir;

  current(root, path, cmd, fcmd);
  if ((dir = opendir(fcmd)) == NULL)
    return (FAILURE);
  closedir(dir);
  realpath(fcmd, rpath);
  if (strstr(rpath, root) == NULL)
    return (FAILURE);
  strcpy(fcmd, rpath);
  return (SUCCESS);
}

int             valid_cmd(char *root, char *path, char *cmd, char *fcmd)
{
  char          rpath[DEFAULT];
  DIR           *dir;

  strcpy(fcmd, root);
  if (cmd[0] != '/')
    strcat(fcmd, path);
  if (cmd[0] == '\0')
    return (SUCCESS);
  strcat(fcmd, cmd);
  strcat(fcmd, "/");
  if ((dir = opendir(fcmd)) == NULL)
    return (FAILURE);
  closedir(dir);
  realpath(fcmd, rpath);
  if (strstr(rpath, root) == NULL)
    return (FAILURE);
  return (SUCCESS);
}
