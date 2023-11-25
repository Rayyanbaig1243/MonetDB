/*
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2023 MonetDB B.V.
 */

#ifndef _SQL_MEM_H_
#define _SQL_MEM_H_

#include "gdk.h"
#include "exception_buffer.h"

#define SQL_OK 	1
#define SQL_ERR 0
#define SQL_CONFLICT 2

#ifdef WIN32
#ifdef LIBSQL
#define sql_export extern __declspec(dllexport)
#else
#define sql_export extern __declspec(dllimport)
#endif
#else
#define sql_export extern
#endif

#define MNEW( type ) (type*)GDKmalloc(sizeof(type) )
#define ZNEW( type ) (type*)GDKzalloc(sizeof(type) )
#define NEW_ARRAY( type, size ) (type*)GDKmalloc((size)*sizeof(type))
#define ZNEW_ARRAY( type, size ) (type*)GDKzalloc((size)*sizeof(type))
#define RENEW_ARRAY( type,ptr,size) (type*)GDKrealloc((void*)ptr,(size)*sizeof(type))

#define _DELETE( ptr )	do { GDKfree(ptr); ptr = NULL; } while (0)
#define _STRDUP( ptr )	GDKstrdup((char*)ptr)

typedef struct allocator {
	struct allocator *pa;
	size_t size;
	size_t nr;
	char **blks;
	size_t used; 	/* memory used in last block */
	size_t usedmem;	/* used memory */
	void *freelist;	/* list of freed blocks */
	exception_buffer eb;
} allocator;

sql_export allocator *sa_create( allocator *pa );
sql_export allocator *sa_reset( allocator *sa );
sql_export void *sa_alloc( allocator *sa,  size_t sz );
sql_export void *sa_zalloc( allocator *sa,  size_t sz );
extern void *sa_realloc( allocator *sa,  void *ptr, size_t sz, size_t osz );
extern void sa_destroy( allocator *sa );
extern char *sa_strndup( allocator *sa, const char *s, size_t l);
sql_export char *sa_strdup( allocator *sa, const char *s);
extern char *sa_strconcat( allocator *sa, const char *s1, const char *s2);
extern size_t sa_size( allocator *sa );

#define SA_NEW( sa, type ) (sa?((type*)sa_alloc( sa, sizeof(type))):MNEW(type))
#define SA_ZNEW( sa, type ) (sa?((type*)sa_zalloc( sa, sizeof(type))):ZNEW(type))
#define SA_NEW_ARRAY( sa, type, size ) (sa?(type*)sa_alloc( sa, ((size)*sizeof(type))):NEW_ARRAY(type,size))
#define SA_ZNEW_ARRAY( sa, type, size ) (type*)sa_zalloc( sa, ((size)*sizeof(type)))
#define SA_RENEW_ARRAY( sa, type, ptr, sz, osz ) (sa?(type*)sa_realloc( sa, ptr, ((sz)*sizeof(type)), ((osz)*sizeof(type))):RENEW_ARRAY(type,ptr,sz))
#define SA_STRDUP( sa, s) (sa?sa_strdup(sa, s):_STRDUP(s))

#define _strlen(s) (int)strlen(s)

#if !defined(NDEBUG) && !defined(__COVERITY__) && defined(__GNUC__)
#define sa_alloc(sa, sz)					\
	({							\
		allocator *_sa = (sa);			\
		size_t _sz = (sz);				\
		void *_res = sa_alloc(_sa, _sz);		\
		TRC_DEBUG(ALLOC,				\
				"sa_alloc(%p,%zu) -> %p\n",	\
				_sa, _sz, _res);	\
		_res;						\
	})
#define sa_zalloc(sa, sz)					\
	({							\
		allocator *_sa = (sa);			\
		size_t _sz = (sz);				\
		void *_res = sa_zalloc(_sa, _sz);		\
		TRC_DEBUG(ALLOC,				\
				"sa_zalloc(%p,%zu) -> %p\n",	\
				_sa, _sz, _res);	\
		_res;						\
	})
#define sa_realloc(sa, ptr, sz, osz)					\
	({								\
		allocator *_sa = (sa);				\
		void *_ptr = (ptr);					\
		size_t _sz = (sz);					\
		size_t _osz = (osz);					\
		void *_res = sa_realloc(_sa, _ptr, _sz, _osz);		\
		TRC_DEBUG(ALLOC,				\
				"sa_realloc(%p,%p,%zu,%zu) -> %p\n",	\
				_sa, _ptr, _sz, _osz, _res);		\
		_res;							\
	})
#define sa_strdup(sa, s)					\
	({							\
		allocator *_sa = (sa);			\
		const char *_s = (s);				\
		char *_res = sa_strdup(_sa, _s);		\
		TRC_DEBUG(ALLOC,				\
				"sa_strdup(%p,len=%zu) -> %p\n",	\
				_sa, strlen(_s), _res);	\
		_res;						\
	})
#define sa_strndup(sa, s, l)					\
	({							\
		allocator *_sa = (sa);			\
		const char *_s = (s);				\
		size_t _l = (l);				\
		char *_res = sa_strndup(_sa, _s, _l);		\
		TRC_DEBUG(ALLOC,				\
				"sa_strndup(%p,len=%zu) -> %p\n", 	\
				_sa, _l, _res);		\
		_res;						\
	})
#endif

#endif /*_SQL_MEM_H_*/
