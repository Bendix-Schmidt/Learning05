/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschmidt <bschmidt@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:59:15 by bschmidt          #+#    #+#             */
/*   Updated: 2025/01/15 17:03:02 by bschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node {
	enum {
		ADD,
		MULTI,
		VAL 
	}	type;
	int val;
	struct node *l;
	struct node *r;
}   node;

node *parse_addition(char **s);

node *new_node(node n)
{
	node *ret = calloc(1, sizeof(node));
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

void destroy_tree(node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void unexpected_char(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int expect(char **s, char c)
{
	if (accept(s,c))
		return (1);
	//unexpected_char(**s);
	return (0);
}

node *parse_value(char **s)
{
	if (!isdigit(**s))
		return (NULL);
	
	node n = {.type = VAL, .val = **s - '0'};
	(*s)++;
	return (new_node(n));
}

node *parse_parens(char **s)
{
	if (!accept(s, '('))
		return (parse_value(s));
	
	node *ret = parse_addition(s);
	if (!ret)
		return NULL;

	if (!expect(s, ')'))
		return (destroy_tree(ret), NULL);
	
	return (ret);
}

node *parse_multiplication(char **s)
{
	node *l = parse_parens(s);
	
	if (!l)
		return NULL;
	
	while (accept(s, '*'))
	{
		node *r = parse_parens(s);
		if (!r)
			return (destroy_tree(l), NULL);
		
		node n = {.type = MULTI, .l = l, .r = r};
		l = new_node(n);
		if (!l)
		{
			return (destroy_tree(r), NULL);
		}
	}

	return (l);
}

node *parse_addition(char **s)
{
	node *l = parse_multiplication(s);
	
	if (!l)
		return NULL;
	
	while (accept(s, '+'))
	{
		node *r = parse_multiplication(s);
		if (!r)
			return (destroy_tree(l), NULL);
		
		node n = {.type = ADD, .l = l, .r = r};
		l = new_node(n);
		if (!l)
		{
			return (destroy_tree(r), NULL);
		}
	}

	return (l);
}

node *parse_expr(char *s)
{
	node *ret = parse_addition(&s);
	if (!ret || *s)
		return (unexpected_char(*s), destroy_tree(ret), NULL);
	
	if(*s)
	{
		destroy_tree(ret);
		return (NULL);
	}
	return (ret);
}

int eval_tree(node *tree)
{
	switch (tree->type)
	{
		case ADD:
			return (eval_tree(tree->l) + eval_tree(tree->r));
		case MULTI:
			return (eval_tree(tree->l) * eval_tree(tree->r));
		case VAL:
			return (tree->val);
	}
}

int main (int argc, char** argv)
{
	if (argc!= 2)
		return 1;
	node *tree = parse_expr(argv[1]);
	if (!tree)
		return 1;
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}