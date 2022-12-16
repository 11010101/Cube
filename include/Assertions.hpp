#ifndef __ASSERTIONS_HPP__
#define __ASSERTIONS_HPP__

#include <iostream>

#ifdef assert(x, ...)
#undef assert(x, ...)
#endif /* assert(x, ...) */

#define assert(cond, ...)							\
		do {										\
				if((cond)){							\
					fprintf(stderr, __VA_ARGS__);	\
					exit(1);					\
				} else {							\
					break;							\
				}									\
		}while(0)

#define error(...)							 \
			do {							 \
				fprintf(stderr, __VA_ARGS__);\
				exit(1);				 \
			}while(0)

#endif /* __ASSERTIONS_HPP__ */