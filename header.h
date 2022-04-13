#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

struct s_client_info
{
	int		liked_ingredients_nb;
	int		desliked_ingredients_nb;
	char	**liked_ingredients;
	char	**disliked_ingredients;
} typedef t_client_info;

typedef struct	slst_ingredient_info
{
	char	*name;
	int		score;
	struct	slst_ingredient_info *next;
} tlst_ingredient_info;

//void				lst_swap(tlst_ingredient_info *a, tlst_ingredient_info *b);
void				lstadd_back(tlst_ingredient_info **lst, tlst_ingredient_info *new);
void				lstadd_front(tlst_ingredient_info **lst, tlst_ingredient_info *new);
tlst_ingredient_info	*lstlast(tlst_ingredient_info *stack);
void				ft_lstclear(tlst_ingredient_info **lst);

#endif