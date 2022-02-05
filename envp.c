#include "minishell.h"

char *get_key(char *str)
{
	char *key;
	temp_str(-1);
	while (*str != '=')
	{
		key = temp_str(*str);
		str++;
	}
	return (key);
}

char *get_value(char *str)
{
	char *key;
	while (*str != '=')
	{
		str++;
	}
	str++;
	return (str);
}

char *join_key_and_value(char *key, char *value)
{
	int size;
	char *out;

	size = ft_strlen(key) + ft_strlen(value) + 2;
	out = malloc(size * sizeof(char));
	ft_strlcpy(out, key, ft_strlen(key) + 1);
	ft_strlcat(out, "=", ft_strlen(key) + 2);
	ft_strlcat(out, value,  ft_strlen(key) + ft_strlen(value) + 2);
	return (out);
}

void	save_envp_to_dict(t_node **dict, char **envp)
{
	char	*line;

	while (*envp != NULL)
	{
		line = *envp;
		add_dict_value(dict, get_key(line), get_value(line));
		envp++;
	}
}

int		transfom_tuple_list(t_node *node, char **envp, int i)
{
	while (node != NULL)
	{
		envp[i] = join_key_and_value((char *)node->key, (char *)node->data);
		node = node->next;
		// printf("%s\n", envp[i]);
		i--;
	}
	return (i);
}

char **make_envp_from_dict(t_node **dict)
{
	char	**envp;
	int		size;
	int		i;

	i = 0;

	size = dict_size(dict);
	envp = malloc((size + 1) * sizeof(char *));
	envp[size] = NULL;
	size -= 1;


	while (i < DICT_ARRAY_SIZE)
	{
		size = transfom_tuple_list(dict[i], envp, size);
		i++;
	}

	return (envp);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	// char *line;

// 	// line = envp[3];
// 	// printf("%s\n", line);
// 	// printf("%s\n", get_key(line));
// 	// printf("%s\n", get_value(line));
// 	// printf("%s\n", join_key_and_value(get_key(line), get_value(line)));

// 	t_node	**dict;
// 	char **env2;
// 	char *s = "this $ a test string";
// 	t_node *node;

// 	dict = create_dict();
// 	save_envp_to_dict(dict, envp);
// 	s = replace_vars_in_str(dict, s);
// 	printf("%s\n", s);
// 	// node = find_dict_node(dict, "PATH");
// 	// node = find_dict_node(dict, "GDK_BACKEND");
// 	// printf("%s\n", (char *)node->data);



// 	// env2 = make_envp_from_dict(dict);
// 	// print_str_array(env2);
// 	// free_dict(dict);
// 	// free_str_array(env2);

// 	// print_dict(dict);
// }
