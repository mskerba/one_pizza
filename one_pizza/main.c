#include "header.h"
int clients_nb;

char *get_line(int fd)
{
	int i;
	int len;
	char *temp;
	char *line;
	char buffer;

	line = NULL;
	buffer = 0;
	while (buffer != '\n' && read(fd, &buffer, 1) > 0)
	{
		i = -1;
		len = 0;
		temp = line;
		if (line)
			while (line[len])
				len++;
		line = malloc(len + 2);
		while (++i < len)
			line[i] = temp[i];
		line[i++] = buffer;
		line[i] = 0;
		if (line)
			free(temp);
	}
	return (line);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;

    printf("%s",s1);
	printf("%s",s2);
	if (!s1 || !s2)
		return (0);
	i = strlen(s1);
	j = strlen(s2);
	dst = (char *)malloc(sizeof(char) * (j + i + 1));
	if (!dst)
		return (0);
	strcpy(dst, s1);
	strcat(dst, s2);
	return (dst);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if(s[i] != '\n')
		   write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	long int	i;

	i = nb;
	if (i < 0)
	{
		ft_putstr_fd("-", fd);
		i = -i;
	}
	if (i > 9)
	{
		ft_putnbr_fd(i / 10, fd);
	}
	ft_putchar_fd(i % 10 + '0', fd);
}

void	*end_output(tlst_ingredient_info **head, int *i)
{
	tlst_ingredient_info *ptr;

	ptr = *head;
	// printf("(%d)",ptr);
	while(ptr)
	{
		if(ptr->score == 0)
			ptr = NULL;
		ptr = ptr->next;
		i++;
	}
}

void	*sort(tlst_ingredient_info **head)
{
	tlst_ingredient_info	*list1;
	tlst_ingredient_info	*list2;
	int			score;
	char			*name;

	list1 = *head;
	while (list1)
	{
		list2 = list1->next;
		while (list2)
		{
			if (list1->score < list2->score)
			{
				score = list1->score;
				name = list1->name;
				list1->score = list2->score;
				list1->name = list2->name;
				list2->score = score;
				list2->name = name;
			}
			list2 = list2->next;
		}
		list1 = list1->next;
	}
}

void	update_ingerdient_info(tlst_ingredient_info **ingredients_info_lst,char *name, int inc)
{
	// printf("name is: %s\n", name);
	int					ist_in;
	tlst_ingredient_info *tmp;

	tmp = *ingredients_info_lst;
	ist_in = 0;
	while(tmp)
	{
		if (strstr(tmp->name, name) != NULL)
		{
			ist_in = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!ist_in)
	{
		tmp = malloc(sizeof(tlst_ingredient_info));
		tmp->name = name;
		tmp->score = inc;
		lstadd_back(ingredients_info_lst, tmp);
	}
	else
		tmp->score += inc;
}

void get_clients_info(t_client_info **clients_info_arr, tlst_ingredient_info **ingredients_info_lst, int fd)
{
	char *line;
	int ingredients_nb;
	int i = -1;
	int j;

	while (++i < clients_nb)
	{
		clients_info_arr[i] = malloc(sizeof(t_client_info));
		line = get_line(fd);
		ingredients_nb = atoi(strtok(line, " \n"));
		line += (strlen(strtok(line, " \n")) + 1);
		// liked ingredients
		clients_info_arr[i]->liked_ingredients_nb = ingredients_nb;
		clients_info_arr[i]->liked_ingredients = malloc(ingredients_nb * sizeof(char *));
		j = -1;
		while (++j < ingredients_nb)
		{
			update_ingerdient_info(ingredients_info_lst, strtok(line, " \n"), 1);
			clients_info_arr[i]->liked_ingredients[j] = strtok(line, " \n");
			line += (strlen(clients_info_arr[i]->liked_ingredients[j]) + 1);
		}
		// disliked ingredients
		line = get_line(fd);
		ingredients_nb = atoi(strtok(line, " \n"));
		line += (strlen(strtok(line, " \n")) + 1);
		clients_info_arr[i]->disliked_ingredients = malloc((ingredients_nb + 1) * sizeof(char *));
		clients_info_arr[i]->desliked_ingredients_nb = ingredients_nb;
		j = -1;
		while (++j < ingredients_nb)
		{
			update_ingerdient_info(ingredients_info_lst, strtok(line, " \n"), -1);
			clients_info_arr[i]->disliked_ingredients[j] = strtok(line, " \n");
			line += (strlen(clients_info_arr[i]->disliked_ingredients[j]) + 1);
		}
	}
}

int main()
{
	t_client_info **clients_info_arr;
	tlst_ingredient_info *ingredients_info_lst = NULL;
	int fd = open("e_elaborate.in.txt", O_RDONLY);
	int	fd_2 = open("j.txt",O_WRONLY);
	// int fd = open("b.txt", O_RDONLY);
	// int	fd_2 = open("outputb.txt",O_WRONLY);
	int nb_ingredients = 0;
	char *dst = NULL;

	clients_nb = atoi(get_line(fd));
	clients_info_arr = malloc(sizeof(t_client_info *) * clients_nb);
	get_clients_info(clients_info_arr, &ingredients_info_lst,fd);
	sort(&ingredients_info_lst);
	// end_output(&ingredients_info_lst,&nb_ingredients);
	
	{
		// int i = -1;
	// int j;
	// while (++i < clients_nb)
	// {
	// 	printf("Client ID %i\n", i);
	// 	printf("	liked_ingredients_nb: %i\n", clients_info_arr[i]->liked_ingredients_nb);
	// 	j = -1;
	// 	while (++j < clients_info_arr[i]->liked_ingredients_nb)
	// 	{
	// 		printf("	liked_ingredients: %s\n", clients_info_arr[i]->liked_ingredients[j]);
	// 	}
	// 	printf("	desliked_ingredients_nb: %i\n", clients_info_arr[i]->desliked_ingredients_nb);
	// 	j = -1;
	// 	while (++j < clients_info_arr[i]->desliked_ingredients_nb)
	// 		printf("	disliked_ingredients: %s\n", clients_info_arr[i]->disliked_ingredients[j]);
	// }
	}
	tlst_ingredient_info *tmp;

	tmp = ingredients_info_lst;
	while (tmp->score > 0)
	{
		nb_ingredients++;
		tmp = tmp->next;
	}
// printf("%d",nb_ingredients);
	ft_putnbr_fd(nb_ingredients,fd_2);
	ft_putchar_fd(' ',fd_2);
	tmp = ingredients_info_lst;
	while (tmp->score > 0)
	{
		// printf("name:%s", tmp->name);
		// printf("score %d",tmp->score);
		ft_putstr_fd(tmp->name,fd_2);
		ft_putchar_fd(' ',fd_2);
		tmp = tmp->next;
	}
	// dst = strdup("");
	// printf("%s\n",dst);
	// while (tmp->score > 0)
	// {
	// 	// printf("|||||||%s\n",tmp->name);
	// 	printf("else :%s\n",tmp->name);
	// 	dst = ft_strjoin(dst,tmp->name);
	// 	// dst = ft_strjoin(dst," ");
	// 	printf("%s\n",dst);
	// 	nb_ingredients++;
	// 	tmp = tmp->next;
	// 		//  printf("{%s}\n",dst);
	// }
	// printf("%s\n",dst);
	// while (tmp->score > 0)
	// {
	// 	ft_putchar_fd(' ',fd_2);
	// 	ft_putstr_fd(tmp->name,fd_2);
	// 	tmp = tmp->next;
	// }
	close(fd);
}