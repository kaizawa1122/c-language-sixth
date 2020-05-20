#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
struct tnode *addword(struct tnode *p, char *w);
void listprint(struct tnode *);
int getword(char *,int);
int length(struct tnode *p);
void selectsort(struct tnode *p, int n);
void swap(struct tnode *ptr1,struct tnode *ptr2);

struct tnode {
	char *word;
	int count;
	struct tnode *next;
};

int main(void)
{
	struct tnode *root;
	char word[MAXWORD];
	char *number;
	int len;

	root = NULL;

	while (getword(word,MAXWORD) != EOF)
	{
		if (isalpha(word[0]))
		{
			root = addword(root, word);
		}
	}

	len = length(root);
	
	selectsort(root,len);
	listprint(root);
	return 0;
}

struct tnode *talloc(void);
char *strdup01(char *s);

struct tnode *addword(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL)
	{
		p = talloc();
		p->word = strdup01(w);
		p -> count = 1;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
	{
		p ->count++;
		return p;
	}
	else 
	{
		p->next = addword(p->next,w);
	}
	return p;
}

int length(struct tnode *p)	
{
	int len = 0;
	while(p != NULL)
	{
		++len;
	}
	return len;
}


void selectsort(struct tnode *p, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		struct tnode *t = p->next;
		struct tnode *x = p;
		int count = p -> count;

		for (int j = i+1; j<n; j++)
		{
			if (count < (t ->count))
			{
				count = t -> count;
				*x = t;
			}
			t = t->next;
		}
	}
}

void listprint(struct tnode *p)
{
	if (p != NULL) 
	{
		listprint(p->next);
		printf("%4d %s\n",p->count, p->word);
	}
}

void swap(struct tnode *ptr1,struct tnode *ptr2)
{
	struct tnode hold;

	hold = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = hold;
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
