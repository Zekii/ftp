/*
** ftp_connect.c for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Fri May  6 17:07:47 2016 Tony
** Last update Wed May 11 17:51:25 2016 Tony
*/

#include <string.h>
#include "myftp.h"
#include "error.h"
#include "server.h"

int		ftp_user(t_server *srv, t_client *clt, char *cmd)
{
  if (clt->_log != N_LOG)
    return (my_write(srv->_clt, RFC_530));
  strcpy(clt->_user, param(cmd));
  clt->_log = A_LOG;
  return (my_write(srv->_clt, RFC_331));
}

int		ftp_pass(t_server *srv, t_client *clt, char *cmd)
{
  if (clt->_log == N_LOG)
    return (my_write(srv->_clt, RFC_503));
  if (clt->_log == LOGGED)
    return (my_write(srv->_clt, RFC_230));
  strcpy(clt->_pass, param(cmd));
  if (strcmp(clt->_pass, ACC_PW) == 0 && strcmp(clt->_user, ACC_ID) == 0)
    {
      clt->_log = LOGGED;
      return (my_write(srv->_clt, RFC_230));
    }
  clt->_log = N_LOG;
  return (my_write(srv->_clt, RFC_530));
}

int		ftp_noop(t_server *srv, t_client *clt, char *cmd)
{
  (void)cmd;
  if (clt->_log != LOGGED)
    return (my_write(srv->_clt, RFC_530));
  return (my_write(srv->_clt, RFC_200));
}

int		ftp_quit(t_server *srv, t_client *clt, char *cmd)
{
  (void)cmd;
  (void)clt;
  my_write(srv->_clt, RFC_221);
  return (FAILURE);
}

int		ftp_help(t_server *srv, t_client *clt, char *cmd)
{
  (void)cmd;
  if (clt->_log != LOGGED)
    return (my_write(srv->_clt, RFC_530));
  return (my_write(srv->_clt, RFC_214));
}
