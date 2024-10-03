#include "STLS.h"
#include "stdio.h"
#include "stdlib.h"

void push_Back(Vector *v, int value)
{
    if (v->size >= v->capacity)
    {
        resizeVector(v);
    }
    v->data[v->size++] = value;
}
void pop_Back(Vector *vec)
{
    if (vec->size > 0)
    {
        vec->size--;
    }
}
int size(Vector *vec)
{
    return vec->size;
}
void resizeVector(Vector *v)
{
    v->capacity *= 2;
    v->data = (int *)realloc(v->data, v->capacity * sizeof(int));
}

void initVector(Vector *v, int cap)
{
    v->size = 0;
    v->capacity = cap;
    v->data = (int *)malloc(cap * sizeof(int));
}

int getElement(Vector *v, int ind)
{
    if (ind < v->size && ind >= 0)
    {
        return v->data[ind];
    }
}