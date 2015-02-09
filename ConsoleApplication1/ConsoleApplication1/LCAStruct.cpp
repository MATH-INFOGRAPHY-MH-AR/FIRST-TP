#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "LCAStruct.h"

/*
Maillon* lcamaillon_new(float ymax, float xmin, float coeffInversed)
{
	Maillon* m = (Maillon*)malloc(sizeof(Maillon));
	m->next = NULL;
	m->ymax = ymax;
	m->xmin = xmin;
	m->coeffInversed = coeffInversed;

	return m;
}

void lcamaillon_display(Maillon* m)
{
	while (m)
	{
		std::cout << m->ymax << " " << m->xmin << " " << m->coeffInversed << std::endl;
		m = m->next;
	}
}

unsigned int lcamaillon_size(Maillon* m)
{
	unsigned int size = 0;

	while (m)
	{
		size++;
		m = m->next;
	}

	return size;
}

void lcamaillon_append(Maillon** m, float ymax, float xmin, float coeffInversed)
{
	while (*m)
		m = &((*m)->next);
	*m = lcamaillon_new(ymax, xmin, coeffInversed);
}

void lcamaillon_remove_index(Maillon** m, int index)
{
	int i = 0;

	while (i != index && *m)
	{
		m = &((*m)->next);
		i++;
	}

	if (*m)
	{
		Maillon* tmp = *m;
		*m = (*m)->next;
		free(tmp);
	}
}

void lcamaillon_insert_index(Maillon** m, int index, float ymax, float xmin, float coeffInversed)
{
	int i = 0;

	while (i != index && *m)
	{
		m = &((*m)->next);
		i++;
	}

	if (i == index)
	{
		Maillon* new_maillon = lcamaillon_new(ymax, xmin, coeffInversed);
		new_maillon->next = *m;
		*m = new_maillon;
	}

}
*/