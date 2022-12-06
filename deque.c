/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:06:44 by yooh              #+#    #+#             */
/*   Updated: 2022/12/05 21:06:09 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

t_deque	*create_deque(void *value)
{
	t_deque	*result;

	result = (t_deque *) malloc(sizeof(t_deque));
	if (result == NULL)
		return (NULL);
	result->value = value;
	result->left = NULL;
	result->right = NULL;
	result->index = 0;
	return (result);
}

t_deque	*deque_push(t_deque **head, void *value)
{
	t_deque	*cur;
	t_deque	*new;

	new = create_deque(value);
	if (new == NULL)
		return (NULL);
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	cur = *head;
	while (cur->right)
		cur = cur->right;
	new->index = cur->index + 1;
	cur->right = new;
	new->left = cur;
	return (new);
}

ssize_t	deque_length(t_deque *head)
{
	ssize_t	i;

	i = 0;
	if (head == NULL)
		return (0);
	while (head)
	{
		i++;
		head = head->right;
	}
	return (i);
}

void	free_deque(t_deque *dq)
{
	t_deque	*tmp;

	while (dq)
	{
		tmp = dq;
		dq = dq->right;
		if (tmp->left)
			tmp->left = NULL;
		if (tmp->right)
			tmp->right = NULL;
		free(tmp->value);
		free(tmp);
	}
}
