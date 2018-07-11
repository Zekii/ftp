/*
** server.h for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Wed May  4 23:36:30 2016 Tony
** Last update Sun May 15 22:27:57 2016 Tony
*/

#ifndef SERVER_H_
# define SERVER_H_

char		*my_read(const int);
int		my_write(int, char *);
void		current(char *, char *, char *, char *);
void		serialize(char *);
void		assemble(char *);
void		adapt(char *);
int		valid_fld(char *, char *, char *, char *);
int		valid_cmd(char *, char *, char *, char *);
int	        compare(char *, char *);
char	        *param(char *);
void	        clean(char *);
int		assign_client(t_server *);
int		init_pasv(t_server *, t_client *);
int	        accept_data(t_server *);
int		close_data(t_server *, t_client *, int);

#endif /* !SERVER_H_ */
