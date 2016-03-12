int		ft_column_count(char *str)
{
	int		ret;
	int		i;
	int		j;

	ret = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (ft_isdigit(str[i + j]))
			j++;
		if (j)
			ret++;
		i += j;
		while (str[i] && !ft_isdigit(str[i]))
			i++;
	}
	return (ret);
}

void	ft_isnum_or_space(char *line, int fd)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && (line[i] < '0' || line[i] > '9'))
		{
			close(fd);
			ft_strdel(&line);
			ft_putendl_fd("WRONG MAP {trailing characters on the map}!", 2);
			exit(0);
		}
		i++;
	}
}

int		ft_check_line(char *map, int fd, t_data data)
{
	if (data->nb_col == -1)
		data->nb_col = ft_column_count(map);
	else if (data->nb_col != ft_column_count(map))
	{
		close(fd);
		free(map);
		printf("%d\t%d", i , ft_column_count(map));
		ft_putendl_fd("WRONG MAP {map is not a square}!", 2);
		exit(0);
	}
	return (i);

}