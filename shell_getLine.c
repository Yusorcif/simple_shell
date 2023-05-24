#include "shell.h"
/**
 * in_buf - buffers chained commands
 * @yusinfo: parameter struct
 * @buf: address of buffer
 * @len: address of len var.
 *
 * Return: bytes read
 */
ssize_t in_buf(yusinfo_t *yusinfo, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
      /*pfree((void **)yusinfo->cmd_buf);*/
		free(*buf);
	*buf = NULL;
	signal(SIGINT, handle_sig);
#if C_GETLINE
	r = getline(buf, &len_p, stdin);
#else
	r = agetline(yusinfo, buf, &len_p);
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
	yus_history_list(yusinfo, *buf, yusinfo->histcount++);
	/* if (cstrchr(*buf, ';')) is this a command chain? */
	{
	*len = r;
	yusinfo->cmd_buf = buf;
	}
	}
	}
	return (r);
}

/**
 * agetinput - gets a line minus the newline
 * @yusinfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t agetinput(yusinfo_t *yusinfo)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(yusinfo->arg), *p;

	__putchar(BUF_FLUSH);
	r = in_buf(yusinfo, &buf, &len);
	if (r == -1) /* EOF */
	return (-1);
	if (len)/* we have commands left in the chain buffer */
	{
	j = i; /* init new iterator to current buf position */
	p = buf + i; /* get pointer for return */

	ch_chain(yusinfo, buf, &j, i, len);
	while (j < len) /* iterate to semicolon or end */
	{
	if (yuchain(yusinfo, buf, &j))
	break;
	j++;
	}

	i = j + 1; /* increment past nulled ';'' */
	if (i >= len) /* reached end of buffer? */
	{
	i = len = 0; /* reset position and length */
	yusinfo->cmd_buf_type = C_NORM;
	}

	buf_p = p; /* pass back pointer to current command position */
	return (cstrlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from agetline() */
	return (r); /* return length of buffer from agetline() */
}

/**
 * readabuffer - reads a buffer
 * @yusinfo: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t readabuffer(yusinfo_t *yusinfo, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
	return (0);
	r = read(yusinfo->readmyfd, buf, READ_BUF_SIZE);
	if (r >= 0)
	*i = r;
	return (r);
}

/**
 * agetline - gets the next line of input from STDIN
 * @yusinfo: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int agetline(yusinfo_t *yusinfo, char **ptr, size_t *length)
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

	r = readabuffer(yusinfo, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
	return (-1);

	c = cstrchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = yurealloc(p, s, s ? s + k : k + 1);
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
	yus_puts("\n");
	yus_puts("$ ");
	__putchar(BUF_FLUSH);
}
