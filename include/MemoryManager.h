#ifndef MEMORYMANAGER_H_INCLUDED
#define MEMORYMANAGER_H_INCLUDED

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

#include <stdlib.h>

//
// A simple linked list structure to store created pointers

typedef struct memory_entry_t {
    void *address;
    struct memory_entry_t *next_entry;
} MemoryEntry;

//
// MemoryManager structure
//
// Provides functions to allocate/free memory, and cleanup

typedef struct memory_manager_t {
    MemoryEntry *last_entry;
    MemoryEntry *entry_list;
    void (*(*malloc)(struct memory_manager_t *self, size_t size));
    void (*(*calloc)(struct memory_manager_t *self, size_t num, size_t size));
    void (*(*realloc)(struct memory_manager_t *self, void *ptr, size_t size));
    void (*free)(struct memory_manager_t *self, void **ptr);
    void (*cleanup)(struct memory_manager_t **self);
} MemoryManager;

MemoryManager * getMemoryManager(void);

#endif // MEMORYMANAGER_H_INCLUDED
