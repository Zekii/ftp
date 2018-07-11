/*
** command.c for  in /home/truong_g/rendu/PSU_2015_myftp/srcs
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Fri May  6 16:58:03 2016 Tony
** Last update Wed May 11 20:01:52 2016 Tony
*/

#include "myftp.h"
#include "ftp_command.h"

t_cmd	g_cmd[] = {
  {"USER", &ftp_user},
  {"PASS", &ftp_pass},
  {"PWD", &ftp_pwd},
  {"CWD", &ftp_cwd},
  {"CDUP", &ftp_cdup},
  {"LIST", &ftp_list},
  {"PASV", &ftp_pasv},
  {"PORT", &ftp_port},
  {"RETR", &ftp_retr},
  {"STOR", &ftp_stor},
  {"DELE", &ftp_dele},
  {"NOOP", &ftp_noop},
  {"QUIT", &ftp_quit},
  {"HELP", &ftp_help},
  {"", NULL}
};
