/*
** error.h<PSU_2015_myftp> for  in /home/truong_g/rendu/PSU_2015_myftp/include
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Mon May  2 18:08:14 2016 Tony
** Last update Wed May 11 22:37:33 2016 Tony
*/

#ifndef ERROR_H_
# define ERROR_H_

# define SUCCESS (0)
# define FAILURE (-1)

# define PORT_MIN (1024)
# define PORT_MAX (65535)

# define ERR_USAGE "Usage: ./server PORT PATH"
# define ERR_PORT "Usage: PORT invalid"
# define ERR_PATH "Usage: PATH invalid"
# define ERR_SOCKET "socket failed"
# define ERR_PROTO "getprotobyname failed"
# define ERR_LISTEN "listen failed"
# define ERR_SETSOCK "setsockopt failed"
# define ERR_BIND "bind failed"
# define ERR_ACCEPT "accept failed"
# define ERR_READ "read failed"
# define ERR_WRITE "write failed"
# define ERR_CLOSE "close failed"
# define ERR_MALLOC "malloc failed"
# define ERR_FORK "fork failed"

int	error_handler(char *);
int	perror_handler(char *);
int     close_server(t_server *, char *);
int	check_usage(int, char **);

#endif /* !ERROR_H_ */
