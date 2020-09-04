START TRANSACTION;
CREATE TABLE "sys"."t2" (
	"c0" DOUBLE        NOT NULL,
	"c1" INTERVAL MONTH,
	CONSTRAINT "t2_c0_pkey" PRIMARY KEY ("c0"),
	CONSTRAINT "t2_c1_c0_unique" UNIQUE ("c1", "c0")
);
COPY 1 RECORDS INTO "sys"."t2" FROM stdin USING DELIMITERS E'\t',E'\n','"';
1662973479	1626041622

SELECT ALL t2.c0 FROM t2 WHERE ((COALESCE(0.9, 0.5, 0.7, 0.6, 0.8)) IS NULL) IS NOT NULL;
	-- 1662973479
SELECT CAST(SUM(count) AS BIGINT) FROM (SELECT ALL CAST(((COALESCE(0.9, 0.5, 0.7, 0.6, 0.8)) IS NULL) IS NOT NULL AS INT) 
as count FROM t2) as res;
	-- 1
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t0" ("c0" TIME,"c1" SMALLINT NOT NULL);
CREATE TABLE "sys"."t1" ("c1" SMALLINT,"c2" DATE NOT NULL);
CREATE TABLE "sys"."t2" ("c0" TIME,"c1" SMALLINT,CONSTRAINT "t2_c0_unique" UNIQUE ("c0"));
COPY 3 RECORDS INTO "sys"."t2" FROM stdin USING DELIMITERS E'\t',E'\n','"';
NULL	0
16:03:32	NULL
02:15:11	NULL

select all t0.c1 from t0, t1 natural join t2 where (t1.c1) not between symmetric (t1.c1) and (t0.c1);
	--empty
ROLLBACK;

CREATE TABLE t2(c1 bigint UNIQUE PRIMARY KEY NOT NULL);
CREATE IMPRINTS INDEX i0 ON t2 (c1);
INSERT INTO t2(c1) VALUES(68055641); 
CREATE INDEX i1 ON t2 (c1);
INSERT INTO t2(c1) VALUES(1807763525);
DROP TABLE t2;

START TRANSACTION;
CREATE TABLE "sys"."t0" ("c0" DOUBLE,"c1" DOUBLE NOT NULL,CONSTRAINT "t0_c1_c0_unique" UNIQUE ("c1", "c0"));
COPY 8 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
NULL	0.11556091558253245
0.29659357385748286	68693719
0.9191040589762235	0.5658689286027364
NULL	0.1019666413117839
NULL	0.64159659402381
NULL	0.06945707167931647
1696129939	1930440479
0.291412016319756	0.19803645886665644

CREATE TABLE "sys"."t1" ("c1" DOUBLE,CONSTRAINT "t1_c1_unique" UNIQUE ("c1"));

select cast(sum(count) as bigint) from (select cast(not ((-307103413) in (0.68224454, 0.9718348)) as int) as count from t0 right outer join t1 
on (t0.c1) between symmetric (t1.c1) and (((- (-1063131904))&(coalesce(-569972440, 1845997183))))) as res;
	-- NULL
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t0" ("c0" TIMESTAMP NOT NULL,CONSTRAINT "t0_c0_pkey" PRIMARY KEY ("c0"),CONSTRAINT "t0_c0_unique" UNIQUE ("c0"));
COPY 3 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
"1970-01-12 10:04:08.000000"
"1970-01-06 03:09:33.000000"
"1970-01-19 10:03:56.000000"

CREATE TABLE "sys"."t1" ("c0" TIMESTAMP);
COPY 3 RECORDS INTO "sys"."t1" FROM stdin USING DELIMITERS E'\t',E'\n','"';
"1970-01-16 15:26:07.000000"
"1970-01-21 09:11:00.000000"
"1969-12-24 08:07:10.000000"

CREATE TABLE "sys"."t2" ("c0" INTERVAL MONTH,"c1" DOUBLE,"c2" BOOLEAN);
COPY 4 RECORDS INTO "sys"."t2" FROM stdin USING DELIMITERS E',',E'\n','"';
1293946112,0.3251224351379446,true
1293946112,0.3251224351379446,true
540568573,NULL,false
NULL,NULL,false

SELECT 1 FROM t2 LEFT JOIN t0 ON CASE CAST(t2.c0 AS VARCHAR(32)) WHEN CAST(t2.c2 AS VARCHAR(32)) THEN 4 WHEN COALESCE('a', 'b') THEN 3 END IS NOT NULL;
	-- 1
	-- 1
	-- 1
	-- 1
SELECT CAST(SUM(count) AS BIGINT) FROM (SELECT CAST(t2.c2 AS INT) as count FROM t2 LEFT OUTER JOIN t0 ON (CASE CAST(t2.c0 AS VARCHAR(32)) WHEN CAST('*D' AS VARCHAR(32)) THEN CASE 'u--' 
WHEN 'Q' THEN 0.81 END WHEN CAST(t2.c2 AS VARCHAR(32)) THEN CASE 51854410 WHEN 0.6132552 THEN 134188918 END WHEN COALESCE('鈋', 'Nb|k', 's{%g.8Bj') THEN CAST(571120738 AS INT) 
ELSE CAST(0.13 AS REAL) END) IS NOT NULL CROSS JOIN (SELECT ALL COALESCE(t1.c0, t0.c0) FROM t0, t1) AS sub0) as res;
	-- 54
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t0" ("c0" BOOLEAN NOT NULL,CONSTRAINT "t0_c0_pkey" PRIMARY KEY ("c0"),CONSTRAINT "t0_c0_unique" UNIQUE ("c0"));
CREATE IMPRINTS INDEX "i0" ON "sys"."t0" ("c0");
CREATE TABLE "sys"."t2" ("c0" BOOLEAN);

SELECT 1 FROM t0 FULL OUTER JOIN t2 ON CASE WHEN TRUE THEN EXISTS (SELECT 1 FROM t2) END;
	-- empty
SELECT CAST(SUM(count) AS BIGINT) FROM (SELECT ALL CAST((CASE TIMESTAMP '1970-01-23 00:06:34' WHEN TIMESTAMP '1970-01-15 23:55:20' THEN 0.1 ELSE 0.7 END) NOT IN (COALESCE(0.8, 0.2), COALESCE(0.4, 0.5, 0.9, 0.8)) AS INT) as count 
FROM t0 FULL OUTER JOIN t2 ON CASE WHEN t2.c0 THEN (DATE '1970-01-24') IN (DATE '1970-01-11', DATE '1969-12-18') WHEN (t2.c0) NOT BETWEEN SYMMETRIC (t0.c0) AND (CASE DATE '1970-01-01' WHEN DATE '1970-01-15' THEN TRUE ELSE t2.c0 END) 
THEN t0.c0 WHEN NOT (((t2.c0)<=(t2.c0))) THEN NOT EXISTS (SELECT DISTINCT INTERVAL '903334778' SECOND FROM t2 WHERE t2.c0) END) as res;
	-- empty
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t2" ("c0" CHARACTER LARGE OBJECT NOT NULL);
INSERT INTO t2 VALUES (TIME '20:39:07' BETWEEN TIME '11:09:56' AND TIME '04:20:04');
SELECT c0 from t2;
	-- false
INSERT INTO t2(c0) VALUES(CAST((CASE WHEN r'' THEN TIME '06:29:46' WHEN r'b_P' THEN TIME '20:39:07' END) BETWEEN ASYMMETRIC (COALESCE(TIME '11:09:56', TIME '12:05:55')) AND (COALESCE(TIME '18:59:07', TIME '04:20:04', TIME '19:01:06')) AS STRING(638)));
	--error while converting string '' to bit
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t0" ("c0" DATE NOT NULL,CONSTRAINT "t0_c0_pkey" PRIMARY KEY ("c0"));
CREATE TABLE "sys"."t1" ("c0" DATE NOT NULL);
CREATE INDEX "i1" ON "sys"."t1" ("c0");
CREATE ORDERED INDEX "i2" ON "sys"."t1" ("c0");
create view v0(c0) as (select 1 from t0,t1 where ((t0.c0)>=(t1.c0)));
select '12' like 'i' from t0, t1 right outer join v0 on exists (select 'a' from t0, t1);
	--empty
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t0" ("c0" CHARACTER LARGE OBJECT NOT NULL,"c1" INTEGER,CONSTRAINT "t0_c0_pkey" PRIMARY KEY ("c0"),CONSTRAINT "t0_c0_unique" UNIQUE ("c0"),CONSTRAINT "t0_c1_unique" UNIQUE ("c1"));
COPY 4 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
"0.6010931584470857"	-743829177
"0.42620477484022556"	NULL
"1329239822"	-2112960019
"(tO\\i4"	NULL

CREATE TABLE "sys"."t1" ("c0" CHARACTER LARGE OBJECT,"c1" INTEGER);
COPY 3 RECORDS INTO "sys"."t1" FROM stdin USING DELIMITERS E'\t',E'\n','"';
NULL	-1356169629
NULL	21282885
"380068065"	2028904352

CREATE TABLE "sys"."t2" ("c0" CHARACTER LARGE OBJECT);
COPY 20 RECORDS INTO "sys"."t2" FROM stdin USING DELIMITERS E'\t',E'\n','"';
"1339658188"
"g曹"
NULL
"1886645193"
"I+"
"YhN"
"밿o{%p"
"n8v"
"nFa{#"
"1001686043"
">+"
"0.3359225172978786"
"_"
"990996842"
"B3弸_"
""
"Pd\\"
"!jt*cw+~"
""
"<P9\t-s펰>"

create view v0(c0, c1, c2, c3) as (select distinct timestamp '1970-01-15 12:32:10', date '1970-01-19', t1.c1, t1.c1 from t0, t1 where ((t1.c1)=(t1.c1)));
select 1 from t2 right outer join t1 on t1.c0 not like t2.c0;
	-- 21 1s
select 1 from t2 join t1 on t1.c0 not like t2.c0;
	-- 19 1s
select cast((((coalesce(t2.c0, t2.c0))not ilike(t2.c0))) = true as int) as count from v0, t2 right outer join t1 on not (not (((t1.c0)not ilike(t2.c0))));
	-- 6 NULLs, 57 0s, 63 rows in total
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t1" ("c0" BOOLEAN);
INSERT INTO t1(c0) VALUES(TRUE), ((EXISTS (SELECT DATE '1970-01-06' FROM t1)) BETWEEN (TRUE) AND ((1) IN (1)));
SELECT c0 from t1;
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t0" ("c0" TIMESTAMP,"c1" CHARACTER LARGE OBJECT NOT NULL,CONSTRAINT "t0_c1_pkey" PRIMARY KEY ("c1"),CONSTRAINT "t0_c0_c1_unique" UNIQUE ("c0", "c1"));
COPY 4 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
"1970-01-23 07:23:51.000000"	"1906903205"
"1970-01-23 07:23:51.000000"	"0.4338646653291859"
"1970-01-23 07:23:51.000000"	"-1882905169"
"1970-01-23 07:23:51.000000"	"*"

CREATE TABLE "sys"."t1" ("c0" CHAR(343) NOT NULL,"c2" SMALLINT NOT NULL,CONSTRAINT "t1_c0_pkey" PRIMARY KEY ("c0"),CONSTRAINT "t1_c0_unique" UNIQUE ("c0"),CONSTRAINT "t1_c2_unique" UNIQUE ("c2"),CONSTRAINT "t1_c2_c0_unique" UNIQUE ("c2", "c0"));
COPY 3 RECORDS INTO "sys"."t1" FROM stdin USING DELIMITERS E'\t',E'\n','"';
"+}TD"	1
""	3
"541635614"	5

CREATE TABLE "sys"."t2" ("c0" CHAR(343) NOT NULL,"c2" SMALLINT NOT NULL);

SELECT t0.c1 FROM t0, t1 FULL OUTER JOIN t2 ON TRUE WHERE (t0.c1) BETWEEN SYMMETRIC ('p%AY') AND (t1.c0);
	-- 1906903205
	-- 1906903205
	-- 0.4338646653291859
	-- 0.4338646653291859
	-- -1882905169
	-- -1882905169
	-- *
SELECT t1.c2 FROM t0, t1 FULL OUTER JOIN t2 ON NOT (((TIME '03:59:32') IS NULL) = TRUE) WHERE (t0.c1) NOT BETWEEN SYMMETRIC ('p%AY') AND (t1.c0);
	-- 1
	-- 5
	-- 5
	-- 5
	-- 5
SELECT CAST(SUM(count) AS BIGINT) FROM (SELECT ALL CAST((t0.c1) NOT BETWEEN SYMMETRIC ('p%AY') AND (t1.c0) AS INT) as count FROM t0, t1 FULL OUTER JOIN t2 ON NOT (((TIME '03:59:32') IS NULL) = TRUE)) as res;
	-- 5
ROLLBACK;

CREATE TABLE t1(c0 TIME  DEFAULT (TIME '23:27:06'), c1 CHAR(317));
INSERT INTO t1(c1, c0) VALUES(r'V', TIME '14:09:48'), (r'c', TIME '01:06:46');
DELETE FROM t1 WHERE NOT (CAST(((854517748)/(-1764883455)) AS BOOLEAN));
INSERT INTO t1(c0) VALUES(TIME '09:41:58');
CALL sys.vacuum('sys', 't1');
DROP TABLE t1;

CREATE TABLE t0(c0 TIME NULL PRIMARY KEY, c1 TIMESTAMP);
CREATE TABLE IF NOT EXISTS t1(c0 TIMESTAMP, c1 INTERVAL SECOND);
CREATE TABLE t2(LIKE t1); 
INSERT INTO t1(c1) VALUES(INTERVAL '1520729315' SECOND);
CREATE ORDERED INDEX i0 ON t0 (c0);
INSERT INTO t2(c0) VALUES(TIMESTAMP '1970-01-02 17:11:53');
CREATE UNIQUE INDEX i1 ON t0 (c0, c1);
INSERT INTO t0(c0) VALUES(TIME '20:35:54');
SELECT CAST(TIMESTAMP '1970-01-01 19:30:21' = ALL(SELECT DISTINCT t2.c0 FROM t1, t2) AS INT) as count FROM t2, t0 LEFT OUTER JOIN t1 ON NOT EXISTS (SELECT DISTINCT t2.c0 FROM t1, t0, t2);
	-- 0
DROP TABLE t0;
DROP TABLE t1;
DROP TABLE t2;

START TRANSACTION;
CREATE TABLE "sys"."t0" ("c0" CHAR(473),"c1" INTERVAL SECOND NOT NULL,
	CONSTRAINT "t0_c0_unique" UNIQUE ("c0"),
	CONSTRAINT "t0_c1_unique" UNIQUE ("c1"),
	CONSTRAINT "t0_c0_c1_unique" UNIQUE ("c0", "c1")
);
CREATE INDEX "i0" ON "sys"."t0" ("c1", "c0");
COPY 18 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
"Qnec4v3|"	916700621.000
"B"	916700621.000
NULL	2052029418.000
"R"	1043124199.000
""	165830731.000
NULL	345888540.000
"[|"	393122059.000
" 瘞o"	1919932925.000
NULL	894242295.000
NULL	973935741.000
"W~[G-"	449082176.000
NULL	553114649.000
"MH锈"	2121838025.000
"'F6ꒉ"	97497547.000
NULL	2056175383.000
NULL	836812973.000
"/j"	97497547.000
"\t()Y%"	709557814.000

CREATE TABLE "sys"."t1" ("c0" CHAR(473) NOT NULL);
COPY 40 RECORDS INTO "sys"."t1" FROM stdin USING DELIMITERS E'\t',E'\n','"';
"v0"
"?}z#4齩"
"}IFT"
"A铑"
"1953144617"
"F฀r.(H"
"Vt1"
"E+Tx4A"
"b"
"O-,j3맲"
"0.6948820797452814"
"\015Hꢖ"
"^"
"RﻻK2"
"858302044"
"鄌"
"Y7瑚?뮱Qpt鿌"
"["
"-1593184632"
"0.4196422515625643"
"F9"
"VA"
"fN\n?菸\015Bb"
"0.3418058502965632"
"pM\015"
"{dT"
""
"vT"
"Ri5D"
"o_⑦l"
" "
"j"
""
""
"1814883154"
"715827645"
""
"pv"
"'AㆁB^UrHl"
"670216259"

CREATE TABLE "sys"."t2" ("c0" DECIMAL(18,3) NOT NULL,"c1" DATE DEFAULT DATE '1970-01-07',
	CONSTRAINT "t2_c0_pkey" PRIMARY KEY ("c0"),
	CONSTRAINT "t2_c1_c0_unique" UNIQUE ("c1", "c0")
);
COPY 9 RECORDS INTO "sys"."t2" FROM stdin USING DELIMITERS E'\t',E'\n','"';
0.203	1970-01-16
0.252	1970-01-07
0.511	1970-01-07
0.880	1970-01-23
0.209	1970-01-07
0.713	1970-01-07
0.199	1970-01-07
0.109	1970-01-07

SELECT t1.c0 FROM t1 WHERE t1.c0 <> ALL(SELECT DISTINCT CAST(0.5646222839477373 AS INT) FROM t0, t1 WHERE (t0.c1) NOT BETWEEN ASYMMETRIC (COALESCE(t0.c1, t0.c1)) AND (t0.c1));
	-- 40 rows
SELECT CAST(SUM(count) AS BIGINT) FROM (SELECT ALL CAST(t1.c0 <> ALL(SELECT DISTINCT CAST(0.5646222839477373 AS INT) FROM t0, t1 WHERE (t0.c1) NOT BETWEEN ASYMMETRIC (COALESCE(t0.c1, t0.c1)) AND (t0.c1)) AS INT) as count FROM t1) as res;
	-- 40
ROLLBACK;
