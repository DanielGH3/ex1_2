#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include "book.h"

struct AdptArray_
{
    int capacity;
    PElement *elements;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
};


PAdptArray CreateAdptArray(COPY_FUNC copy_f, DEL_FUNC del_f, PRINT_FUNC print_f){
    PAdptArray array = (PAdptArray)malloc(sizeof(struct AdptArray_));
    array->elements = (PElement*)malloc(sizeof(PElement));
    array->capacity = 0;
    array->copy_func = copy_f;
    array->del_func = del_f;
    array->print_func = print_f;
    return array;
}

void DeleteAdptArray(PAdptArray array){
    for(int i = 0; i < array->capacity; i++){
        if(array->elements[i] != NULL){
            array->del_func(array->elements[i]);
        }
    }
    free(array->elements);
    free(array);
}

Result SetAdptArrayAt(PAdptArray array, int pos, PElement e){
    if(array->capacity <= pos){
        int last_cap = array->capacity;
        array->elements = (PElement*)realloc(array->elements, sizeof(PElement) * (pos + 1));

        array->capacity = pos + 1;
        for(int i = last_cap; i < pos + 1; i++){
            array->elements[i] = NULL;
        }
    }
    array->elements[pos] = array->copy_func(e);
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray array, int pos){
    if(array->capacity <= pos){
        return NULL;
    }
    if(array->elements[pos] == NULL){
        return NULL;
    }
    return array->copy_func(array->elements[pos]);
}

int GetAdptArraySize(PAdptArray array){
    return array->capacity;
}

void PrintDB(PAdptArray array){
    for(int i = 0; i < array->capacity; i++){
        if(array->elements[i] != NULL){
            array->print_func(array->elements[i]);
        }
    }
}