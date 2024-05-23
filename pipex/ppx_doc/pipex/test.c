#include "test.h"

int ft_strlen(char *str)
{
    int i = 0;
    
    while(str[i])
        i++;

    return(i);

}


int comparaison(char *s1, char *s2)
{
    int i = 0;
    

    while(s1[i] == s2[i])
        i++;
    if(i == ft_strlen(s1) - 1)
        return(1);
    else 
        return(0);
}


int main(void)
{
    char *line;
    char *cmp = "here_doc";
    while(1)
    {
        line = get_next_line(0);
        printf("%s", line);
        // CHECKER LES LIGNES //
        if(comparaison(line, cmp) == 1)
            return(printf("Ouais ma biche"));
        
        free(line);
    }
    return(0);
}