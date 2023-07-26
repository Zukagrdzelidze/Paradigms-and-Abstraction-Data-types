#include "vector.h"

typedef struct {
    bool *bitmap; // set to be of size 'groupSize'
    vector strings; // vector of dynamically allocated, nonempty C strings
} group;


typedef struct {
    group *groups; // dynamically allocated array of structs, defined below
    int numGroups; // number of groups
    int arrayLength; // logical length of the full sparsestringarray
    int groupSize; // number of strings managed by each group
} sparsestringarray;

typedef void (*SSAMapFunction)(int index, const char *str, void *auxData);
static void StringFree(void *elem) { free(*(char **) elem); }

void SSANew(sparsestringarray *ssa, int arrayLength, int groupSize);
bool SSAInsert(sparsestringarray *ssa, int index, const char *str);
void SSAMap(sparsestringarray *ssa, SSAMapFunction mapfn, void *auxData);
void SSADispose(sparsestringarray *ssa);