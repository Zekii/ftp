/*
** server.c for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Mon May  2 18:15:29 2016 Tony
** Last update Sun May 15 01:32:32 2016 Tony
*/

#include <string.h>
#include "myftp.h"
#include "server.h"
#include "error.h"

int			set_info(t_server *srv)
{
  struct hostent	*host;
  struct in_addr	**addr_list;

  bzero(srv->_ip, sizeof(srv->_ip));
  if (gethostname(srv->_ip, sizeof(srv->_ip)) == -1)
    return (FAILURE);
  if ((host = gethostbyname(srv->_ip)) == NULL)
    return (FAILURE);
  addr_list = (struct in_addr **)host->h_addr_list;
  strcpy(srv->_ip , inet_ntoa(*addr_list[0]));
  adapt(srv->_ip);
  return (SUCCESS);
}

int			init_server(t_server *srv, int port, char *path)
{
  struct protoent	*proto;
  int			enable;

  enable = 1;
  srv->_clt = 0;
  srv->_data = 0;
  realpath(path, srv->_root);
  if ((proto = getprotobyname("TCP")) == NULL)
    return (error_handler(ERR_PROTO));
  srv->_socket.sin_family = AF_INET;
  srv->_socket.sin_addr.s_addr = htonl(INADDR_ANY);
  srv->_socket.sin_port = htons(port);
  if ((srv->_srv = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    return (perror_handler(ERR_SOCKET));
  if (setsockopt(srv->_srv, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    return (perror_handler(ERR_SETSOCK));
  if (bind(srv->_srv, (struct sockaddr *)(&(srv->_socket)),
	   sizeof(srv->_socket)) == -1)
    return (perror_handler(ERR_BIND));
  if (listen(srv->_srv, SOMAXCONN) == -1)
    return (perror_handler(ERR_LISTEN));
  return (set_info(srv));
}

int		my_accept(t_server *srv)
{
  socklen_t	len;

  len = sizeof(srv->_socket);
  srv->_clt = 0;
  srv->_clt = accept(srv->_srv, (struct sockaddr *)&(srv->_socket), &len);
  if (srv->_clt == -1)
    return (close_server(srv, ERR_ACCEPT));
  return (SUCCESS);
}

int		process(t_server *srv)
{
  pid_t		pid;

  while (1)
    {
      if (my_accept(srv) == -1)
	return (FAILURE);
      if ((pid = fork()) == -1)
	return (close_server(srv, ERR_FORK));
      else if (pid > 0)
	close(srv->_clt);
      else
	return (assign_client(srv));
    }
  return (SUCCESS);
}

int		server(t_server *srv, int port, char *path)
{
  if (init_server(srv, port, path) == FAILURE)
    return (FAILURE);
  if (process(srv) == FAILURE)
    return (FAILURE);
  if (close(srv->_srv) == -1)
    return (error_handler(ERR_CLOSE));
  return (SUCCESS);
}
