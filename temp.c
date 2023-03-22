#include "AdptArray.h"
#include <stdlib.h>
#include <book.h>

struct AdptArray_
{
    int capacity;
    PElement* elements;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
};


PAdptArray CreateAdptArray(COPY_FUNC copyf, DEL_FUNC delf, PRINT_FUNC printf){
    PAdptArray array = (PAdptArray)malloc(sizeof(PAdptArray));
    array->elements = (PElement*)malloc(0);
    array->capacity = 0;
    array->copy_func = copyf;
    array->del_func = delf;
    array->print_func = printf;
    return array;
}

void DeleteAdptArray(PAdptArray array){
    for(int i = 0; i < array->capacity; i++){
        array->del_func(array->elements[i]);
    }
    free(array);
}

Result SetAdptArrayAt(PAdptArray array, int pos, PElement e){
    print_book(e);

    if(array->capacity <= pos){
        array->elements = (PElement*)realloc(array->elements, sizeof(PElement) * (pos + 1));
        array->capacity = pos + 1;
        for(int i = 0; i < pos + 1; i++){
            array->elements[i] = NULL;
        }
    }
    array->elements[pos] = e;
    print_book(array->elements[pos]);
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray array, int pos){
    if(array->capacity <= pos){
        return NULL;
    }
    return array->copy_func(array->elements[pos]);
}

int GetAdptArraySize(PAdptArray array){
    return array->capacity;
}

void PrintDB(PAdptArray array){
    for(int i = 0; i < array->capacity; i++){
        array->print_func(array->elements[i]);
    }
}