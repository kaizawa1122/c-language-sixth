#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *);
int getword(char *,int);
char *number;

void treeprint(struct tnode *p);

struct tnode {
	char *word;
	struct tnode *left;
	struct tnode *right;
};

struct gnode {
	char  *word;
	struct tnode *list[MAXWORD];
	struct gnode *next;
}

void createGroup(struct gnode *g, struct gnode *t)
{
	if (t != NULL)
	{
		createGroup(g, t->left);
		addGroup(g,t);
		createGroup(g, t->right);
	}
}

struct gnode *addGroup(struct gnode *g, struct tnode *t )
{
	char *s
	s = strdup01(t -> word);

	if (g == NULL) 
	{
		g =  (struct tnode *) malloc(sizeof(struct tnode));
		g ->word = s;
		g -> next = NULL;
		g -> list[0] = t;
		g -> count = 1;
	}
	else if (strncmp(g -> word, t->word, number) == 0) 
	{
		g -> list[g-> count++] == t;
	}
	else 
	{
		g -> next = addGroup(g->next,t);
	}

	return g;
}
int argvnumber;

int main(int argc, char *argv[])
{
	struct tnode *root;
	struct tnode *groot;
	char word[MAXWORD];

	root = NULL;

	number = argv[1];
	argvnumber = atoi(number); //数字の取得
	
	while (getword(word,MAXWORD) != EOF)
	{
		if (isalpha(word[0]))
		{
			root = addtree(root, word);
		}
	}

	treeprint(root);
	return 0;
}

struct tnode *talloc(void);
char *strdup01(char *s);

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL)
	{
		p = talloc();
		p->word = strdup01(w);
		p->left = p->right = NULL;
	}
	else if ((cond = strncmp(w, p->word,argvnumber)) == 0)
	{
		p -> count++;
	}
	else if (cond < 0)
	{
		p->left = addtree(p->left,w);
	}
	else
	{
		p->right = addtree(p->right,w);
	}
	return p;
}

void gprint(struct gnode *g)
{
	if (g != NULL) 
	{
		printf("%s\n", g->list);
		for (int i =0; i<g->count; ++i)
		{
			printf("%s\n", g -> list[i]->word);
		}
		printf("\n");
		gprint(g->next);
	}
}

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup01(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL)
	{
		strcpy(p,s);
	}
	return p;
}

int getword(char *word, int lim)
{
	int c,getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()));
	if (c != EOF)
	{
		*w++ = c;
	}
	if (!isalpha(c)) 
	{
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
	{
		if (!isalnum(*w = getch()))
		{
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
	{
		printf("ungetch: too many characters\n");
	}
	else
	{
		buf[bufp++] = c;
	}
}

//This is the comment. Hello How are you? I'm fine and you you you?
