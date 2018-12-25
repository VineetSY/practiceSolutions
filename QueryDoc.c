#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {

}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 

}

char*** kth_paragraph(char**** document, int k) {

}

char**** get_document(char* text) {
    char *word = (char *)malloc(sizeof(char)*50);
    char **sentence = (char **)malloc(sizeof(char *));
    char ***paragraph = (char ***)malloc(sizeof(char **));
    char ****doc = (char ****)malloc(sizeof(char ***));
    if( (word == NULL) || (sentence == NULL) || (paragraph == NULL) || (doc == NULL) )
    {
        printf("\nerror in malloc\n");
        return 1;
    }
    int index = 0, i_char = 0, i_sen = 0, i_para = 0;
    char c = text[index];
    int wordCount = 0;
    int doclen = strlen(text);
    for(index = 0; index < doclen ; ++index)
    {
        if(isalpha(c)) 
        {
            word[i_char++] = text[index];
        }
        else if( c == ' ') 
        {
            /* Complete last words as a string */
            word[i_char] = '\0';
            i_char = 0;
            /* Reallocate memory for word and add the word to words array */
            sentence[i_sen] = (char *)realloc((sentence+i_sen),sizeof(char *)*(i_sen+1));
            i_sen++;
            strcpy(sentence[i_sen], word);
        }
        else if( c == '.')
        {
            /* Complete the last sentence*/
        }
        else if( c == '\n')
        {
            /* Complete the last paragraph */
        }
        printf("\n%c",text[index]);
    }
}


char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}
