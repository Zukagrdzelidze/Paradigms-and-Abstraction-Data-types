#include "multitable.h"

void MultiTableNew(multitable *mt, int keySizeInBytes, int valueSizeInBytes, int numBuckets, MultiTableHashFunction hash, MultiTableCompareFunction compare){
    mt->keySize = keySizeInBytes;
    mt->valueSize = valueSizeInBytes;
    HashSetNew(&mt->mappings, keySizeInBytes + sizeof(vector), numBuckets,hash, compare, NULL);
}


void MultiTableEnter(multitable *mt, const void *keyAddr, const void *valueAddr){
    void * elem = HashSetLookup(&mt->mappings, keyAddr);

    if (elem ==  NULL){
        char newElem[mt->keySize + sizeof(vector)];
        memcpy(newElem, keyAddr, mt->keySize);
        vector * vec = newElem + mt->keySize;
        VectorNew(vec, mt->valueSize, NULL, 1);
        VectorAppend(vec, valueAddr);
        HashSetEnter(&mt->mappings, newElem);
    }else{
        vector * vec = (char *)elem + mt->keySize;
        VectorAppend(vec, valueAddr);
    }
}

typedef struct{
    void * auxData;
    int keySize;
    MultiTableMapFunction map;
}mapHelper;


void hashsetMapFunc(void * elemAddr, void * auxData){
    mapHelper * helper = (mapHelper *)auxData;
    vector * vec = (char *)elemAddr + helper->keySize;
    for (int i = 0; i < VectorLength(vec); i++){
        void * valueAddr = VectorNth(vec, i);
        helper->map(elemAddr, valueAddr, helper->auxData);
    }
}

void MultiTableMap(multitable *mt, MultiTableMapFunction map, void *auxData){
    mapHelper helper = {auxData, mt->keySize, map};
    HashSetMap(&mt->mappings, hashsetMapFunc, &helper);
}




void ListRecordsInRange(multitable *zipCodes, char *low, char *high)
{
    char *endpoints[] = {low, high};
    MultiTableMap(zipCodes, InRangePrint, endpoints);
}

static void InRangePrint(void *keyAddr, void *valueAddr, void *auxData){
    char *zipcode = (char *)keyAddr;
    char *city = *(char **)valueAddr;
    char ** endpoints = (char **)auxData;
    char *low = endpoints[0]; // *(char **)auxData;
    char *high = endpoints[1]; // *((char **)auxData + 1)

    if ((strcmp(zipcode, low) >= 0) && (strcmp(zipcode, high) <= 0))
        printf("%5s: %s\n", zipcode, city);
}