#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode *addword(struct tnode *p, char *w);
void listprint(struct tnode *);
int getword(char *,int);
int length(struct tnode *p);
void mysort(struct tnode *p,struct tnode *q,int len);

struct tnode *talloc(void);
char *strdup01(char *s);

struct tnode {
	char *word;
	int count;
	struct tnode *next;
};

int main(void)
{
	struct tnode *root,*start,*sortedword;
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
	start = talloc();
	start->next = root;
	sortedword = talloc();

	mysort(start,sortedword,len);
	listprint(sortedword);
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

void mysort(struct tnode *q,struct tnode *sortedword,int len)
{
	for(int i = 0; i < len; ++i)
	{
		int maxnumber = 0;
		struct tnode *t, *savenode, *addsave;

		for(t = q; t->next != NULL; t = t->next)
		{
			if (t->next->count > maxnumber)
			{
				maxnumber = t->next->count;
				savenode = t; //最大のカウントのノードの手前を指すノード
			}
		}

		addsave = savenode->next; // 新しい短方向リストに最大のノードを保持する
		savenode->next = savenode->next->next; //旧リストの最大のノードを飛ばしている
		sortedword->count = addsave->count; //sortedwordのnextノードも保持してしまうため一つずつコピー。
		sortedword->word = addsave->word; //sortedwordのnextノードも保持してしまうためwordのノードをcopy。
		sortedword->next = talloc(); //NULLの状態だからメモリを確保する
		sortedword = sortedword->next; //sortedwordを更新する
	}
}

void listprint(struct tnode *q)
{
	if (q->next != NULL) 
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
