/* Include the system headers we need */
#include <stdio.h>
#include <stdlib.h>

/* Include our header */
#include "vector.h"

/* Define what our struct is */
struct vector_t {
  size_t size;
  int *data;
};

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
static void allocation_failed() {
  fprintf(stderr, "Out of memory.\n");
  exit(1);
}

/* Bad example of how to create a new vector */
/**
 * It's a bad idea using stack memory and return it.
 */
vector_t *bad_vector_new() {
  /* Create the vector and a pointer to it */
  vector_t *retval, v;
  retval = &v;

  /* Initialize attributes */
  retval->size = 1;
  retval->data = malloc(sizeof(int));
  if (retval->data == NULL) {
    allocation_failed();
  }

  retval->data[0] = 0;
  return retval;
}

/* Another suboptimal way of creating a vector */
/**
 * This function works fine actually, but it will re-construct again
 * in the caller function. Sort of ineffective
 */
vector_t also_bad_vector_new() {
  /* Create the vector */
  vector_t v;

  /* Initialize attributes */
  v.size = 1;
  v.data = malloc(sizeof(int));
  if (v.data == NULL) {
    allocation_failed();
  }
  v.data[0] = 0;
  return v;
}

/* Create a new vector with a size (length) of 1
   and set its single component to zero... the
   RIGHT WAY */
vector_t *vector_new() {
  /* Declare what this function will return */
  vector_t *retval;

  /* First, we need to allocate memory on the heap for the struct */
  retval = (vector_t *)malloc(sizeof(vector_t));
  /* Check our return value to make sure we got memory */
  if (retval == NULL) {
    allocation_failed();
  }

  /* Now we need to initialize our data.
     Since retval->data should be able to dynamically grow,
     what do you need to do? */
  retval->size = 1 /* YOUR CODE HERE */;
  retval->data = (int *)malloc(sizeof(int));
  /* Check the data attribute of our vector to make sure we got memory */
  if (retval->data == NULL) {
    free(retval); // Why is this line necessary? // If we don't free retval, it
                  // will cause memory leak
    allocation_failed();
  }

  /* Complete the initialization by setting the single component to zero */
  retval->data[0] = 0;

  /* and return... */
  return retval;
}

/* Return the value at the specified location/component "loc" of the vector */
int vector_get(vector_t *v, size_t loc) {

  /* If we are passed a NULL pointer for our vector, complain about it and exit.
   */
  if (v == NULL) {
    fprintf(stderr, "vector_get: passed a NULL vector.\n");
    abort();
  }

  /* If the requested location is higher than we have allocated, return 0.
   * Otherwise, return what is in the passed location.
   */
  if (loc < v->size) {
    return v->data[loc];
  } else {
    return 0;
  }
}

/* Free up the memory allocated for the passed vector.
   Remember, you need to free up ALL the memory that was allocated. */
void vector_delete(vector_t *v) { /* YOUR SOLUTION HERE */
  // free data attribute of vector
  if (v->size <= 0) {
    fprintf(stderr, "vector_delete: delete an empty vector");
    abort();
  }
  free(v->data);
  free(v);
}

/* Set a value in the vector. If the extra memory allocation fails, call
   allocation_failed(). */
void vector_set(vector_t *v, size_t loc, int value) {
  /* What do you need to do if the location is greater than the size we have
   * allocated?  Remember that unset locations should contain a value of 0.
   */
  if (loc >= v->size) {
    /*  We need to expand the memory */
    int new_size = (v->size << 1);
    while (new_size < loc) {    // Guarantee new_size is large than loc
      new_size <<= 1;
    }
    v->data = (int *)realloc(
        v->data,
        new_size * sizeof(int)); // realloc takes care to release the old one
    if (v->data == NULL) {
      allocation_failed();
    }
    // Initialize new allocated area
    for (int i = v->size; i < new_size; i++) {
      v->data[i] = 0;
    }
    v->size = new_size;
  }

  v->data[loc] = value;
}