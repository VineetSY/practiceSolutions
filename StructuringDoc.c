#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};
struct document get_document(char* text) {
    struct word word;
    struct sentence sentence;
    struct paragraph paragraph;
    struct document doc;
    int index = 0, i_char = 0, i_sen = 0, i_para = 0, i_doc = 0;
    char c;
    int doclen = strlen(text);

    word.data = malloc(sizeof(char)*MAX_CHARACTERS);
    sentence.data = malloc(sizeof(struct word));
    sentence.word_count = 0;
    paragraph.data = malloc(sizeof(struct sentence));
    paragraph.sentence_count = 0;
    doc.data = malloc(sizeof(struct paragraph)*MAX_PARAGRAPHS);
    doc.paragraph_count = 0;

    for(index = 0; index < doclen ; ++index)
    {
        c = text[index];
        if(isalpha(c)) 
        {
            word.data[i_char++] = text[index];
        }
        else if( c == ' ') 
        {
            /* Complete last words as a string */
            word.data[i_char] = '\0';
            i_char = 0;
            /* Reallocate memory for word and add the word to words array */
            sentence.data = realloc((sentence.data),sizeof(struct word)*(i_sen+1));
            sentence.data[i_sen] = word;
            ++sentence.word_count;
            ++i_sen;
            word.data = malloc(sizeof(char)*MAX_CHARACTERS);
        }
        else if( c == '.')
        {
            /* Complete the last sentence*/
            word.data[i_char] = '\0';
            i_char = 0;
            /* Reallocate memory for word and add the word to words array */
            sentence.data = realloc(sentence.data,sizeof(struct word)*(i_sen+1));
            sentence.data[i_sen] = word;
            ++sentence.word_count;
            i_sen = 0;
            paragraph.data = realloc(paragraph.data,sizeof(struct sentence)*(i_para+1));
            paragraph.data[i_para] = sentence;
            ++paragraph.sentence_count;
            ++i_para;
            /* New word and new sentence locations */
            word.data = malloc(sizeof(char)*MAX_CHARACTERS);
            sentence.word_count = 0;
            sentence.data = malloc(sizeof(struct word));
        }
        else if( c == '\n')
        {
            i_para = 0;
            doc.data[i_doc] = paragraph;
            ++doc.paragraph_count;
            ++i_doc;
            paragraph.sentence_count = 0;
            paragraph.data = malloc(sizeof(char **));
        }
    }

    doc.data[i_doc] = paragraph;
    ++doc.paragraph_count;
    free(word.data);
    free(sentence.data);
    return doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n-1].data[m-1].data[k-1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m-1].data[k-1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k-1];
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
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

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }
}
