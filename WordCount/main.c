#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h> // Türkçe karakterler



typedef struct words_s {
    char *str;
    int count;
    struct words_s *next;
} words;

words *create_words (char *word)
{
    words *new_Word = malloc (sizeof (words));
    if (NULL != new_Word) {
        new_Word->str = (char *) malloc ((strlen (word)) + 1);
        strcpy (new_Word->str, word);
        new_Word->str[strlen (word)] = '\0';
        //printf (" Create: %s ", newWord->str);
        new_Word->count = 1;
        new_Word->next = NULL;
    }
    return new_Word;
}

words *add_word (words **wordList, char *word)
{

  words *new_Word = NULL;
    if (!*wordList) {
        return *wordList = create_words (word);
    }

    words *temp = *wordList;
    while (temp!= NULL) {

        if (strcmp (temp->str, word) == 0) {
            temp->count = temp->count +1;
            return *wordList;
        }
        new_Word = temp;
        temp = temp->next;
    }

    new_Word->next = create_words (word);
    return new_Word;


}
words *ilk=NULL, *son=NULL;

int main (int argc, char *argv[]) {

    words *mywords = NULL;
    FILE *myFile;
    setlocale(LC_ALL,"turkish");

    myFile = fopen ("metin.txt", "r");
    if (myFile == 0) {
        printf ("file not opened\n");
        return 1;
    } else {
        printf ("file opened \n");
    }
    printf("\n");

    //start reading file character by character
    int ch = 0, word = 1, i = 0;
    char thisword[100];
    while ((ch = fgetc (myFile)) != EOF) {
        if (ch == ' ' ||  ch == '\n') {
            if (word == 1) {
                word = 0;
                thisword[i] = '\0';

                add_word (&mywords, thisword);
                i = 0;
            }
        }
        else {
            word = 1;
            thisword[i++] = tolower (ch);

        }
    }

    int k=1;
    while (mywords!=NULL)
    {
        printf("%d: %s ==> %d \n",k, mywords->str, mywords->count);
        mywords = mywords->next;
        k++;
    }

    return 0;

}
