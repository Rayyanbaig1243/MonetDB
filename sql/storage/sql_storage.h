/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2020 MonetDB B.V.
 */

#ifndef SQL_STORAGE_H
#define SQL_STORAGE_H

#include "sql_catalog.h"
#include "store_sequence.h"

#define COLSIZE	1024

#define LOG_OK		0
#define LOG_ERR		(-1)

#define isTemp(x) (isNew((x)->t)||(x)->t->persistence!=SQL_PERSIST)
#define isTempTable(x)   ((x)->persistence!=SQL_PERSIST)
#define isGlobal(x)      ((x)->persistence!=SQL_LOCAL_TEMP && (x)->persistence!=SQL_DECLARED_TABLE)
#define isGlobalTemp(x)  ((x)->persistence==SQL_GLOBAL_TEMP)
#define isTempSchema(x)  (strcmp((x)->base.name, "tmp") == 0)
#define isDeclaredTable(x)  ((x)->persistence==SQL_DECLARED_TABLE)

extern int catalog_version;

typedef enum store_type {
	store_bat,	/* delta bats, ie multi user read/write */
	store_tst,
	store_mem
} store_type;

#define STORE_READONLY (store_readonly)

/* builtin functions have ids less than this */
#define FUNC_OIDS 2000

extern sql_trans *gtrans;
extern list *active_sessions;
extern ATOMIC_TYPE store_nr_active;
extern store_type active_store_type;
extern int store_readonly;
extern int store_singleuser;
extern int store_initialized;

/* relational interface */
typedef oid (*column_find_row_fptr)(sql_trans *tr, sql_column *c, const void *value, ...);
typedef void *(*column_find_value_fptr)(sql_trans *tr, sql_column *c, oid rid);
typedef sqlid (*column_find_sqlid_fptr)(sql_trans *tr, sql_column *c, oid rid);
typedef int (*column_find_int_fptr)(sql_trans *tr, sql_column *c, oid rid);
typedef int (*column_update_value_fptr)(sql_trans *tr, sql_column *c, oid rid, void *value);
typedef int (*table_insert_fptr)(sql_trans *tr, sql_table *t, ...);
typedef int (*table_delete_fptr)(sql_trans *tr, sql_table *t, oid rid);
typedef int (*table_vacuum_fptr)(sql_trans *tr, sql_table *t);

typedef struct rids {
	BUN cur;
	void *data;
} rids;

typedef struct subrids {
	BUN pos;
	sqlid id;
	void *ids;
	void *rids;
} subrids;

/* returns table rids, for the given select ranges */
typedef rids *(*rids_select_fptr)( sql_trans *tr, sql_column *key, const void *key_value_low, const void *key_value_high, ...);

/* order rids by orderby_column values */
typedef rids *(*rids_orderby_fptr)( sql_trans *tr, rids *r, sql_column *orderby_col);

typedef rids *(*rids_join_fptr)( sql_trans *tr, rids *l, sql_column *lc, rids *r, sql_column *rc);
typedef rids *(*rids_diff_fptr)( sql_trans *tr, rids *l, sql_column *lc, subrids *r, sql_column *rc);

/* return table rids from result of table_select, return (-1) when done */
typedef oid (*rids_next_fptr)(rids *r);

/* clean up the resources taken by the result of table_select */
typedef void (*rids_destroy_fptr)(rids *r);
typedef int (*rids_empty_fptr)(rids *r);

typedef subrids *(*subrids_create_fptr)( sql_trans *tr, rids *l, sql_column *jc1, sql_column *jc2, sql_column *obc);

/* return table rids from result of table_select, return (-1) when done */
typedef oid (*subrids_next_fptr)(subrids *r);
typedef sqlid (*subrids_nextid_fptr)(subrids *r);

/* clean up the resources taken by the result of table_select */
typedef void (*subrids_destroy_fptr)(subrids *r);

typedef struct table_functions {
	column_find_row_fptr column_find_row;
	column_find_value_fptr column_find_value;
	column_find_sqlid_fptr column_find_sqlid;
	column_find_int_fptr column_find_int;
	column_update_value_fptr column_update_value;
	table_insert_fptr table_insert;
	table_delete_fptr table_delete;
	table_vacuum_fptr table_vacuum;

	rids_select_fptr rids_select;
	rids_orderby_fptr rids_orderby;
	rids_join_fptr rids_join;
	rids_next_fptr rids_next;
	rids_destroy_fptr rids_destroy;
	rids_empty_fptr rids_empty;

	subrids_create_fptr subrids_create;
	subrids_next_fptr subrids_next;
	subrids_nextid_fptr subrids_nextid;
	subrids_destroy_fptr subrids_destroy;
	rids_diff_fptr rids_diff;
} table_functions;

sqlstore_export table_functions table_funcs;

/* delta table setup (ie readonly col + ins + upd + del)
-- binds for column,idx (rdonly, inserts, updates) and delets
*/
typedef void *(*bind_col_fptr) (sql_trans *tr, sql_column *c, int access);
typedef void *(*bind_idx_fptr) (sql_trans *tr, sql_idx *i, int access);
typedef void *(*bind_del_fptr) (sql_trans *tr, sql_table *t, int access);

/*
-- binds data for column, idx and delets (from the parent transaction)
*/
typedef void *(*bind_col_data_fptr) (sql_trans *tr, sql_column *c);
typedef void *(*bind_idx_data_fptr) (sql_trans *tr, sql_idx *i);
typedef void *(*bind_del_data_fptr) (sql_trans *tr, sql_table *t);

/*
-- append/update to columns and indices
*/
typedef int (*append_col_fptr) (sql_trans *tr, sql_column *c, size_t offset, void *d, int t);
typedef int (*append_idx_fptr) (sql_trans *tr, sql_idx *i, size_t offset, void *d, int t);
typedef int (*update_col_fptr) (sql_trans *tr, sql_column *c, void *tids, void *d, int t);
typedef int (*update_idx_fptr) (sql_trans *tr, sql_idx *i, void *tids, void *d, int t);
typedef int (*delete_tab_fptr) (sql_trans *tr, sql_table *t, void *d, int tpe);
typedef size_t (*claim_tab_fptr) (sql_trans *tr, sql_table *t, size_t cnt);

/*
-- count number of rows in column (excluding the deletes)
-- check for sortedness
 */
typedef size_t (*count_del_fptr) (sql_trans *tr, sql_table *t, int upd);
typedef size_t (*count_col_fptr) (sql_trans *tr, sql_column *c, int upd);
typedef size_t (*count_idx_fptr) (sql_trans *tr, sql_idx *i, int upd);
typedef size_t (*dcount_col_fptr) (sql_trans *tr, sql_column *c);
typedef int (*prop_col_fptr) (sql_trans *tr, sql_column *c);

/*
-- create the necessary storage resources for columns, indices and tables
-- returns LOG_OK, LOG_ERR
*/
typedef int (*create_col_fptr) (sql_trans *tr, sql_column *c);
typedef int (*create_idx_fptr) (sql_trans *tr, sql_idx *i);
typedef int (*create_del_fptr) (sql_trans *tr, sql_table *t);

/*
-- upgrade the necessary storage resources for columns, indices and tables
-- needed for the upgrade of the logger structure (ie user tables are
-- now stored using the object ids, no longer the names). This allows
-- renames.
-- returns LOG_OK, LOG_ERR
*/
typedef int (*upgrade_col_fptr) (sql_column *c);
typedef int (*upgrade_idx_fptr) (sql_idx *i);
typedef int (*upgrade_del_fptr) (sql_table *t);

/*
-- duplicate the necessary storage resources for columns, indices and tables
-- returns LOG_OK, LOG_ERR
*/
typedef int (*dup_col_fptr) (sql_trans *tr, sql_column *oc, sql_column *c);
typedef int (*dup_idx_fptr) (sql_trans *tr, sql_idx *oi, sql_idx *i );
typedef int (*dup_del_fptr) (sql_trans *tr, sql_table *ot, sql_table *t);

/*
-- free the storage resources for columns, indices and tables
-- returns LOG_OK, LOG_ERR
*/
typedef int (*destroy_col_fptr) (sql_trans *tr, sql_column *c);
typedef int (*destroy_idx_fptr) (sql_trans *tr, sql_idx *i);
typedef int (*destroy_del_fptr) (sql_trans *tr, sql_table *t);

/*
-- clear any storage resources for columns, indices and tables
-- returns number of removed tuples
*/
typedef int (*clear_table_fptr) (sql_trans *tr, sql_table *t);

/*
-- update_table rollforward the changes made from table ft to table tt
-- returns LOG_OK, LOG_ERR
*/
typedef int (*update_table_fptr) (sql_trans *tr, sql_table *ft, sql_table *tt);

/*
-- gtrans_update push ibats and ubats
-- returns LOG_OK, LOG_ERR
*/
typedef int (*gtrans_update_fptr) (sql_trans *tr);

/*
-- handle deletes
-- returns LOG_OK, LOG_ERR
*/
typedef int (*cleanup_fptr) ();

/* backing struct for this interface */
typedef struct store_functions {

	bind_col_fptr bind_col;
	bind_idx_fptr bind_idx;
	bind_del_fptr bind_del;

	bind_col_data_fptr bind_col_data;
	bind_idx_data_fptr bind_idx_data;
	bind_del_data_fptr bind_del_data;

	append_col_fptr append_col;
	append_idx_fptr append_idx;
	update_col_fptr update_col;
	update_idx_fptr update_idx;
	delete_tab_fptr delete_tab;
	claim_tab_fptr claim_tab;

	count_del_fptr count_del;
	count_col_fptr count_col;
	count_idx_fptr count_idx;
	dcount_col_fptr dcount_col;
	prop_col_fptr sorted_col;
	prop_col_fptr unique_col;
	prop_col_fptr double_elim_col; /* varsize col with double elimination */

	create_col_fptr create_col;
	create_idx_fptr create_idx;
	create_del_fptr create_del;

	dup_col_fptr dup_col;
	dup_idx_fptr dup_idx;
	dup_del_fptr dup_del;

	destroy_col_fptr destroy_col;
	destroy_idx_fptr destroy_idx;
	destroy_del_fptr destroy_del;

	/* functions for logging */
	create_col_fptr log_create_col;
	create_idx_fptr log_create_idx;
	create_del_fptr log_create_del;

	destroy_col_fptr log_destroy_col;
	destroy_idx_fptr log_destroy_idx;
	destroy_del_fptr log_destroy_del;

	clear_table_fptr clear_table;
	update_table_fptr log_table;
	update_table_fptr update_table;
	gtrans_update_fptr gtrans_minmax;

	cleanup_fptr cleanup;
} store_functions;

sqlstore_export store_functions store_funcs;

typedef int (*logger_create_fptr) (int debug, const char *logdir, int catalog_version);
typedef void (*logger_destroy_fptr) (void);
typedef int (*logger_flush_fptr) (void);

typedef int (*logger_changes_fptr)(void);
typedef int (*logger_get_sequence_fptr) (int seq, lng *id);

typedef int (*log_isnew_fptr)(void);
typedef int (*log_tstart_fptr) (void);
typedef int (*log_tend_fptr) (void);
typedef int (*log_sequence_fptr) (int seq, lng id);

/*
-- List which parts of which files must be included in a hot snapshot.
-- This is written to the given stream in the following format:
-- - The first line is the absolute path of the db dir. All other paths
--   are relative to this.
-- - Every other line is either "c %ld %s\n" or "w %ld %s\n". The long
--   is always the number of bytes to write. The %s is the relative path of the
--   destination. For "c" lines (copy), it is also the relative path of the
--   source file. For "w" lines (write), the %ld bytes to write follow directly
--   after the newline.
-- Using a stream (buffer) instead of a list data structure simplifies debugging
-- and avoids a lot of tiny allocations and pointer manipulations.
*/
typedef gdk_return (*logger_get_snapshot_files_fptr)(stream *plan);

typedef struct logger_functions {
	logger_create_fptr create;
	logger_destroy_fptr destroy;
	logger_flush_fptr flush;

	logger_changes_fptr changes;
	logger_get_sequence_fptr get_sequence;

	logger_get_snapshot_files_fptr get_snapshot_files;

	log_isnew_fptr log_isnew;
	log_tstart_fptr log_tstart;
	log_tend_fptr log_tend;
	log_sequence_fptr log_sequence;
} logger_functions;

sqlstore_export logger_functions logger_funcs;

/* we need to add an interface for result_tables later */

extern res_table *res_table_create(sql_trans *tr, int res_id, oid query_id, int nr_cols, mapi_query_t querytype, res_table *next, void *order);
extern res_col *res_col_create(sql_trans *tr, res_table *t, const char *tn, const char *name, const char *typename, int digits, int scale, int mtype, void *v);

extern void res_table_destroy(res_table *t);

extern res_table *res_tables_remove(res_table *results, res_table *t);
sql_export void res_tables_destroy(res_table *results);
extern res_table *res_tables_find(res_table *results, int res_id);

extern int store_init(sql_allocator *pa, int debug, store_type store, int readonly, int singleuser);
extern void store_exit(void);

extern void store_suspend_log(void);
extern void store_resume_log(void);
extern lng store_hot_snapshot(str tarfile);
extern lng store_hot_snapshot_to_stream(stream *s);

extern void store_manager(void);
//extern void idle_manager(void);

extern void store_lock(void);
extern void store_unlock(void);
extern sqlid store_next_oid(void);

extern sql_trans *sql_trans_create(sql_trans *parent, const char *name, bool try_spare);
extern sql_trans *sql_trans_destroy(sql_trans *tr, bool try_spare);
extern bool sql_trans_validate(sql_trans *tr);
extern int sql_trans_commit(sql_trans *tr);

extern sql_type *sql_trans_create_type(sql_trans *tr, sql_schema *s, const char *sqlname, int digits, int scale, int radix, const char *impl);
extern int sql_trans_drop_type(sql_trans *tr, sql_schema * s, sqlid id, int drop_action);

extern sql_func *sql_trans_create_func(sql_trans *tr, sql_schema *s, const char *func, list *args, list *res, sql_ftype type, sql_flang lang, const char *mod, const char *impl, const char *query, bit varres, bit vararg, bit system);

extern int sql_trans_drop_func(sql_trans *tr, sql_schema *s, sqlid id, int drop_action);
extern int sql_trans_drop_all_func(sql_trans *tr, sql_schema *s, list *list_func, int drop_action);

extern void sql_trans_update_tables(sql_trans *tr, sql_schema *s);
extern void sql_trans_update_schemas(sql_trans *tr);

extern void reset_functions(sql_trans *tr);

extern sql_schema *sql_trans_create_schema(sql_trans *tr, const char *name, sqlid auth_id, sqlid owner);
extern sql_schema *sql_trans_rename_schema(sql_trans *tr, sqlid id, const char *new_name);
extern int sql_trans_drop_schema(sql_trans *tr, sqlid id, int drop_action);

extern sql_table *sql_trans_create_table(sql_trans *tr, sql_schema *s, const char *name, const char *sql, int tt, bit system, int persistence, int commit_action, int sz, bit properties);

extern int sql_trans_set_partition_table(sql_trans *tr, sql_table *t);
extern sql_table *sql_trans_add_table(sql_trans *tr, sql_table *mt, sql_table *pt);
extern int sql_trans_add_range_partition(sql_trans *tr, sql_table *mt, sql_table *pt, sql_subtype tpe, ptr min, ptr max, bit with_nills, int update, sql_part** err);
extern int sql_trans_add_value_partition(sql_trans *tr, sql_table *mt, sql_table *pt, sql_subtype tpe, list* vals, bit with_nills, int update, sql_part **err);

extern sql_table *sql_trans_rename_table(sql_trans *tr, sql_schema *s, sqlid id, const char *new_name);
extern sql_table *sql_trans_set_table_schema(sql_trans *tr, sqlid id, sql_schema *os, sql_schema *ns);
extern sql_table *sql_trans_del_table(sql_trans *tr, sql_table *mt, sql_table *pt, int drop_action);

extern int sql_trans_drop_table(sql_trans *tr, sql_schema *s, sqlid id, int drop_action);
extern BUN sql_trans_clear_table(sql_trans *tr, sql_table *t);
extern sql_table *sql_trans_alter_access(sql_trans *tr, sql_table *t, sht access);

extern sql_column *sql_trans_create_column(sql_trans *tr, sql_table *t, const char *name, sql_subtype *tpe);
extern sql_column *sql_trans_rename_column(sql_trans *tr, sql_table *t, const char *old_name, const char *new_name);
extern int sql_trans_drop_column(sql_trans *tr, sql_table *t, sqlid id, int drop_action);
extern sql_column *sql_trans_alter_null(sql_trans *tr, sql_column *col, int isnull);
extern sql_column *sql_trans_alter_default(sql_trans *tr, sql_column *col, char *val);
extern sql_column *sql_trans_alter_storage(sql_trans *tr, sql_column *col, char *storage);
extern int sql_trans_is_sorted(sql_trans *tr, sql_column *col);
extern int sql_trans_is_unique(sql_trans *tr, sql_column *col);
extern int sql_trans_is_duplicate_eliminated(sql_trans *tr, sql_column *col);
extern size_t sql_trans_dist_count(sql_trans *tr, sql_column *col);
extern int sql_trans_ranges(sql_trans *tr, sql_column *col, char **min, char **max);

extern sql_key *sql_trans_create_ukey(sql_trans *tr, sql_table *t, const char *name, key_type kt);
extern sql_key * sql_trans_key_done(sql_trans *tr, sql_key *k);

extern sql_fkey *sql_trans_create_fkey(sql_trans *tr, sql_table *t, const char *name, key_type kt, sql_key *rkey, int on_delete, int on_update);
extern sql_key *sql_trans_create_kc(sql_trans *tr, sql_key *k, sql_column *c /*, extra options such as trunc */ );
extern sql_fkey *sql_trans_create_fkc(sql_trans *tr, sql_fkey *k, sql_column *c /*, extra options such as trunc */ );
extern int sql_trans_drop_key(sql_trans *tr, sql_schema *s, sqlid id, int drop_action);

extern sql_idx *sql_trans_create_idx(sql_trans *tr, sql_table *t, const char *name, idx_type it);
extern sql_idx *sql_trans_create_ic(sql_trans *tr, sql_idx * i, sql_column *c /*, extra options such as trunc */ );
extern int sql_trans_drop_idx(sql_trans *tr, sql_schema *s, sqlid id, int drop_action);

extern sql_trigger * sql_trans_create_trigger(sql_trans *tr, sql_table *t, const char *name, sht time, sht orientation, sht event, const char *old_name, const char *new_name, const char *condition, const char *statement );
extern sql_trigger * sql_trans_create_tc(sql_trans *tr, sql_trigger * i, sql_column *c /*, extra options such as trunc */ );
extern int sql_trans_drop_trigger(sql_trans *tr, sql_schema *s, sqlid id, int drop_action);

extern sql_sequence *create_sql_sequence(sql_allocator *sa, sql_schema *s, const char *name, lng start, lng min, lng max, lng inc, lng cacheinc, bit cycle);
extern sql_sequence * sql_trans_create_sequence(sql_trans *tr, sql_schema *s, const char *name, lng start, lng min, lng max, lng inc, lng cacheinc, bit cycle, bit bedropped);
extern void sql_trans_drop_sequence(sql_trans *tr, sql_schema *s, sql_sequence *seq, int drop_action);
extern sql_sequence *sql_trans_alter_sequence(sql_trans *tr, sql_sequence *seq, lng min, lng max, lng inc, lng cache, bit cycle);
extern sql_sequence *sql_trans_sequence_restart(sql_trans *tr, sql_sequence *seq, lng start);
extern sql_sequence *sql_trans_seqbulk_restart(sql_trans *tr, seqbulk *sb, lng start);

extern sql_session * sql_session_create(int autocommit);
extern void sql_session_destroy(sql_session *s);
extern int sql_session_reset(sql_session *s, int autocommit);
extern int sql_trans_begin(sql_session *s);
extern void sql_trans_end(sql_session *s, int commit /* rollback=0, or commit=1 temporaries */);

extern list* sql_trans_schema_user_dependencies(sql_trans *tr, sqlid schema_id);
extern void sql_trans_create_dependency(sql_trans *tr, sqlid id, sqlid depend_id, sql_dependency depend_type);
extern void sql_trans_drop_dependencies(sql_trans *tr, sqlid depend_id);
extern void sql_trans_drop_dependency(sql_trans *tr, sqlid id, sqlid depend_id, sql_dependency depend_type);
extern list* sql_trans_get_dependencies(sql_trans *tr, sqlid id, sql_dependency depend_type, list *ignore_ids);
extern int sql_trans_get_dependency_type(sql_trans *tr, sqlid depend_id, sql_dependency depend_type);
extern int sql_trans_check_dependency(sql_trans *tr, sqlid id, sqlid depend_id, sql_dependency depend_type);
extern list* sql_trans_owner_schema_dependencies(sql_trans *tr, sqlid id);

extern sql_table *create_sql_table(sql_allocator *sa, const char *name, sht type, bit system, int persistence, int commit_action, bit properties);
extern sql_column *create_sql_column(sql_trans *tr, sql_table *t, const char *name, sql_subtype *tpe);
extern sql_ukey *create_sql_ukey(sql_allocator *sa, sql_table *t, const char *nme, key_type kt);
extern sql_fkey *create_sql_fkey(sql_allocator *sa, sql_table *t, const char *nme, key_type kt, sql_key *rkey, int on_delete, int on_update );
extern sql_key *create_sql_kc(sql_allocator *sa, sql_key *k, sql_column *c);
extern sql_key * key_create_done(sql_allocator *sa, sql_key *k);

extern sql_idx *create_sql_idx(sql_allocator *sa, sql_table *t, const char *nme, idx_type it);
extern sql_idx *create_sql_ic(sql_allocator *sa, sql_idx *i, sql_column *c);
extern sql_func *create_sql_func(sql_allocator *sa, const char *func, list *args, list *res, sql_ftype type, sql_flang lang, const char *mod, const char *impl, const char *query, bit varres, bit vararg, bit system);

/* for alter we need to duplicate a table */
extern sql_table *dup_sql_table(sql_allocator *sa, sql_table *t);
extern void drop_sql_column(sql_table *t, sqlid id, int drop_action);
extern void drop_sql_idx(sql_table *t, sqlid id);
extern void drop_sql_key(sql_table *t, sqlid id, int drop_action);

extern sql_column *sql_trans_copy_column(sql_trans *tr, sql_table *t, sql_column *c);
extern sql_key *sql_trans_copy_key(sql_trans *tr, sql_table *t, sql_key *k);
extern sql_idx *sql_trans_copy_idx(sql_trans *tr, sql_table *t, sql_idx *i);
extern sql_trigger *sql_trans_copy_trigger(sql_trans *tr, sql_table *t, sql_trigger *tri);
extern sql_part *sql_trans_copy_part(sql_trans *tr, sql_table *t, sql_part *pt);

extern void sql_trans_drop_any_comment(sql_trans *tr, sqlid id);
extern void sql_trans_drop_obj_priv(sql_trans *tr, sqlid obj_id);

/* This function should be used in exceptional cases such as dealing with tricky upgrades! */
extern void insert_functions(sql_trans *tr, sql_table *sysfunc, list *funcs_list, sql_table *sysarg);

#endif /*SQL_STORAGE_H */
