mem-manager
===========

A small c library to free the developers from memory management problems.

Abstract
========

This is a c library to do the memory management activities in c code.

Generally, its a big headache to allocate the memory, keep track of it and
free the memory when not in use. The memory allocated by malloc function
must be freed while exiting the program, otherwise it can result into memory
leaks.

This library provides functions to allocate and free memory that when used
in code can reduce the effort required by developers to manage memory.
The developers only have to initiate the MemoryManager once at the start
of the program and then they can allocate memory using MemoryManagers builtin
functions. At the end of the program, developers just have to call cleanup()
of MemoryManager and it will do the rest for you.

Developed By : ViRaNiAc!
License      : Apache V2

Usage Instructions
==================

The mem-manager library exposes a structure named as MemoryManager to the
programs that can be used to allocate and free memory space as and when
required. In case where developers forgets to free the memory or is not clear
when to free the allocated memory, they can use the cleanup method of the 
MemoryManager to clean all the allocated memory spaces at the end of the program
or the function.

To get an instance of the MemoryManager, following method can be used.


	#include "MemoryManager.h"

	MemoryManager * getMemoryManager(void);


This is the factory function that initiates and returns the MemoryManager
structure. This structure exposes the following method 

malloc - Allocates a block of memory of the specified size. Returns a null 
pointer if memory is not available


	void * malloc(MemoryManager *self, size_t size);


calloc - Allocates a block of memory of the specified size and initializes
the memory space to zero. Returns null if the memory space is not available


	void * calloc(MemoryManager *self, size_t num, size_t size);


realloc - resizes allready allocated block of memory. Acts as malloc if the
passed pointer is pointing to null.


	void * realloc(MemoryManager *self, void * ptr, size_t size);


free - Frees the allocated memory and changes the pointer to point at null


	void free(MemoryManager *self, void **ptr);


cleanup - Frees all the allocated memory and deallocates the memory assigned
to MemoryManager as well. This makes the pointer to the Memory Manager 
structure to point to null.

Once this method is used, Memory Manager structure needs to be initialized 
again for any further use.


	void cleanup(MemoryManager **self);


The name and prototypes of these functions are purposefully kept similar to
the standard c libraries memory management functions to make it easy to use
these libraries into c projects without needing any special learning curve.

Example Code
============

```c
#include <string.h>
#include "MemoryManager.h"

int main(){
    void *ptr;
    MemoryManager *mm;

    // instantiate MemoryManager structure
    mm = getMemoryManager();

    // allocate 10 bytes of memory to ptr
    // its necessary to pass the memory manager instance here
    ptr = mm->malloc(mm, 10);		// ptr is now pointing to some address

    // Lets free some memory
    // we have to pass the address of the pointer variable
    mm->free(mm, &ptr);			// ptr is now a null pointer
    
    // Lets allocate some memory again. This time using calloc
    ptr = mm->calloc(mm, 10, sizeof(char));	//ptr is pointing to 10 \0 chars

    // Lets resize the memory again
    ptr = mm->realloc(mm, ptr, 5);		//ptr is now 5 bytes

    // Lets cleanup and exit
    mm->cleanup(&mm);	// will free all memory and initialize mm to null

    return 0;   
}

```
Developers can create multiple instances of MemoryManager if the want to seperate
the management of memory in different sections of code. 

MemoryManager instances can be passed to different functions. This eliminates the
need to create seperate MemoryManager instances in different functions.

Note: MemoryManager uses linked list to keep track of memory allocated using its
instance. it won't be able to free memory thats allocated without using Memory 
Manager instance. 
