#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 3
#define BUFSIZE 100
#define MAXLINE 1001

static struct nlist *hashtab[HASHSIZE];
struct nlist *lookup(char *s);

void undef(char *s);
void printfhashtab();
void printNode (struct nlist* pList);
struct nlist *install(char *name, char *defn);
int getline01(char s[], int lim);
int strindex(char s[], char t[]);

char buf[BUFSIZE];
int bufp = 0;
char *pattern = "#define";
char undefchar[MAXLINE] = "OUT";

struct nlist 
{
	struct nlist *next;
	char *name;
	char *defn;
};

int main ()
{
	char line[MAXLINE];
	int len;
	while((len = getline01(line,MAXLINE)) > 0)
	{
		if (strindex(line, pattern) >= 0)
		{
			char *a, *b, *token;
			token = strtok(line, " ");
			a = strtok(NULL, " ");
			b = strtok(NULL, "\n");
			install(a,b);
			undef(undefchar);
		}
	}
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

struct nlist *prvlookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np->next != NULL; np = np->next)
	{
		if(strcmp(s,np->next->name) == 0)
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
void undef(char *s)
{
	struct nlist *np,*t;

	if ((np = prvlookup(s)) != NULL) //定義を探す
	{
		t = np->next;
		np->next = np->next->next;
		free(t);
	}
	else
	{
		printf("条件に当てはまる定義がありません\n");
	}
}

//hashtabを表示する
void printfhashtab()
{
	struct nlist* pList;
	for (int i = 0; i < HASHSIZE; ++i)
	{
		pList = hashtab[i];
		if (pList == NULL)
		{
			printf("%d : NULL\n",i);
		}
		else
		{
			printf("%d : ",i);
			printNode(pList);
			puts("\n");
		}
	}
}
void printNode (struct nlist* pList)
{
	printf("name %s,defn: %s !----!", pList->name,pList->defn);
	if (pList->next != NULL)
	{
		printNode (pList->next);
	}
}
int getline01(char *s, int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
	{
		s[i++] = c;
	}
	if(c == '\n')
	{
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}
int strindex(char *s, char *t)
{
	int i, j, k;
	for (i = 0; s[i] != '\0'; i++)
	{
		for (j=k, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++);
		if (k > 0 && t[k] == '\0')
		{
			return i;
		}
	}
	return -1;
}
