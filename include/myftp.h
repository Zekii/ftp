/*
** myftp.h for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Mon May  2 17:27:40 2016 Tony
** Last update Sun May 15 19:56:02 2016 Tony
*/

#ifndef MYFTP_H_
# define MYFTP_H_

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netdb.h>

# define READ_SIZE (1024)
# define PATH_SIZE (512)
# define DEFAULT (256)

# define RFC_150 "150 Data ready.\r\n"
# define RFC_200 "200 Okay.\r\n"
# define RFC_214 "214 Help.\r\n"
# define RFC_220 "220 Howdy.\r\n"
# define RFC_221 "221 Disconnected.\r\n"
# define RFC_226 "226 Transfer complete.\r\n"
# define RFC_227 "227 Ready.\r\n"
# define RFC_230 "230 Logged in.\r\n"
# define RFC_250 "250 Change Directory.\r\n"
# define RFC_257 "257 PWD.\r\n"
# define RFC_331 "331 Need Password.\r\n"
# define RFC_332 "332 Need ID.\r\n"
# define RFC_421 "421 Problem.\r\n"
# define RFC_425 "425 Define a mode.\r\n"
# define RFC_500 "500 Syntax error.\r\n"
# define RFC_501 "501 Syntax error.\r\n"
# define RFC_503 "503 Bad sequence.\r\n"
# define RFC_530 "530 You are doing something wrong..\r\n"
# define RFC_550 "550 Failed.\r\n"

# define ACC_ID "Anonymous"
# define ACC_PW ""

# define FTP_QUIT "Closing the server"

typedef enum	e_tmode
  {
    UNDEFINED = 0,
    PASV,
    PORT
  }		t_tmode;

typedef enum	e_log
  {
    N_LOG = 0,
    A_LOG,
    LOGGED
  }		t_log;

typedef struct		s_server
{
  struct sockaddr_in	_socket;
  char			_root[PATH_SIZE];
  char			_ip[DEFAULT];
  int			_srv;
  int			_clt;
  int			_data;
  int			_pata;
}			t_server;

typedef struct		s_client
{
  char			_user[DEFAULT];
  char			_pass[DEFAULT];
  char			_path[PATH_SIZE];
  char			_ip[DEFAULT];
  int			_port;
  t_log			_log;
  t_tmode		_mode;
}			t_client;

typedef int	(*f_cmd)(t_server *, t_client *, char *);

typedef struct		s_cmd
{
  char			*name;
  f_cmd		        cmd;
}			t_cmd;

extern t_cmd	g_cmd[];

int		server(t_server *, int, char *);

#endif /* !MYFTP_H_ */
