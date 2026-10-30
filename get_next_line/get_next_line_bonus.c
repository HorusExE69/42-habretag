#include "get_next_line_bonus.h"

static int	check_stash(char *stash)
{
	unsigned int	i;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buf;
	int		n;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	n = 1;
	if (!buf)
		n = -1;
	while (n > 0 && !check_stash(stash))
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n > 0)
		{
			buf[n] = '\0';
			stash = ft_strjoin(stash, buf);
			if (!stash)
				n = -1;
		}
	}
	free(buf);
	if (n == -1)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

static char	*stash_to_line(char *stash)
{
	char			*line;
	unsigned int	i;

	i = 0;
	line = malloc(sizeof(char) * (line_length(stash) + 1));
	if (!line)
		return (NULL);
	while (*stash != '\n' && *stash != '\0')
	{
		line[i] = *stash;
		i++;
		stash++;
	}
	if (*stash == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*stash_to_rest(char *stash)
{
	char			*rest;
	unsigned int	start;
	unsigned int	i;

	if (rest_length(stash) == 0)
		return (NULL);
	rest = malloc(sizeof(char) * (rest_length(stash) + 1));
	if (!rest)
		return (NULL);
	start = line_length(stash);
	i = 0;
	while (stash[start + i])
	{
		rest[i] = stash[start + i];
		i++;
	}
	rest[i] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*line;
	char		*rest;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = stash_to_line(stash[fd]);
	rest = stash_to_rest(stash[fd]);
	if (!line || (!rest && rest_length(stash[fd]) > 0))
	{
		free(line);
		free(rest);
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	free(stash[fd]);
	stash[fd] = rest;
	return (line);
}
