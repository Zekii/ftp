/*
** utils.c for  in /home/truong_g/rendu/PSU_2015_myftp
**
** Made by Tony
** Login   <truong_g@epitech.net>
**
** Started on  Tue May 10 19:13:25 2016 Tony
** Last update Sun May 15 18:20:58 2016 Tony
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "myftp.h"
#include "server.h"
#include "error.h"

int		my_write(int fd, char *buffer)
{
  if (write(fd, buffer, strlen(buffer)) == -1)
    return (error_handler(ERR_WRITE));
  return (SUCCESS);
}

char	*my_reallocat(char *str1, char *str2)
{
  char	*tmp;
  int	len;
  int	i;
  int	j;

  i = 0;
  len = strlen(str1) + strlen(str2) + 1;
  if ((tmp = malloc(sizeof(char) * len)) == NULL)
    return (NULL);
  while (str1[i] != '\0')
    {
      tmp[i] = str1[i];
      i = i + 1;
    }
  j = i;
  i = 0;
  while (str2[i] != '\0')
    {
      tmp[j] = str2[i];
      j = j + 1;
      i = i + 1;
    }
  tmp[j] = '\0';
  free(str1);
  return (tmp);
}

char		*get_next_part(char *buff)
{
  char		*tmp;
  unsigned int	i;
  int		j;

  i = 0;
  j = 0;
  while (i < strlen(buff) && buff[i] != '\n')
    i = i + 1;
  if ((strlen(buff) - i) > 0)
    {
      if ((tmp = malloc(sizeof(char) * (strlen(buff) - i + 1))) == NULL)
	return (NULL);
      buff[i] = '\0';
      i = i + 1;
      while (buff[i] != '\0')
	{
	  tmp[j] = buff[i];
	  j = j + 1;
	  i = i + 1;
	}
      tmp[j] = '\0';
      return (tmp);
    }
  return (NULL);
}

char		*set_next_part(char *to_cat)
{
  char		*tmp;
  int		i;

  i = 0;
  if (to_cat != NULL)
    {
      if ((tmp = malloc(sizeof(char) * (strlen(to_cat) + 1))) == NULL)
	return (NULL);
      while (to_cat[i] != '\0')
	{
	  tmp[i] = to_cat[i];
	  i = i + 1;
	}
      tmp[i] = '\0';
      free(to_cat);
      return (tmp);
    }
  if ((tmp = malloc(sizeof(char) * 1)) == NULL)
    return (NULL);
  tmp[0] = '\0';
  return (tmp);
}

char		*my_read(const int fd)
{
  static char	*next = NULL;
  char		buff[READ_SIZE + 1];
  char		*line;
  int		len;

  line = set_next_part(next);
  if ((next = get_next_part(line)) != NULL)
    return (line);
  while ((len = read(fd, buff, READ_SIZE)) > 0)
    {
      buff[len] = '\0';
      line = my_reallocat(line, buff);
      if ((next = get_next_part(line)) != NULL)
	return (line);
    }
  free(line);
  return (NULL);
}
