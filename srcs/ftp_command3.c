/*
** ftp_command3.c for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Wed May 11 00:24:51 2016 Tony
** Last update Sun May 15 22:36:47 2016 Tony
*/

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "myftp.h"
#include "error.h"
#include "server.h"
#include "ftp_command.h"

int		ftp_pasv(t_server *srv, t_client *clt, char *cmd)
{
  (void)cmd;
  if (clt->_log != LOGGED)
    return (my_write(srv->_clt, RFC_530));
  if (init_pasv(srv, clt) == FAILURE)
    return (my_write(srv->_clt, RFC_421));
  dprintf(srv->_clt, "227 Entering Passive Mode (%s,%d,%d)\r\n",
	 srv->_ip, srv->_pata / 256, srv->_pata % 256);
  return (SUCCESS);
}

int		ftp_port(t_server *srv, t_client *clt, char *cmd)
{
  (void)cmd;
  if (clt->_log != LOGGED)
    return (my_write(srv->_clt, RFC_530));
  if (param(cmd) == '\0')
    return (my_write(srv->_clt, RFC_501));
  return (my_write(srv->_clt, RFC_220));
}

int		ftp_retr(t_server *srv, t_client *clt, char *cmd)
{
  if (clt->_log != LOGGED)
    return (my_write(srv->_clt, RFC_530));
  if (clt->_mode == UNDEFINED)
    return (my_write(srv->_clt, RFC_425));
  if (clt->_mode == PASV)
    {
      if (param(cmd) == '\0')
	return (my_write(srv->_clt, RFC_550));
      return (retr_pasv(srv, clt, cmd));
    }
  return (SUCCESS);
}

int		ftp_stor(t_server *srv, t_client *clt, char *cmd)
{
  (void)cmd;
  if (clt->_log != LOGGED)
    return (my_write(srv->_clt, RFC_530));
  if (param(cmd) == '\0')
    return (my_write(srv->_clt, RFC_550));
  if (clt->_mode == PASV)
    {
      if (param(cmd) == '\0')
	return (my_write(srv->_clt, RFC_550));
      return (stor_pasv(srv, clt, cmd));
    }
  return (SUCCESS);
}

int		ftp_dele(t_server *srv, t_client *clt, char *cmd)
{
  char		path[DEFAULT];

  if (clt->_log != LOGGED)
    return (my_write(srv->_clt, RFC_530));
  if (param(cmd) == '\0')
    return (my_write(srv->_clt, RFC_550));
  current(srv->_root, clt->_path, param(cmd), path);
  if (access(path, F_OK) != -1)
    {
      if (remove(path) == -1)
	return (my_write(srv->_clt, RFC_550));
      return (my_write(srv->_clt, RFC_250));
    }
  return (my_write(srv->_clt, RFC_550));
}
