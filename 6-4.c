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


void selectsort(struct tnode *p, int n)
{
	int i;

	struct tnode *q;
	q -> next = p; //次の構造体から見るようにする

	for (i = 0; i < n - 1; i++)
	{
		struct tnode *t = q; //origin
		struct tnode *x = q; //Input max of number
		struct tnode *y;

		for (int j = i+1; j<n; j++)
		{
			if (x->count < ((t->next)->count)) // if old max < origin
			{
				x = t; // Input max
				t = t->next; //point next
			}
		}
		//swapの作業 扱うのは、q,xだけ。
		//qは基準として交換するノードを固定、xはqを含む後のノードの中の最大値のノードのひとつの集団
		y = q->next; 	   //p->A hold
		x->next = t->next; //p->A p->B (q->Bはまだある)
		q->next = y; 	   //q->B : q->a
		//AとBの位置はもう変わっている
		y = q->next->next;
		(q->next->next) = (t->next->next); //A->(Aがさしているやつ)

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
