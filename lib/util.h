#ifndef UTIL_H
#define UTIL_H

/* Given POINTER, the address of the given MEMBER in a STRUCT object, returns
 *  *    the STRUCT object. */
#define CONTAINER_OF(POINTER, STRUCT, MEMBER)                           \
          ((STRUCT *) (void *) ((char *) (POINTER) - offsetof (STRUCT, MEMBER)))

#endif
