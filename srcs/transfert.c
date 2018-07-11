/*
** transfert.c for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Wed May 11 15:12:19 2016 Tony
** Last update Sun May 15 22:27:45 2016 Tony
*/

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "myftp.h"
#include "server.h"
#include "error.h"

int			init_pasv(t_server *srv, t_client *clt)
{
  struct sockaddr_in	sock;
  struct protoent	*proto;
  socklen_t		len;

  close(srv->_data);
  proto = getprotobyname("TCP");
  if ((srv->_data = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    return (FAILURE);
  sock.sin_family = AF_INET;
  sock.sin_addr.s_addr = INADDR_ANY;
  sock.sin_port = 0;
  if (bind(srv->_data, (struct sockaddr *)&sock, sizeof(sock)) == -1)
    return (FAILURE);
  if (listen(srv->_data, 1) == -1)
    return (FAILURE);
  len = sizeof(sock);
  if (getsockname(srv->_data, (struct sockaddr *)&sock, &len) == -1)
    return (FAILURE);
  srv->_pata = ntohs(sock.sin_port);
  clt->_mode = PASV;
  return (SUCCESS);
}

int		close_data(t_server *srv, t_client *clt, int fd)
{
  if (close(fd) == -1)
    return (FAILURE);
  if (close(srv->_data) == -1)
    return (FAILURE);
  srv->_data = 0;
  clt->_mode = UNDEFINED;
  return (SUCCESS);
}

int			accept_data(t_server *srv)
{
  struct sockaddr_in	sock;
  socklen_t		len;
  int			fd;

  len = sizeof(sock);
  fd = accept(srv->_data, (struct sockaddr *)&sock, &len);
  return (fd);
}
