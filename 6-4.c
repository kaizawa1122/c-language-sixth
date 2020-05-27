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

struct tnode *talloc(void);
char *strdup01(char *s);

struct tnode {
	char *word;
	int count;
	struct tnode *next;
};

int main(void)
{
	struct tnode *root,*q;
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

	q = talloc();
	q->next = root;

	len = length(root);
	selectsort(q,len);
	listprint(root);
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
	int i;

	for (i = 0; i < n - 1; i++)
	{
		struct tnode *t = q; //origin
		struct tnode *x = q; //Input max of number
		struct tnode *a, *b, *c, *d;

		for (int j = i+1; j<n; j++)
		{
			if (x->count < ((t->next)->count)) // if old max < origin
			{
				x = t; // Input max
			}
			t = t->next; //point next
		}
		//swapの作業 扱うのは、q,xだけ。
		//保持するためのもの
		a = t->next;
		b = x->next;
		c = t->next->next;
		d = x->next->next;

		t->next = b;
		x->next = a;
		t->next->next = c;
		x->next->next = d;

		q = q->next; //二文字目以降next
	}
	q -> next = NULL; //最後の文字にNULL挿入
}

void listprint(struct tnode *p)
{
	if (p != NULL) 
	{
		listprint(p->next);
		printf("%4d %s\n",p->count, p->word);
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
