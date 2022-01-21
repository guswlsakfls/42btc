/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:57:05 by hyujo             #+#    #+#             */
/*   Updated: 2022/01/21 21:08:44 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_node
{
	int			data;
	struct node	*prev;
	struct node	*next;
}	t_node;

node	*ft_init(Node *ptr)
{
	if (ptr == NULL)
	{
		ptr = malloc(sizeof(Node));
		if (!ptr)
			return (NULL);
		ptr->data = 0;
		ptr->prev = NULL;
		ptr->next = NULL;
		return (ptr);
	}
}

void	ft_node_push(t_node node, int data)
{
	t_node	*new_node;

	new_node = malloc(sizeof(node));
	if (!node)
		return (NULL);
	new_node->data = data;
	new_node->next = node->prev;
	node->prev = NULL;
}

int	ft_node_pop(t_node node)
{
	t_node	*tmp;

	tmp = node;
	node->prev = tmp->next
	free(node)
	return (tmp->data);
}

int	main(int argc, char **argv)
{
	t_node	node;
	

	if (argv = )
	node = ft_init(node);
	return (0);
}
