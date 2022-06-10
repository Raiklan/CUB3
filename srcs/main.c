/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saich <saich@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:26:38 by saich             #+#    #+#             */
/*   Updated: 2022/05/30 20:51:38 by saich            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_error(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	return (1);
}

int	check_cub_ext(char **av)
{
	char	*str;

	str = ft_strrchr(av[1], '.');
	if (str == NULL)
		return (print_error("Not a .cub extension for configuration file\n"));
	str++;
	if (*str == 'c')
	{
		str++;
		if (*str == 'u')
		{
			str++;
			if (*str == 'b')
			{
				str++;
				if (*str == '\0')
					return (0);
			}
		}
	}
	return (print_error("Not a .cub extension for configuration file\n"));
}

int	check_cub_rights(char **av)
{
	int	fd;
	int	fd2;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_error("Couldn't open file\n"));
	close(fd);
	fd2 = open(av[1], __O_DIRECTORY);
	if (fd2 != -1)
	{
		close(fd2);
		return (print_error("file is a directory\n"));
	}
	return (0);
}

/* List of all the content of file and verification there isn't 
two instances of the same data*/
int	get_info(char **av, t_list **lst)
{
	int		fd;
	char	*ret;
	t_list	*elem;

	fd = open(av[1], O_RDONLY);
	ret = get_next_line(fd);
	while (ret != NULL)
	{
		elem = ft_lstnew(ret);
		if (!(elem))
			return (print_error(strerror(errno)));
		ft_lstadd_back(lst, elem);
		ret = get_next_line(fd);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_list	*lst;
	
	lst = NULL;
	if (ac != 2)
	{
		print_error("Not enough arguments: you must include a .cub file for \
configuration of the map !\n");
		return (EXIT_FAILURE);
	}
	if (check_cub_ext(av))
		return (EXIT_FAILURE);
	if (check_cub_rights(av))
		return (EXIT_FAILURE);
	if (get_info(av, &lst))
		return (EXIT_FAILURE);
	if (!check_content(&lst))
		return (EXIT_FAILURE);
	return (0);
}
