#include "sparse_string_array.h"



void SSANew(sparsestringarray *ssa, int arrayLength, int groupSize){
    ssa->groupSize = groupSize;
    ssa->arrayLength = arrayLength;
    ssa->numGroups = (ssa->arrayLength - 1) / ssa->groupSize;
    ssa->groups = malloc(sizeof(group) * ssa->numGroups);

    for(int i = 0; i < ssa->numGroups; ++i){
        ssa->groups[i].bitmap = malloc(sizeof(bool) * ssa->groupSize);
        for(int j = 0; j < ssa->groupSize; ++j){
            ssa->groups[i].bitmap[j] = false;
        }
        VectorNew(&ssa->groups[i].strings, sizeof(char*), StringFree, 1);
    } 
}

bool SSAInsert(sparsestringarray *ssa, int index, const char *str){
    int groupIndex = index / ssa->numGroups;
    int bitmapIndex = index % ssa->numGroups;
    
    group * current = &ssa->groups[groupIndex];
    bool isInArray = current->bitmap[bitmapIndex];

    int vecIndex = 0;
    for(int i = 0; i < bitmapIndex; ++i){
        if(current->bitmap[i]){
            vecIndex++;
        }
    }

    char* tmp = strdup(str);

    if(isInArray){
        VectorInsert(&current->string, &tmp, vecIndex);
    }else{
        VectorReplace(&current->string, &tmp, vecIndex);
        current->bitmap[bitmapIndex] = true;
    }

    return !isInArray;
}

void SSAMap(sparsestringarray *ssa, SSAMapFunction mapfn, void *auxData){
    int groupSize = ssa->groupSize;
    for(int i = 0; i < ssa->numGroups; ++i){
        if(ssa->numGroups - 1 == i && ssa->arrayLength % ssa->groupSize){
            groupSize = ssa->arrayLength % ssa->groupSize;
        }
        int vecIndex = 0;
        for(int j = 0; j < groupSize; ++j){
            char* str = "";
            if(ssa->groups[i].bitmap[j]){
                str = *(char**)VectorNth(&ssa->groups[i].string, vecIndex);
                vecIndex++;
            }
            mapfn(i * ssa->groupSize + j, str, auxData);
        }
    }

}

void SSADispose(sparsestringarray *ssa){
    for(int i = 0; i < ssa->numGroups; ++i){
        free(ssa->groups[i].bitmap);
        VectorDispose(&ssa->groups[i].strings)
    }
    free(ssa->groups);
}