typedef struct
{
    int size;
    int capacity;
    int *data;
} Vector;

void push_Back(Vector *v, int value);
void pop_Back(Vector *vec);
int size(Vector *vec);
void resizeVector(Vector *v);
void initVector(Vector *v, int cap);
int getElement(Vector *v, int ind);