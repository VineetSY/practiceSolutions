#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lexicographic_sort(const char* a, const char* b) {
    return strcmp(*(const char **) a, *(const char **) b);
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return (-1)*(strcmp(*(const char **) a, *(const char **) b));
}

int CountUniqueCharacters(char* str){
    int count = 0;
    _Bool appears = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (str[j] == str[i])
            {
                appears = 1;
                break;
            }
            else
            {
                appears = 0;
            }
        }
        if (!appears)
            count++;
    }
    return count;
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int na = CountUniqueCharacters(*(const char **) a);
    int nb = CountUniqueCharacters(*(const char **) b);
    if(na - nb == 0)
        return lexicographic_sort(a, b);
    return na - nb;
}

int sort_by_length(const char* a, const char* b) {
    int la = strlen(*(const char **) a);
    int lb = strlen(*(const char **) b);
    if(la - lb == 0)
        return lexicographic_sort(a, b);
    return la - lb;
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
//     qsort((void*)arr, len, sizeof(arr[0]), cmp_func);
    int i;
    int j;
    int count = len;
    char temp[50];

    for(i=0;i<count;i++)
    {
        for(j=i+1;j<count;j++)
        {
            if((*cmp_func)(&arr[i],&arr[j]) > 0)
            {
                strcpy(temp,arr[i]);
                strcpy(arr[i],arr[j]);
                strcpy(arr[j],temp);
            }
        }
    }
}


int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}
