#include "MemoryManager.h"

/*
**
** This is a c library to do the memory management activities in c code.
**
** Generally, its a big headache to allocate the memory, keep track of it and
** free the memory when not in use. The memory allocated by malloc function
** must be freed while exiting the program, otherwise it can result into memory
** leaks.
**
** This library provides functions to allocate and free memory that when used
** in code can reduce the effort required by developers to manage memory.
** The developers only have to initiate the MemoryManager once at the start
** of the program and then they can allocate memory using MemoryManagers builtin
** functions. At the end of the program, developers just have to call cleanup()
** of MemoryManager and it will do the rest for you.
**
** Developed By : ViRaNiAc!
** License      : Apache V2
**
*/


void * allocate_memory(MemoryManager *self, size_t size){
    void *tmp_address = NULL;
    MemoryEntry *tmp_memory_entry = NULL;

    tmp_address = malloc(size);

    // We only need to proceed if we have some of the requested memory
    if (tmp_address != NULL) {
        tmp_memory_entry = (MemoryEntry *)malloc(sizeof(MemoryEntry));

        // exit if we can't afford to create new memory entry
        if (tmp_memory_entry == NULL) {
            free(tmp_address);
            tmp_address = NULL;
            return tmp_address;
        }

        // initialize memory entry
        tmp_memory_entry->address = tmp_address;
        tmp_memory_entry->next_entry = NULL;

        // Is this the first element in the list
        if (self->last_entry == NULL) {
            self->last_entry = tmp_memory_entry;
            self->entry_list = self->last_entry;
        } else {
            self->last_entry->next_entry = tmp_memory_entry;
            self->last_entry = self->last_entry->next_entry;
        }

    }

    return tmp_address;
}

void * reallocate_memory(MemoryManager *self, void *ptr, size_t size){
    void *tmp = NULL;
    MemoryEntry *tmp_memory_entry = NULL;

    // Search for the pointer in the entry_list
    tmp_memory_entry = self->entry_list;

    while(tmp_memory_entry != NULL && tmp_memory_entry->address != ptr) {
        tmp_memory_entry = tmp_memory_entry->next_entry;
    }

    if (tmp_memory_entry == NULL) {
        tmp = self->malloc(self, size);
    } else {
        tmp_memory_entry->address = realloc(ptr, size);
        tmp = tmp_memory_entry->address;
    }

    return tmp;
}

void * c_allocate_memory(MemoryManager *self, size_t num, size_t size){
    void *tmp_address = NULL;
    MemoryEntry *tmp_memory_entry = NULL;

    tmp_address = calloc(num, size);

    // We only need to proceed if we have some of the requested memory
    if (tmp_address != NULL) {
        tmp_memory_entry = (MemoryEntry *)malloc(sizeof(MemoryEntry));

        // exit if we can't afford to create new memory entry
        if (tmp_memory_entry == NULL) {
            free(tmp_address);
            tmp_address = NULL;
            return tmp_address;
        }

        // initialize memory entry
        tmp_memory_entry->address = tmp_address;
        tmp_memory_entry->next_entry = NULL;

        // Is this the first element in the list
        if (self->last_entry == NULL) {
            self->last_entry = tmp_memory_entry;
            self->entry_list = self->last_entry;
        } else {
            self->last_entry->next_entry = tmp_memory_entry;
            self->last_entry = self->last_entry->next_entry;
        }

    }
    return tmp_address;
}

void free_memory(MemoryManager *self, void **ptr){
    MemoryEntry *tmp = NULL, *prev_ptr = NULL;
    prev_ptr = NULL;

    // Do nothing if the ptr is a null pointer
    if (*ptr == NULL) {
        return;
    }

    // So ptr is not a null pointer lets try to find it in the list
    tmp = self->entry_list;

    while(tmp != NULL && tmp->address != *ptr) {
        prev_ptr = tmp;
        tmp = tmp->next_entry;
    }

    // Have we reached at the end of the list? If yes then we
    // are not responsible for the supplied ptr.
    if (tmp == NULL) {
        return;
    }

    // if ptr is in the list lets remove it
    // Is ptr the first pointer in the list?
    if (tmp == self->entry_list) {
        self->entry_list = tmp->next_entry;
    }

    // Is ptr the last pointer in the list?
    if (tmp == self->last_entry) {
        self->last_entry = prev_ptr;
    }

    // if ptr is somewhere in the middle of the list
    if (prev_ptr != NULL) {
        prev_ptr->next_entry = tmp->next_entry;
    }

    // List is now rearranged. Lets free the memory
    free(tmp->address);
    *ptr = NULL;    
    free(tmp);
}

void cleanup(MemoryManager **self){
    MemoryEntry *tmp = NULL;

    //lets travel through the list detaching elements from the list one by one
    while ((*self)->entry_list != NULL) {
        tmp = (*self)->entry_list;
        (*self)->entry_list = (*self)->entry_list->next_entry;

        // Have we reached the end of the list? if yes we need to fix the tail
        // pointer
        if ((*self)->entry_list == NULL) {
            (*self)->last_entry = NULL;
        }

        //all right, lets free the entry that we detached from the list
        free(tmp->address);
        free(tmp);
    }

    // MemoryManager has lost everything. Committing suicide
    free(*self);
    (*self) = NULL;
}

MemoryManager * getMemoryManager(void){
    MemoryManager *mm = (MemoryManager *) malloc(sizeof(MemoryManager));
    mm->last_entry = NULL;
    mm->entry_list = NULL;
    mm->malloc = allocate_memory;
    mm->realloc = reallocate_memory;
    mm->calloc = c_allocate_memory;
    mm->free = free_memory;
    mm->cleanup = cleanup;
    return mm;
}

