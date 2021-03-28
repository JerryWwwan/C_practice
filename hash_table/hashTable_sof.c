#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct nlist { /* table entry: */
    char *key; /* defined key */
    char *val; /* replacement text */
    struct nlist *next; /* next entry in chain */
}hash_t;

#define HASHSIZE 101
hash_t *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
hash_t*lookup(char *s)
{
    int i = 0;
    hash_t *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next){
        printf("%d\n",i++);
        if (strcmp(s, np->key) == 0)
          return np; /* found */
    }
    return NULL; /* not found */
}

/* install: put (key, val) in hashtab */
hash_t *install(char *key, char *val)
{
    hash_t *np;
    unsigned hashval;
    if ((np = lookup(key)) == NULL) { /* not found */
        np = (hash_t *) malloc(sizeof(*np));
        if (np == NULL || (np->key = strdup(key)) == NULL)
          return NULL;
        hashval = hash(key);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *) np->val); /*free previous val */
    if ((np->val = strdup(val)) == NULL)
       return NULL;
    return np;
}


int main()
{
    unsigned hashval;
    hash_t *result;
    printf("hashtab:%#x\n",hashtab);
    install("test123","123456");
    hashval = hash("test123");
    printf("hashtab[%d]:     %#x\n",hashval,hashtab[hashval]);
    printf("hashtab[%d]->key:%#x\n",hashval,&(hashtab[hashval]->key));
    printf("hashtab[%d]->val:%#x\n",hashval,&(hashtab[hashval]->val));
    printf("hashtab[%d]->next:%#x\n",hashval,&(hashtab[hashval]->next));
    install("test2","456");

    result = lookup("test2");
    printf("%s\n",result->val);


    result = lookup("test1");
    if(result != NULL){
        printf("%s\n",result->val);
    }else{
        printf("NULL\n");
    }
    

    return 0;
}