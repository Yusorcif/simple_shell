#include "shell.h"
/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
mylist_t *add_node(mylist_t **head, const char *str, int num)
{
  mylist_t *new_head;

  if (!head)
    return (NULL);
  new_head = malloc(sizeof(mylist_t));
  if (!new_head)
    return (NULL);
  aymemset((void *)new_head, 0, sizeof(mylist_t));
  new_head->num = num;
  if (str)
    {
      new_head->str = cp_null(str);
      if (!new_head->str)
	{
	  free(new_head);
	  return (NULL);
	}
    }
  new_head->next = *head;
  *head = new_head;
  return (new_head);
}
/**
 * a_n_e - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
mylist_t *a_n_e(mylist_t **head, const char *str, int num)
{
  mylist_t *new_node, *node;

  if (!head)
    return (NULL);
  node = *head;
  new_node = malloc(sizeof(mylist_t));
  if (!new_node)
    return (NULL);
  aymemset((void *)new_node, 0, sizeof(mylist_t));
  new_node->num = num;
  if (str)
    {
      new_node->str = cp_null(str);
      if (!new_node->str)
	{
	  free(new_node);
	  return (NULL);
	}
    }
  if (node)
    {
      while (node->next)
	node = node->next;
      node->next = new_node;
    }
  else
    *head = new_node;
  return (new_node);
}
/**
 * p_l_s - prints only the str element of a mylist_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t p_l_s(const mylist_t *h)
{
  size_t i = 0;

  while (h)
    {
      ayo_puts(h->str ? h->str : "(nil)");
      ayo_puts("\n");
      h = h->next;
      i++;
    }
  return (i);
}
/**
 * delnode - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delnode(mylist_t **head, unsigned int index)
{
  mylist_t *node, *prev_node;
  unsigned int i = 0;

  if (!head || !*head)
    return (0);
  if (!index)
    {
      node = *head;
      *head = (*head)->next;
      free(node->str);
      free(node);
      return (1);
    }
  node = *head;
  while (node)
    {
      if (i == index)
	{
	  prev_node->next = node->next;
	  free(node->str);
	  free(node);
	  return (1);
	}
      i++;
      prev_node = node;
      node = node->next;
    }
  return (0);
}
/**
 * fr_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void fr_list(mylist_t **head_ptr)
{
  mylist_t *node, *next_node, *head;

  if (!head_ptr || !*head_ptr)
    return;
  head = *head_ptr;
  node = head;
  while (node)
    {
      next_node = node->next;
      free(node->str);
      free(node);
      node = next_node;
    }
  *head_ptr = NULL;
}
