/*
** assign_client.c for  in /home/truong_g/rendu/PSU_2015_myftp/srcs
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Wed May  4 23:17:03 2016 Tony
** Last update Sun May 15 18:20:51 2016 Tony
*/

#include <string.h>
#include <strings.h>
#include "myftp.h"
#include "server.h"
#include "ftp_command.h"
#include "error.h"

int		init_client(t_server *srv, t_client *clt)
{
  clt->_log = N_LOG;
  clt->_mode = UNDEFINED;
  bzero(clt->_user, sizeof(clt->_user));
  bzero(clt->_pass, sizeof(clt->_pass));
  strcpy(clt->_path, "/");
  my_write(srv->_clt, RFC_220);
  return (SUCCESS);
}

int		process_cmd(t_server *srv, t_client *clt, char *cmd)
{
  int		i;

  i = 0;
  while (strcmp(g_cmd[i].name, "") != 0 &&
	 compare(g_cmd[i].name, cmd) != SUCCESS)
    ++i;
  if (strcmp(g_cmd[i].name, "") != 0)
    return (g_cmd[i].cmd(srv, clt, cmd));
  return (my_write(srv->_clt, RFC_500));
}

int		assign_client(t_server *srv)
{
  t_client	clt;
  char	        *request;

  init_client(srv, &clt);
  while (1)
    {
      if ((request = my_read(srv->_clt)) == NULL)
	{
	  printf("Close client\n");
	  return (close(srv->_clt));
	}
      assemble(request);
      if (process_cmd(srv, &clt, request) == FAILURE)
	return (SUCCESS);
      free(request);
      sleep(1);
    }
  return (SUCCESS);
}
