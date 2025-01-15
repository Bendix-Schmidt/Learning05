#ifndef VBC_H
# define VBC_H

# include <stdio.h>
# include <malloc.h>
# include <ctype.h>

typedef struct node {
	enum {
		ADD,
		MULTI,
		VAL 
	}   type;
	int val;
	struct node *l;
	struct node *r;
}	node;

node	*new_node(node n);
void	destroy_tree(node *n);

void	unexpected_char(char c);

int		accept(char **s, char c);
int		expect(char **s, char c);

node	*parse_value(char **s);
node	*parse_parens(char **s);
node	*parse_multiplication(char **s);
node	*parse_addition(char **s);
node	*parse_expr(char *s);

int		eval_tree(node *tree);

#endif