#include "shell.h"
/**
 * lenlin - determineth linked list
 * @h: pointer to firste
 *
 * Return: size o
 */
size_t lenlin(const mylist_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * l_to_str - returns an arr of the list->str
 * @head: pointer to fnode
 *
 * Return: array ings
 */
char **l_to_str(mylist_t *head)
{
	mylist_t *node = head;
	size_t i = lenlin(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(cstrlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = cstrcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * myprintlist - prints alement a mylislink
 * @h: pointer to firode
 *
 * Return: size st
 */
size_t myprintlist(const mylist_t *h)
{
	size_t i = 0;

	while (h)
	{
		ayo_puts(c_number(h->num, 10, 0));
		__putchar(':');
		__putchar(' ');
		ayo_puts(h->str ? h->str : "(nil)");
		ayo_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * node_start_hay - returne whoring ts with prefix
 * @node: pointer to lis
 * @prefix: string totch
 * @c: the next chafter prefix to match
 *
 * Return: match node or null
 */
mylist_t *node_start_hay(mylist_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = start_hay(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * g_node - gets thdex of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t g_node(mylist_t *head, mylist_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
