/*
** ftp_command2.c for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Sun May  8 12:38:42 2016 Tony
** Last update Sun May 15 22:19:29 2016 Tony
*/

#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "myftp.h"
#include "server.h"
#include "ftp_command.h"
#include "error.h"

int		ftp_pwd(t_server *srv, t_client *clt, char *cmd)
{
  char	        fcmd[PATH_SIZE];

  (void)cmd;
  if (clt->_log != LOGGED)
    return (my_write(srv->_clt, RFC_530));
  strcpy(fcmd, "257 \"");
  strcat(fcmd, clt->_path);
  strcat(fcmd, "\"");
  serialize(fcmd);
  return (my_write(srv->_clt, fcmd));
}

int		ftp_cwd(t_server *srv, t_client *clt, char *cmd)
{
  char	        fcmd[PATH_SIZE];

  if (clt->_log != LOGGED)
    return (my_write(srv->_clt, RFC_530));
  if (param(cmd) == '\0')
    return (my_write(srv->_clt, RFC_501));
  if (valid_fld(srv->_root, clt->_path, param(cmd), fcmd) == FAILURE)
    return (my_write(srv->_clt, RFC_501));
  strcpy(clt->_path, &(fcmd[strlen(srv->_root)]));
  if (clt->_path[0] == '\0')
    strcpy(clt->_path, "/");
  return (my_write(srv->_clt, RFC_250));
}

int		ftp_cdup(t_server *srv, t_client *clt, char *cmd)
{
  (void)cmd;
  if (clt->_log != LOGGED)
    return (my_write(srv->_clt, RFC_530));
  strcpy(clt->_path, "/");
  return (my_write(srv->_clt, RFC_200));
}

int		ftp_list(t_server *srv, t_client *clt, char *cmd)
{
  if (clt->_log != LOGGED)
    return (my_write(srv->_clt, RFC_530));
  if (clt->_mode == UNDEFINED)
    return (my_write(srv->_clt, RFC_425));
  if (clt->_mode == PASV)
    return (list_pasv(srv, clt, cmd));
  return (SUCCESS);
}
