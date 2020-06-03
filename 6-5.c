#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101
#define BUFSIZE 100

static struct nlist *hashtab[HASHSIZE];
struct nlist *lookup(char *s);
char *strdup01(char *s);

int getch();
char printfhashtab();

char buf[BUFSIZE];
int bufp = 0;

struct nlist 
{
	struct nlist *next;
	char *name;
	char *defn;
};

int main ()
{
	char a,b;
	getch();
	struct nlist *install(a,b);
	printfhashtab();
}

unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
	{
		hashval = *s + 31 * hashval;
	}
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
	struct nlist *np;
	
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
	{
		if (strcmp(s, np->name) == 0)
		{
			return np;
		}
	}
	return NULL;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL)
	{
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
		{
			return NULL;
		}
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else
	{
		free((void *) np->defn);
	}
	if ((np->defn = strdup(defn)) == NULL)
	{
		return NULL;
	}
	return np;
}

char *strdup01(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
	{
		strcpy(p,s);
	}
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
char printfhashtab()
{

}
