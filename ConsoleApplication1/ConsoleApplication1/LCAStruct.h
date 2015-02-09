#ifndef MAILLON_H 
#define MAILLON_H

typedef struct s_maillon
{
	float ymax;
	float xmin;
	float coeffInversed;
	struct s_maillon *next;

} Maillon;

Maillon* lcamaillon_new(float ymax, float xmin, float coeffInversed);
void lcamaillon_display(Maillon* m);
unsigned int lcamaillon_size(Maillon* m);
void lcamaillon_append(Maillon** m, float ymax, float xmin, float coeffInversed);
void lcamaillon_remove_index(Maillon** m, int index);
void lcamaillon_insert_index(Maillon** m, int index, float ymax, float xmin, float coeffInversed);

#endif