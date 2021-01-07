/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2021 MonetDB B.V.
 */

#ifndef BATSTORAGE_H
#define BATSTORAGE_H

#include "sql_storage.h"
#include "bat_logger.h"

typedef struct column_storage {
	int bid;
	int uibid;		/* bat with positions of updates */
	int uvbid;		/* bat with values of updates */
	int cleared;
	size_t ucnt;		/* number of updates */
	int wtime;		/* time stamp */
} column_storage;

typedef struct sql_delta {
	column_storage cs;
	struct sql_delta *next;	/* possibly older version of the same column/idx */
} sql_delta;

typedef struct segment {
	BUN start;
	BUN end;
	sql_trans *owner;	/* keep which transaction owns this */
	struct segment *next;	/* usualy one should be enough */
} segment;

/* container structure too allow sharing this structure */
typedef struct segments {
	sql_ref r;
	BUN end;		/* current end */
	struct segment *head;
} segments;

typedef struct storage {
	column_storage cs;	/* storage on disk */
	bit cached_cnt;
	size_t cnt;
	size_t ucnt;	/* updates (ie deletes) in this transaction */
	size_t icnt;	/* claimed in the transaction */
	BUN end;		/* end maybe less than the segments indicate */
	segments *segs;	/* local used segements */
	struct storage *next;
} storage;

/* initialize bat storage call back functions interface */
extern void bat_storage_init( store_functions *sf );

extern sql_delta * timestamp_delta( sql_delta *d, int ts);
extern storage * timestamp_dbat( storage *d, int ts);

#endif /*BATSTORAGE_H */

