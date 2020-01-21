# include "argz.h"

int substr_index(const char *str1, const char *str2, size_t argz_len) 
{
	int index = 0, j = 0, buff = 0;
	size_t i = 0;
	while (i <= argz_len) 
	{
		buff = i;
		while ((str1[buff] == str2[j]) && (str2[j] != '\0'))
		{
			buff++;
			j++;
		}
		if (str2[j] != '\0') 
		{
			j = 0;
			buff = 0;
			i++;
		}
		else 
		{
			index = buff - j;
			return index;
		}
	}
	if (i > argz_len)
	{
		printf("No substr in str\n");
		return 0;
	}
}

void separation(char **argz, size_t len)
{
	size_t i = 0;
	while (i < len) 
	{
		while (((*argz)[i] != 58) && (i < len)) 
		{
			i++;
		}
		(*argz)[i] = '\0';
		i++;
	}
}

error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len)
{
	size_t j;
	*argz_len = strlen(string);

	if (*argz == NULL)
		return ERROR;

	*argz = (char*)malloc(strlen(string) * sizeof(char));
	for (j = 0; j < *argz_len; j++) 
	{
		(*argz)[j] = string[j];
	}
	separation(argz, *argz_len);
	return OK;
}

size_t argz_count(const char *argz, size_t argz_len)
{
	size_t i = 0;
	int count = 0;
	for(;i <= argz_len;i++)
	{
		if (argz[i] == '\0') 
			count++;
	}
	return count;
}

void argz_print(const char *argz, size_t argz_len) 
{
	size_t i = 0;
	printf("\t");
	for (;i < argz_len;i++) 
	{
		if (argz[i] != '\0')
			printf("%c", argz[i]); 
		else 
			printf("\n\t");
	}
}

error_t argz_add(char **argz, size_t *argz_len, const char *string)
{
	size_t old_len, i, len_string;
	old_len = *argz_len;
	len_string = strlen(string);
	i = 0;

	if (string == NULL)
		return ERROR;

	*argz_len += len_string + 1;
	*argz = (char*)realloc(*argz, *argz_len*(sizeof(char)));
	(*argz)[old_len] = '\0';
	while (i < len_string) 
	{
		(*argz)[old_len + i + 1] = string[i];
		i++;
	}
	separation(argz, *argz_len);
	printf("\nArgz_len(add) = %d\n", *argz_len);
	return OK;
}

void argz_delete(char **argz, size_t *argz_len, char *entry)
{
	int entry_len;
	size_t i;
	entry_len = strlen(entry) + 1;
	i = substr_index(*argz, entry, *argz_len);

	if (i == 0)
	{
		printf("No str to delete in argz\n");
		return;
	}

	i += entry_len;
	for (; i <= (*argz_len); i++) 
	{
		(*argz)[i - entry_len] = (*argz)[i];
	}
	*argz_len = *argz_len - entry_len+1;
	*argz = (char*)realloc(*argz, (*argz_len));
	separation(argz, *argz_len);
	printf("\nArgz_len(delete) = %d\n", *argz_len);
	return;
}

error_t argz_insert(char **argz, size_t *argz_len, char *before, const char *entry) 
{
	int i, k, entry_len;
	if (before == NULL)
		return ERROR;
	if (entry == NULL)
		return ERROR;
	i = substr_index(*argz, before, *argz_len);
	if (i == 0)
	{
		printf("No matching in argz\n");
		return ERROR;
	}
	entry_len = strlen(entry);
	*argz_len += entry_len;
	*argz = (char*)realloc(*argz, *argz_len * sizeof(char));
	for (k = *argz_len; k >= i + entry_len; k--) 
	{
		(*argz)[k] = (*argz)[k - entry_len];
	}
	for (k = 0; k < entry_len; k++) 
	{
		(*argz)[i] = entry[k];
		i++;
	}
	separation(argz, *argz_len);
	printf("\nArgz_len(insert) = %d\n", *argz_len);
	return OK;
}

char * argz_next(char *argz, size_t argz_len, const char *entry) 
{
	if (entry == NULL)
		return argz;

	char* next_index = (const char*)entry;
	next_index += strlen(next_index) + 1;

	if (next_index - argz >= argz_len)
		return 0;
	else 
		return next_index;
}

error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with) 
{
	argz_insert(argz, argz_len, (char*)str, with);
	int str_len;
	size_t i;
	str_len = strlen(str);
	i = substr_index(*argz, str, *argz_len);
	if (i == 0)
	{
		printf("No str to replace in argz\n");
		return ERROR;
	}
	i += str_len;
	for (; i < (*argz_len); i++) 
	{
		(*argz)[i - str_len] = (*argz)[i];
	}
	*argz_len = *argz_len - str_len - 1;
	*argz = (char*)realloc(*argz, (*argz_len));
	separation(argz, *argz_len);
	printf("\nArgz_len(replace) = %d\n", *argz_len);
	return OK;
}
