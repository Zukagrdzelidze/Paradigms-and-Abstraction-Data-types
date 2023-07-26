#include "GenericSortedSet.h"



static const int kInitialCapacity = 4;

/*
* Function: SetNew
* Usage: SetNew(&stringSet, sizeof(char *), StringPtrCompare);
*
SetNew(&constellations, sizeof(pointT), DistanceCompare);
* ----------------
* SetNew allocates the requisite space needed to manage what
* will initially be an empty sorted set. More specifically, the
* routine allocates space to hold up to 'kInitialCapacity' (currently 4)
* client elements.
*/
void SetNew(sortedset* set, int elemSize, int (*cmpfn)(const void*, const void*)) {
    assert(elemSize > 0);
    assert(set != NULL);
    assert(cmpfn != NULL);
    set->cmpfn = cmpfn;
    set->elemSize = elemSize;
    set->allocLen = kInitialCapacity;
    set->logLen = 0;
    set->root = (int*)malloc(1 + set->allocLen * (set->elemSize + 2 * sizeof(int)));
}


int* FindNode(sortedset* set, const void* elem){
    void* curr;
    int* root = set->root;
    while(*root != -1){
        curr = (char*)(set->root + 1) + *root * (sizeof(int) * 2 + set->elemSize);
        int cmp = set->cmpfn(curr, elem);
        if(cmp == 0){
            break;
        } else if(cmp < 0){
            root = (char*)curr + set->elemSize;
        }else{
            root = (char*)curr + set->elemSize + sizeof(int);
        }
    }
    return root;
}


/*
* Function: SetSearch
* Usage: if (SetSearch(&staffSet, &lecturer) == NULL)
*
printf("musta been fired");
* -------------------
* SetSearch searches for the specified client element according
* the whatever comparison function was provided at the time the
* set was created. A pointer to the matching element is returned
* for successful searches, and NULL is returned to denote failure.
*/
void* SetSearch(sortedset* set, const void* elemPtr) {
    int* root = FindNode(set, elemPtr);
    if(*root == -1) return NULL;
    return (char*) (set->root + 1) + *root * (sizeof(int) * 2 + set->elemSize);
}



/*
* Function: SetAdd
* Usage: if (!SetAdd(&friendsSet, &name)) free(name);
* ----------------
* Adds the specified element to the set if not already present.
* present, the client element is not copied into the set. true
* is returned if and only if the element at address elemPtr
* was copied into the set.
*/
bool SetAdd(sortedset* set, const void* elemPtr) {
    int* node = FindNode(set, elem);
    if(*node != -1){
        return false;
    }
    if(set->allocLen == set->logLen){
        set->allocLen *= 2;
        set->root = realloc(set->root, 1 + set->allocLen * (sizeof(int) * 2 + set->elemSize));
        assert(set->root != NULL);
    }
    int* last = (char*)(set->root + 1) + set->allocLen * (set->elemSize + sizeof(int) * 2);
    *node = set->logLen++;
    memcpy(end, elemPtr, set->elemSize);
    int* arr = end + set->elemSize;
    arr[0] = -1;
    arr[1] = -1;
    return true;
}
