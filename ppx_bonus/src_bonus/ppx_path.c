#include "../pipex.h"

int path_finder(char **map)
{
	int i; 
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		if(map[i][j])
		{
			if(map[i][j] == 'P' && map[i][j + 1] == 'A' && map[i][j + 2] == 'T' && map[i][j + 3] == 'H')
				return(i);
			else
				j++;
		}
		i++;
	}
    return(0);
}

char *make_path(char *split_path, char *cmd)
{
	int i;
	int j;
	char *path;

	i = 0; 
	path = malloc(ft_strlen(split_path) + ft_strlen(cmd + 1) + 1 * sizeof(char));
	if(!path)
		return(NULL);
	while(split_path[i])
	{
		path[i] = split_path[i];
		i++;
	}
	path[i] = '/';
	i++;
	j = 0; 
	while(cmd[j] && cmd[j] != ' ')
	{
		path[i] = cmd[j];
		i++;
		j++;
	}
	path[i] = '\0';
	return(path);
}

char *locate_path(char **split_path, char *cmd)
{
	int i; 
	int flag_acss; 
	char *path; 

	i = 0;
	while(split_path[i])
	{
		path = make_path(split_path[i], cmd);
		flag_acss = access(path, O_RDONLY);
		if(flag_acss == 0)
			return(path);
		else
		{
			//free(path);
			i++;
		}
	}
    flag_acss = access(cmd, O_RDONLY);
    if(flag_acss == 0)
        return(cmd);

    return(NULL);
}

