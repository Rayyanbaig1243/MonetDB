
#include <mem.h>
#include "sql.h"

#include "atom.h"

/* todo, be able to handle generic atom types */
static int atom_debug = 0;

atom *atom_int(sql_subtype * tpe, int val)
{
	atom *a = NEW(atom);
	a->tpe = *tpe;
	a->data.ival = val;
	a->type = int_value;
	if (atom_debug)
		fprintf(stderr, "atom_int(%s,%d)\n", tpe->type->sqlname, val);
	return a;
}

atom *atom_string(sql_subtype * tpe, char *val)
{
	atom *a = NEW(atom);
	a->tpe = *tpe;
	a->data.sval = val;
	a->type = string_value;
	if (atom_debug)
		fprintf(stderr, "atom_string(%s,%s)\n", tpe->type->sqlname,val);
	return a;
}

atom *atom_float(sql_subtype * tpe, double val)
{
	atom *a = NEW(atom);
	a->tpe = *tpe;
	a->data.dval = val;
	a->type = float_value;
	if (atom_debug)
		fprintf(stderr, "atom_float(%s,%f)\n", tpe->type->sqlname,val);
	return a;
}

atom *atom_general(sql_subtype * tpe, char *val)
{
	atom *a = NEW(atom);
	a->tpe = *tpe;
	a->data.sval = val;
	a->type = general_value;
	if (atom_debug)
		fprintf(stderr, "atom_general(%s,%s)\n", tpe->type->sqlname, val);
	return a;
}

void atom_destroy(atom * a)
{
	if (a->type == string_value || a->type == general_value)
		_DELETE(a->data.sval);
	_DELETE(a);
}

char *atom2string(atom * a)
{
	char buf[1024];
	switch (a->type) {
	case int_value:
		sprintf(buf, "%d", a->data.ival);
		break;
	case string_value:
		sprintf(buf, "\'%s\'", a->data.sval);
	case float_value:
		sprintf(buf, "%f", a->data.dval);
		break;
	case general_value:
		if (a->data.sval)
			sprintf(buf, "%s \'%s\'", a->tpe.type->name,
				a->data.sval);
		else
			sprintf(buf, "NULL");
		break;
	}
	return _strdup(buf);
}

sql_subtype *atom_type(atom * a)
{
	return &(a->tpe);
}

atom *atom_dup(atom * a)
{
	atom *r = NEW(atom);
	*r = *a;
	if (a->type == string_value || a->type == general_value)
		r->data.sval = _strdup(a->data.sval);
	return r;
}
