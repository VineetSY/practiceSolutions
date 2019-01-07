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

#define SWAP(a, b, size)                                                      \
  do                                                                              \
    {                                                                              \
      size_t __size = (size);                                                      \
      char *__a = (a), *__b = (b);                                              \
      do                                                                      \
        {                                                                      \
          char __tmp = *__a;                                                      \
          *__a++ = *__b;                                                      \
          *__b++ = __tmp;                                                      \
        } while (--__size > 0);                                                      \
    } while (0)
#define MAX_THRESH 4
typedef struct
  {
    char *lo;
    char *hi;
  } stack_node;
#define CHAR_BIT 8
#define STACK_SIZE        (CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)        ((void) ((top->lo = (low)), (top->hi = (high)), ++top))
#define        POP(low, high)        ((void) (--top, (low = top->lo), (high = top->hi)))
#define        STACK_NOT_EMPTY        (stack < top)

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
//     qsort((void*)arr, len, sizeof(arr[0]), cmp_func);
    // int i;
    // int j;
    // int count = len;
    // char temp[50];

    // for(i=0;i<count;i++)
    // {
    //     for(j=i+1;j<count;j++)
    //     {
    //         if((*cmp_func)(&arr[i],&arr[j]) > 0)
    //         {
    //             strcpy(temp,arr[i]);
    //             strcpy(arr[i],arr[j]);
    //             strcpy(arr[j],temp);
    //         }
    //     }
    // }
  char *base_ptr = (char *) arr;
  size_t size = sizeof(arr[0]);
  const size_t max_thresh = MAX_THRESH * size;
 
  if ( len == 0)
    /* Avoid lossage with unsigned arithmetic below.  */
    return;
 
  if ( len > MAX_THRESH)
    {
      char *lo = base_ptr;
      char *hi = &lo[size * ( len - 1)];
      stack_node stack[STACK_SIZE];
      stack_node *top = stack;
 
      PUSH (NULL, NULL);
 
      while (STACK_NOT_EMPTY)
        {
          char *left_ptr;
          char *right_ptr;
 
          /* Select median value from among LO, MID, and HI. Rearrange
             LO and HI so the three values are sorted. This lowers the
             probability of picking a pathological pivot value and
             skips a comparison for both the LEFT_PTR and RIGHT_PTR in
             the while loops. */
 
          char *mid = lo + size * ((hi - lo) / size >> 1);
 
          if ((*cmp_func) ((void *) mid, (void *) lo ) < 0)
            SWAP (mid, lo, size);
          if ((*cmp_func) ((void *) hi, (void *) mid ) < 0)
            SWAP (mid, hi, size);
          else
            goto jump_over;
          if ((*cmp_func) ((void *) mid, (void *) lo ) < 0)
            SWAP (mid, lo, size);
        jump_over:;
 
          left_ptr  = lo + size;
          right_ptr = hi - size;
 
          /* Here's the famous ``collapse the walls'' section of quicksort.
             Gotta like those tight inner loops!  They are the main reason
             that this algorithm runs much faster than others. */
          do
            {
              while ((*cmp_func) ((void *) left_ptr, (void *) mid ) < 0)
                left_ptr += size;
 
              while ((*cmp_func) ((void *) mid, (void *) right_ptr ) < 0)
                right_ptr -= size;
 
              if (left_ptr < right_ptr)
                {
                  SWAP (left_ptr, right_ptr, size);
                  if (mid == left_ptr)
                    mid = right_ptr;
                  else if (mid == right_ptr)
                    mid = left_ptr;
                  left_ptr += size;
                  right_ptr -= size;
                }
              else if (left_ptr == right_ptr)
                {
                  left_ptr += size;
                  right_ptr -= size;
                  break;
                }
            }
          while (left_ptr <= right_ptr);
 
          /* Set up pointers for next iteration.  First determine whether
             left and right partitions are below the threshold size.  If so,
             ignore one or both.  Otherwise, push the larger partition's
             bounds on the stack and continue sorting the smaller one. */
 
          if ((size_t) (right_ptr - lo) <= max_thresh)
            {
              if ((size_t) (hi - left_ptr) <= max_thresh)
                /* Ignore both small partitions. */
                POP (lo, hi);
              else
                /* Ignore small left partition. */
                lo = left_ptr;
            }
          else if ((size_t) (hi - left_ptr) <= max_thresh)
            /* Ignore small right partition. */
            hi = right_ptr;
          else if ((right_ptr - lo) > (hi - left_ptr))
            {
              /* Push larger left partition indices. */
              PUSH (lo, right_ptr);
              lo = left_ptr;
            }
          else
            {
              /* Push larger right partition indices. */
              PUSH (left_ptr, hi);
              hi = right_ptr;
            }
        }
    }
 
  /* Once the BASE_PTR array is partially sorted by quicksort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. BASE_PTR points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */
 
#define min(x, y) ((x) < (y) ? (x) : (y))
 
  {
    char *const end_ptr = &base_ptr[size * ( len - 1)];
    char *tmp_ptr = base_ptr;
    char *thresh = min(end_ptr, base_ptr + max_thresh);
    char *run_ptr;
 
    /* Find smallest element in first threshold and place it at the
       array's beginning.  This is the smallest array element,
       and the operation speeds up insertion sort's inner loop. */
 
    for (run_ptr = tmp_ptr + size; run_ptr <= thresh; run_ptr += size)
      if ((*cmp_func) ((void *) run_ptr, (void *) tmp_ptr ) < 0)
        tmp_ptr = run_ptr;
 
    if (tmp_ptr != base_ptr)
      SWAP (tmp_ptr, base_ptr, size);
 
    /* Insertion sort, running from left-hand-side up to right-hand-side.  */
 
    run_ptr = base_ptr + size;
    while ((run_ptr += size) <= end_ptr)
      {
        tmp_ptr = run_ptr - size;
        while ((*cmp_func) ((void *) run_ptr, (void *) tmp_ptr ) < 0)
          tmp_ptr -= size;
 
        tmp_ptr += size;
        if (tmp_ptr != run_ptr)
          {
            char *trav;
 
            trav = run_ptr + size;
            while (--trav >= run_ptr)
              {
                char c = *trav;
                char *hi, *lo;
 
                for (hi = lo = trav; (lo -= size) >= tmp_ptr; hi = lo)
                  *hi = *lo;
                *hi = c;
              }
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
