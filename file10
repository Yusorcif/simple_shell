#include "shell.h"
/**
 * in_buf - buffers chained commands
 * @ayoinfo: parameter struct
 * @buf: address of buffer
 * @len: address of len var.
 *
 * Return: bytes read
 */
ssize_t in_buf(ayoinfo_t *ayoinfo, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*pfree((void **)ayoinfo->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_sig);
#if C_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = agetline(ayoinfo, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			ayoinfo->linecount_myflag = 1;
			c_comments(*buf);
			ayo_history_list(ayoinfo, *buf, ayoinfo->histcount++);
			/* if (cstrchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				ayoinfo->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * agetinput - gets a line minus the newline
 * @ayoinfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t agetinput(ayoinfo_t *ayoinfo)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(ayoinfo->arg), *p;

	__putchar(BUF_FLUSH);
	r = in_buf(ayoinfo, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		ch_chain(ayoinfo, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (aychain(ayoinfo, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			ayoinfo->cmd_buf_type = C_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (cstrlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from agetline() */
	return (r); /* return length of buffer from agetline() */
}

/**
 * readabuffer - reads a buffer
 * @ayoinfo: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t readabuffer(ayoinfo_t *ayoinfo, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(ayoinfo->readmyfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * agetline - gets the next line of input from STDIN
 * @ayoinfo: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int agetline(ayoinfo_t *ayoinfo, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = readabuffer(ayoinfo, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = cstrchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = ayrealloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		cstrncat(new_p, buf + i, k - i);
	else
		cstrncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handle_sig - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void handle_sig(__attribute__((unused))int sig_num)
{
	ayo_puts("\n");
	ayo_puts("$ ");
	__putchar(BUF_FLUSH);
}
