/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2020 MonetDB B.V.
 */

#include "monetdb_config.h"

#include <dirent.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include "stream.h"
#include "msabaoth.h"
#include "mapi.h"
#include "snapshot.h"

static time_t parse_snapshot_name(const char *filename, const char *dbname);
static err validate_location(const char *path);
static err unpack_tarstream(stream *tarstream, char *destdir, int skipcomponents);

/* Create a snapshot of database dbname to file dest.
 * TODO: Make it work for databases without monetdb/monetdb root account.
 */
err
snapshot_database_to(char *dbname, char *dest)
{
	err e = NO_ERR;
	sabdb *stats = NULL;
	int port = -1;
	Mapi conn = NULL;
	MapiHdl handle = NULL;


	/* First look up the database in our administration. */
	e = msab_getStatus(&stats, dbname);
	if (e != NO_ERR) {
		goto bailout;
	}
	if (!stats) {
		e = newErr("No such database: '%s'", dbname);
		goto bailout;
	}

	/* Do not overwrite random files on the system. */
	e = validate_location(dest);
	if (e != NO_ERR) {
		goto bailout;
	}

	/* Connect. This is a dirty hack, making two assumptions:
	 * 1. we're listening on localhost
	 * 2. the database has a root user 'monetdb' with password 'monetdb'.
	 * We'll improve this when have figured out how to authenticate.
	 */
	port = getConfNum(_mero_props, "port");
	conn = mapi_connect("localhost", port, "monetdb", "monetdb", "sql", dbname);
	if (conn == NULL || mapi_error(conn)) {
		e = newErr("connection error: %s", mapi_error_str(conn));
		goto bailout;
	}

	/* Trigger the snapshot */
	handle = mapi_prepare(conn, "CALL sys.hot_snapshot(?)");
	if (handle == NULL || mapi_error(conn)) {
		e = newErr("prepare failed: %s", mapi_error_str(conn));
		goto bailout;
	}
	if (mapi_param_string(handle, 0, 12, dest, NULL) != MOK) {
		e = newErr("internal error: mapi_param_string: %s", mapi_error_str(conn));
		goto bailout;
	}
	if (mapi_execute(handle) != MOK) {
		e = newErr("internal error: execute failed: %s", mapi_result_error(handle));
		goto bailout;
	}

	/* everything seems ok. Leave e == NO_ERR */
bailout:
	if (handle != NULL)
		mapi_close_handle(handle);
	if (conn != NULL)
		mapi_destroy(conn);
	if (stats != NULL)
		msab_freeStatus(&stats);
	return e;
}

/* Restore a database from a snapshot file.
 * TODO: Make it work for databases without monetdb/monetdb root account.
 */
err
snapshot_restore_from(char *dbname, char *source)
{
	err e;
	(void)dbname;
	(void)source;
	sabdb *stats = NULL;
	char *dbfarm = NULL;
	char *tmppath = NULL;
	char *destpath = NULL;
	stream *instream = NULL;

	/* Do not read random files on the system. */
	e = validate_location(source);
	if (e != NO_ERR) {
		goto bailout;
	}

	/* For the time being, do not restore existing databases */
	e = msab_getStatus(&stats, dbname);
	if (e != NO_ERR)
		goto bailout;
	if (stats != NULL) {
		e = newErr("database '%s' already exists", dbname);
		goto bailout;
	}

	/* Figure out the directory to create */
	e = msab_getDBfarm(&dbfarm);
	if (e != NO_ERR)
		goto bailout;
	tmppath = malloc(strlen(dbfarm) + strlen(dbname) + 100);
	sprintf(tmppath, "%s/.tmp.%s", dbfarm, dbname);
	destpath = malloc(strlen(dbfarm) + strlen(dbname) + 100);
	sprintf(destpath, "%s/%s", dbfarm, dbname);

	/* Remove the tmp directory, if it exists. */
	e = deletedir(tmppath);
	if (e != NO_ERR)
		goto bailout;

	/* Open the file */
	instream = open_rstream(source);
	if (instream == NULL) {
		e = newErr("Could not open %s", source);
		goto bailout;
	}

	/* Now create the tmp directory */
	if (mkdir(tmppath, 0755) < 0) {
		e = newErr("could not create dir '%s': %s", tmppath, strerror(errno));
		goto bailout;
	}

	/* fill it */
	e = unpack_tarstream(instream, tmppath, 1);
	if (e != NO_ERR)
		goto bailout;

	/* remove whatever's laying around in the destination directory */
	e = deletedir(destpath);
	if (e != NO_ERR)
		goto bailout;

	/* and finally, move the thing into place */
	if (rename(tmppath, destpath) < 0) {
		e = newErr("Couldn't rename '%s' to '%s': %s",
			tmppath, destpath, strerror(errno));
		goto bailout;
	}

bailout:
	if (stats != NULL)
		msab_freeStatus(&stats);
	if (instream != NULL)
		close_stream(instream);
	free(dbfarm);
	free(tmppath);
	free(destpath);
	return e;
}

err
snapshot_list(char *dbname, int *nsnapshots, struct snapshot **snapshots)
{
	err e = NO_ERR;
	DIR *dir = NULL;
	struct dirent *ent;

	/* get the snapdir */
	char *snapdir = getConfVal(_mero_props, "snapshotdir");
	if (snapdir == NULL || snapdir[0] == '\0') {
		e = newErr("Snapshot target file not allowed because no 'snapshotdir' has been configured");
		goto bailout;
	}

	dir = opendir(snapdir);
	if (dir == NULL) {
		e = newErr("could not open dir %s: %s", snapdir, strerror(errno));
		goto bailout;
	}
	while ((ent = readdir(dir)) != NULL) {
		struct stat statbuf;
		if (fstatat(dirfd(dir), ent->d_name, &statbuf, 0) < 0) {
			e = newErr("couldn't stat %s/%s: %s", snapdir, ent->d_name, strerror(errno));
			goto bailout;
		}
		if ((statbuf.st_mode & S_IFREG) == 0)
			continue;
		time_t timestamp = parse_snapshot_name(ent->d_name, dbname);
		if (timestamp == 0)
			continue;

		struct snapshot *snap = push_snapshot(snapshots, nsnapshots);
		snap->dbname = strdup(dbname);
		snap->time = timestamp;
		snap->size = statbuf.st_size;
		snap->path = malloc(strlen(snapdir) + 1 + strlen(ent->d_name) + 1);
		sprintf(snap->path, "%s/%s", snapdir, ent->d_name);
	}

bailout:
	if (dir != NULL)
		closedir(dir);
	return e;
}

/* Return 0 if the filename is not a valid snapshot name for the
 * given datase. Otherwise, return the timestamp encoded in
 * the filename.
 */
static time_t
parse_snapshot_name(const char *filename, const char *dbname)
{
	// dbname_YYYYMMMDDTHHMMUTC.tar.gz
	//       ^^^^^^^^^^^^^^^^^^^^^^^^^ 26 chars from underscore to end

	if (strlen(filename) <= 26)
		return 0;
	int namelen = strlen(filename) - 26;

	if (strncmp(filename, dbname, namelen) != 0)
		return 0;

	struct tm tm = {0};
	char *end = strptime(filename + namelen, "_%Y%m%dT%H%M%SUTC.tar.gz", &tm);
	if (end != NULL && *end != '\0')
		return 0;

        // We want to interpret this as UTC.
        // Unfortunately, mktime interprets it as Localtime.
        time_t wrong = mktime(&tm);

        // Let's adjust it.
        // Take a timestamp, render it in UTC, then read back as Localtime.
	// Look at the difference.
        time_t before = time(NULL);
        gmtime_r(&before, &tm);
        time_t after = mktime(&tm);
        time_t correct = before - after + wrong;

	return correct;
}

err
snapshot_default_filename(char **ret, const char *dbname)
{
	err e = NO_ERR;
	time_t now;
	size_t len;
	char *name_buf = NULL;
	char *p;

	/* get the snapdir */
	char *snapdir = getConfVal(_mero_props, "snapshotdir");
	if (snapdir == NULL || snapdir[0] == '\0') {
		e = newErr("Snapshot target file not allowed because no 'snapshotdir' has been configured");
		goto bailout;
	}

	/* get the current time, in UTC */
	now  = time(NULL);
	struct tm time_parts;
	gmtime_r(&now, &time_parts);

	/* allocate and write the filename buffer */
	len = strlen(dbname) + strlen(snapdir) + 100;
	name_buf = malloc(len + 1);
	p = name_buf + sprintf(name_buf, "%s%c%s_", snapdir, DIR_SEP, dbname);
	strftime(p, len - (p - name_buf), "%Y%m%dT%H%M%SUTC.tar.gz", &time_parts);

	/* return it */
	*ret = name_buf;

bailout:
	if (e != NULL)
		free(name_buf);
	return e;
}


static err
validate_location(const char *dest)
{
	err e = NO_ERR;
	/* these are malloc'ed: */
	char *resolved_snapdir = NULL;
	char *dest_dup = NULL;
	char *resolved_destination = NULL;
	/* and these are not: */
	char *configured_snapdir = NULL;
	char *dest_dir = NULL;

	/* Get the canonical path of the snapshot directory */
	configured_snapdir = getConfVal(_mero_props, "snapshotdir");
	if (configured_snapdir == NULL || configured_snapdir[0] == '\0') {
		e = newErr("Action not allowed because no 'snapshotdir' has been configured");
		goto bailout;
	}
	if (configured_snapdir[0] != '/') {
		e = newErr("Setting 'snapshotdir' should be an absolute path");
		goto bailout;
	}
	resolved_snapdir = realpath(configured_snapdir, NULL);
	if (resolved_snapdir == NULL) {
		e = newErr("Cannot resolve configured snapshot directory '%s': %s",
			configured_snapdir, strerror(errno));
		goto bailout;
	}

	/* resolve the directory the snapshot is about to be written to */
	dest_dup = strdup(dest);
	dest_dir = dirname(dest_dup);

	resolved_destination = realpath(dest_dir, NULL);
	if (resolved_destination == NULL) {
		e = newErr("Cannot resolve snapshot directory '%s': %s",
			dest_dir, strerror(errno));
		goto bailout;
	}

	/* snapdir must be a prefix of destination */
	if (
		strlen(resolved_snapdir) > strlen(resolved_destination)
		|| 0 != strncmp(
			resolved_snapdir,
			resolved_destination,
			strlen(resolved_snapdir))
	) {
		e = newErr("Snapshot directory '%s' is not inside configured snapshot directory '%s'",
			dest, resolved_snapdir);
		goto bailout;
	}

bailout:
	free(resolved_snapdir);
	free(dest_dup);
	free(resolved_destination);

	return e;
}

#define TAR_BLOCK_SIZE (512)

/* Read a full block from the stream.
 * Return 0 on succes, -1 on failure.
 * Set *err to NULL if the failure is caused by an end of file
 * on a block boundary, non-NULL on read error.
 */
static int
read_tar_block(stream *s, char *block, err *error)
{
	ssize_t nread = mnstr_read(s, block, 1, TAR_BLOCK_SIZE);
	if (nread <= 0) {
		if (mnstr_errnr(s) != 0) {
			/* failure */
			*error = newErr("Read error (%zd): %s", nread, mnstr_error(s));
		} else {
			*error = NULL;
		}
		return -1;
	}
	if (nread < TAR_BLOCK_SIZE) {
		*error = newErr("Incomplete read");
		return -1;
	}
	*error = NULL;
	return 0;
}

static char *
extract_tar_member_filename(const char *block)
{
	const char *name_field = block;
	size_t name_len = strnlen(name_field, 100);
	const char *prefix_field = block + 345;
	size_t prefix_len = strnlen(prefix_field, 155);
	char *buf = malloc(100 + 1 + 155 + 1); // prefix slash name nul

	if (prefix_len == 0) {
		memmove(buf, name_field, name_len);
		buf[name_len] = '\0';
	} else {
		memmove(buf, prefix_field, prefix_len);
		buf[prefix_len] = '/';
		memmove(buf + prefix_len + 1, name_field, name_len);
		buf[prefix_len + 1 + name_len] = '\0';
	}

	return buf;
}

static ssize_t
extract_tar_member_size(const char *block)
{
	size_t size;
	char buf[13];
	memmove(buf, block + 124, 12);
	buf[12] = '\0';
	if (sscanf(buf, "%zo", &size) != 1)
		return -1;
	return (ssize_t) size;
}


/* We're implementing our own untar instead of invoking /usr/bin/tar. Why?
 * Wrapping /usr/bin/tar correctly is quite a lot of work. We have to fork, we
 * have to get any error messages from tar to the child process and then to the
 * parent process, etc. Also, we cannot depend on /usr/bin/tar being able to
 * decompress any compression algorithms so to do it right we should decompress
 * the data ourselves and pipe it to tar to unpack it. A lot of work and a lot
 * of corner cases. Moreover, the snapshot generating tar code is also home
 * grown. This is necessary because we snapshot parts of files, not whole files.
 */
static err
unpack_tarstream(stream *tarstream, char *destdir, int skipfirstcomponent)
{
	char block[TAR_BLOCK_SIZE];
	err e = NO_ERR;
	char *whole_filename = NULL;
	char *destfile = NULL;
	FILE *outfile = NULL;

	while (read_tar_block(tarstream, block, &e) >= 0) {
		if (e != NO_ERR)
			return e;

		// Determine the target filename
		free(whole_filename);
		whole_filename = extract_tar_member_filename(block);
		if (strlen(whole_filename) == 0) {
			goto bailout; // done
		}

		char *useful_part;
		if (skipfirstcomponent) {
			useful_part = strchr(whole_filename, '/');
			if (useful_part != NULL)
				useful_part += 1;
			else
				useful_part = whole_filename;
		} else {
			useful_part = whole_filename;
		}
		destfile = realloc(destfile, strlen(destdir) + 1 + strlen(useful_part) + 1);
		sprintf(destfile, "%s/%s", destdir, useful_part);

		// Create any missing directories
		for (char *p = destfile + strlen(destdir) + 1; *p != '\0'; p++) {
			if (*p == '/') {
				*p = '\0';
				int ret = mkdir(destfile, 0755);
				if (ret < 0 && errno != EEXIST) {
					e = newErr("Could not create directory %s: %s", destfile, strerror(errno));
					goto bailout;
				}
				*p = '/';
			}
		}

		// Copy the data
		outfile = fopen(destfile, "w");
		if (outfile == NULL) {
			e = newErr("Could not open %s", destfile);
			goto bailout;
		}
		ssize_t size = extract_tar_member_size(block);
		while (size > 0) {
			int read_result = read_tar_block(tarstream, block, &e);
			if (e != NO_ERR) {
				goto bailout;
			}
			if (read_result < 0) {
				e = newErr("unexpected end of tar file");
				goto bailout;
			}
			size_t nwrite = size > TAR_BLOCK_SIZE ? TAR_BLOCK_SIZE : size;
			size_t written = fwrite(block, 1, nwrite, outfile);
			if (written < nwrite) {
				e = newErr("Error writing %s: %s", destfile, strerror(errno));
				goto bailout;
			}
			size -= TAR_BLOCK_SIZE;
		}
		fclose(outfile);
		outfile = NULL;
	}

bailout:
	if (outfile != NULL)
		fclose(outfile);
	free(whole_filename);
	free(destfile);
	return e;
}

