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
void swap(struct tnode *q,struct tnode *x);

struct tnode *talloc(void);
char *strdup01(char *s);

struct tnode {
	char *word;
	int count;
	struct tnode *next;
};

int main(void)
{
	struct tnode *root,*q,*t;
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
	q = talloc();
	q->next = root;

	t = q;
	while(t->next != NULL)
	{
		t = t->next;
	}
	t->next = talloc();

	selectsort(q,len);
	listprint(q->next);
	return 0;
}


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
		p = p -> next;
	}
	return len;
}


void selectsort(struct tnode *q, int n)
{
	int i,j;

	for (i = 0; i < n - 1 ; i++)
	{
		struct tnode *t = q; 
		struct tnode *x = q; //Input max of number

		for (j = i+1; j<n; j++)
		{
			if (x->count < ((t->next)->count)) // if old max < origin
			{
				x = t; // Input max
				swap(q,x);
			}
			t = t->next; //point next
		}
		q = q->next; //二文字目以降next
	}
}

void swap(struct tnode *q,struct tnode *x)
{
	struct tnode *a, *b, *c, *d;
	//swapの作業。
	//保持するためのもの

	if (q->next == x)
	{
		a = q;
		b = x;
		c = q->next->next;
		d = x->next->next;

		a->next = c;
		c->next = b;
		b->next = d;
	}
	else 
	{
		a = q->next;
		b = x->next;
		c = q->next->next;
		d = x->next->next;

		q->next = b;
		x->next = a;
		q->next->next = c;
		x->next->next = d;
	}
}

void listprint(struct tnode *q)
{
	if (q != NULL) 
	{
		printf("%4d %s\n",q->count, q->word);
		listprint(q->next);
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
