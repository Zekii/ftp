/*
** ftp_tcommand.c for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Sun May 15 03:02:09 2016 Tony
** Last update Sun May 15 23:21:33 2016 Tony
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "myftp.h"
#include "server.h"
#include "error.h"

int		list_pasv(t_server *srv, t_client *clt, char *cmd)
{
  char		fcmd[PATH_SIZE];
  char	        sys[PATH_SIZE];
  int		fd;
  int	        cfd;

  if ((cfd = accept_data(srv)) == FAILURE)
    return (FAILURE);
  my_write(srv->_clt, RFC_150);
  if (valid_cmd(srv->_root, clt->_path, param(cmd), fcmd) == FAILURE)
    return (my_write(srv->_clt, RFC_226));
  strcpy(sys, "ls -l ");
  strcat(sys, fcmd);
  if ((fd = dup(1)) == -1)
    return (FAILURE);
  dup2(cfd, 1);
  system(sys);
  dup2(fd, 1);
  my_write(srv->_clt, RFC_226);
  return (close_data(srv, clt, cfd));
}

int		retr_pasv(t_server *srv, t_client *clt, char *cmd)
{
  char	        path[DEFAULT];
  char	        *line;
  int		fd;
  int	        cfd;

  current(srv->_root, clt->_path, param(cmd), path);
  if (access(path, F_OK) != -1)
    {
      if ((cfd = accept_data(srv)) == FAILURE)
	return (FAILURE);
      my_write(srv->_clt, RFC_150);
      if ((fd = open(path, O_CREAT | O_RDWR)) == -1)
	return (my_write(srv->_clt, RFC_550));
      while ((line = my_read(fd)) != NULL)
	dprintf(cfd, "%s\n", line);
      close(fd);
      my_write(srv->_clt, RFC_226);
      return (close_data(srv, clt, cfd));
    }
  return (my_write(srv->_clt, RFC_550));
}

int	        stor_pasv(t_server *srv, t_client *clt, char *cmd)
{
  char	        buffer[DEFAULT];
  int	        cfd;
  int		fd;
  int	        len;

  if ((cfd = accept_data(srv)) == FAILURE)
    return (FAILURE);
  my_write(srv->_clt, RFC_150);
  if ((fd = creat(param(cmd), S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
    return (my_write(srv->_clt, RFC_550));
  while ((len = read(cfd, buffer, DEFAULT)) > 0)
    write(fd, buffer, len);
  close(fd);
  my_write(srv->_clt, RFC_226);
  return (close_data(srv, clt, cfd));
}
