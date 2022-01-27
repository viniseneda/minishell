#include "minishell.h"

unsigned long get_hash(char *str)
{
	unsigned long hash;
	int c;

	hash = 5381;
	while (*str)
	{
		c = *str;
		str++;
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash;
}

t_node	**create_dict(void)
{
	t_node **dict;
	int i;

	i = 0;
	dict = malloc(sizeof(t_node *) * DICT_ARRAY_SIZE);
	if (dict == NULL)
		exit (100);
	while (i < DICT_ARRAY_SIZE)
	{
		// *dict++ = NULL;
		dict[i] = NULL;
		i++;
	}
	return (dict);
}

int		print_tuple_list(t_node *node)
{
	int	size;

	size = 0;
	while (node != NULL)
	{
		printf("(%s, %s) ", (char *)node->key, (char *)node->data);
		node = node->next;
		size++;
	}
	return (size);
}

void	free_tuple_list(t_node *node)
{
	t_node	*last;

	while (node != NULL)
	{
		last = node;
		node = node->next;
		free(last->data);
		free(last->key);
		free(last);
	}
}

void	add_dict_value(t_node **dict, char *key, char *value)
{
	unsigned long hash;
	t_node *node;

	if (key == NULL || value == NULL)
		return ;
	node = malloc(sizeof(t_node));
	node->next = NULL;
	hash = get_hash(key) % DICT_ARRAY_SIZE;

	// printf("%ld, %p, %p, %p\n", hash, *(dict + hash), node, node->next);

	if (*(dict + hash) == NULL)
		*(dict + hash) = node;
	else
		get_last_node(*(dict + hash))->next = node;

	node->key = ft_strdup(key);
	node->data = ft_strdup(value);
	node->next = NULL;

	// dict[hash] = node;
	// node->next = NULL;
}

int	print_dict(t_node **dict)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (i < DICT_ARRAY_SIZE)
	{
		if (*(dict + i) != NULL)
		{
			size += print_tuple_list(*(dict + i));
		}
		i++;
	}
	printf("\n");
	return(size);
}

void	free_dict(t_node **dict)
{
	int i;

	i = 0;
	while (i < DICT_ARRAY_SIZE)
	{
		if (dict[i] != NULL)
			free_tuple_list(dict[i]);
		i++;
	}
	free(dict);
}

t_node *find_dict_node(t_node **dict, char *key)
{
	int	hash;
	int	i;

	i = 0;
	hash = get_hash(key) % DICT_ARRAY_SIZE;
	if (dict[hash] != NULL)
		while (dict[hash + i] != NULL)
		{
			if (ft_strncmp(dict[hash + i]->key, key, ft_strlen(key)) == 0)
				return (dict[hash + i]);
			i++;
		}
	return (NULL);
}

int		change_dict_value(t_node **dict, char *key, char *new_value)
{
	t_node	*node;

	node = find_dict_node(dict, key);
	if (node == NULL)
		return (0);
	free(node->data);
	node->data = ft_strdup(new_value);
	return(1);
}

// int	main(void)
// {
// 	t_node **dict;
// 	// char *search;

// 	dict = create_dict();
// 	// add_str_dict(dict, "name", "boo");
// 	add_dict_value(dict, "name", "nuoo");


// 	print_dict(dict);
// 	change_dict_value(dict, "name", "banana");
// 	print_dict(dict);
// 	free_dict(dict);
// }
