/*
** ftp_command.h for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Fri May  6 17:16:55 2016 Tony
** Last update Sun May 15 22:57:14 2016 Tony
*/

#ifndef FTP_COMMAND_H_
# define FTP_COMMAND_H_

int	ftp_user(t_server *, t_client *, char *);
int	ftp_pass(t_server *, t_client *, char *);
int	ftp_noop(t_server *, t_client *, char *);
int	ftp_help(t_server *, t_client *, char *);
int	ftp_quit(t_server *, t_client *, char *);
int	ftp_pwd(t_server *, t_client *, char *);
int	ftp_cwd(t_server *, t_client *, char *);
int	ftp_cdup(t_server *, t_client *, char *);
int	ftp_list(t_server *, t_client *, char *);
int	ftp_pasv(t_server *, t_client *, char *);
int	ftp_port(t_server *, t_client *, char *);
int	ftp_retr(t_server *, t_client *, char *);
int	ftp_stor(t_server *, t_client *, char *);
int	ftp_dele(t_server *, t_client *, char *);
int	list_pasv(t_server *, t_client *, char *);
int	retr_pasv(t_server *, t_client *, char *);
int     stor_pasv(t_server *, t_client *, char *);

#endif /* !FTP_COMMAND_H_ */
