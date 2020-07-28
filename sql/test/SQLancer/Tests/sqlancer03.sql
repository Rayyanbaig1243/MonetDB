select splitpart(r'%Fz晟2墁', '', 1), splitpart(r'%Fz晟2墁', r'', 2), splitpart(r'%Fz晟2墁', r'', 1271186887);

START TRANSACTION; -- Bug 6916
CREATE TABLE "t0" ("c0" BOOLEAN NOT NULL,"c1" SMALLINT NOT NULL,CONSTRAINT "t0_c0_c1_pkey" PRIMARY KEY ("c0", "c1"));
INSERT INTO "t0" VALUES (false, -1);
create view v0(c0, c1, c2, c3) as (select ((t0.c1)<<(cast(0.09114074486978418487836961503489874303340911865234375 as int))), 0.4088967652609865, 0.3848869389602949109274732109042815864086151123046875, t0.c0 from t0 where t0.c0);

SELECT v0.c0 FROM t0 FULL OUTER JOIN v0 ON t0.c0;
	-- NULL
SELECT v0.c0 FROM t0 FULL OUTER JOIN v0 ON t0.c0 WHERE (rtrim(((upper(''))||(v0.c1)))) IS NULL;
	-- NULL
SELECT v0.c0 FROM t0 FULL OUTER JOIN v0 ON t0.c0 WHERE NOT ((rtrim(((upper(''))||(v0.c1)))) IS NULL);
	-- empty
SELECT v0.c0 FROM t0 FULL OUTER JOIN v0 ON t0.c0 WHERE ((rtrim(((upper(''))||(v0.c1)))) IS NULL) IS NULL;
	-- empty

ROLLBACK;

START TRANSACTION; -- Bug 6918
CREATE TABLE "sys"."t0" ("c0" BOOLEAN NOT NULL,"c1" BIGINT,CONSTRAINT "t0_c0_pkey" PRIMARY KEY ("c0"),CONSTRAINT "t0_c0_unique" UNIQUE ("c0"));
create view v0(c0, c1, c2) as (select all 2.020551048E9, 0.16688174, 0.3732000026221729 from t0 where t0.c0) with check option;
SELECT sql_min(sql_max(NULL, ''), '') FROM v0 LEFT OUTER JOIN t0 ON true;
SELECT sql_min(sql_max(NULL, ''), '');
SELECT ALL length(upper(MIN(ALL CAST(((trim(CAST(r'' AS STRING(659)), CAST(r'o3%+i]抔DCöf▟nßOpNbybಜ7' AS STRING)))||(sql_min(sql_max(NULL, r''), splitpart(r'x', r',7+.', t0.c1)))) AS STRING(151))))), 0.4179268710155164 
FROM v0 LEFT OUTER JOIN t0 ON NOT (t0.c0) WHERE t0.c0 GROUP BY 0.3584962, CAST(t0.c1 AS STRING(601)), t0.c1;
ROLLBACK;

START TRANSACTION; -- Bug 6919
CREATE TABLE "sys"."t0" (
	"c0" INTEGER       NOT NULL,
	"c1" DOUBLE,
	CONSTRAINT "t0_c0_pkey" PRIMARY KEY ("c0")
);
COPY 29 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
6	0.01926179604972278
7	0.01926179604972278
8	0.01926179604972278
9	0.01926179604972278
10	0.01926179604972278
11	0.01926179604972278
12	0.01926179604972278
13	0.01926179604972278
14	0.01926179604972278
15	0.01926179604972278
16	0.01926179604972278
17	0.01926179604972278
954233931	0.01926179604972278
-890980732	0.01926179604972278
18	0.9441921149477416
19	0.8647722974466762
20	0.6303259287607281
21	0.7198562388857971
22	1905034025
1927464158	0.827299544139285
421223489	0.03854140660184213
-906851618	0.01926179604972278
23	0.44641096314987394
24	0.5358519423727929
25	0.8490801972106654
911090097	1
-708085857	0.7843275143974144
26	1130231849
27	0.1052118441396751

select "insert"('屁{珙', 1, 1, '1'), "insert"('屁{珙', 1, 1, '抔'), "insert"('屁抔珙', 1, 1, 'ಜ'), "insert"('a', 0, 1, 'ಜ'), "insert"('a', 0, 0, 'ಜ');
select "insert"('屁{珙', 1, 1, '1'), "insert"('屁{珙', 1, 1, '抔'), "insert"('屁抔珙', 1, 1, 'ಜ') from t0;
ROLLBACK;

CREATE TABLE t0(c0 boolean, c1 boolean, c2 int, UNIQUE(c0, c1)); -- Bug 6920
INSERT INTO t0(c1) VALUES((0.5) NOT  BETWEEN SYMMETRIC (CAST(length(upper(r'z')) AS INT)) AND (2)), (FALSE);
INSERT INTO t0(c0) VALUES(TRUE);
INSERT INTO t0(c1) VALUES(FALSE), (TRUE);
INSERT INTO t0(c2, c0, c1) VALUES(2, (ltrim(lower(r'K'), ((upper(r'4'))||(- (7))))) IS NOT NULL, (((lower(r'ö
eg#K,纗HSJw!{cOw⇒l/l!B*H'))||(((CAST(0.1 AS INT))+(-5))))) IN (lower(CAST(TRUE AS STRING)))), (-9, NULL, (0.3) NOT IN (2.96348087E8, 0.3)), (4, TRUE, (0.5) NOT IN (-3, 4));
INSERT INTO t0(c1) VALUES(TRUE);
INSERT INTO t0(c1, c2) VALUES(FALSE, 623585248);
INSERT INTO t0(c0) VALUES(NOT (NOT ((((-1)*(-9))) NOT IN (0.7)))), (FALSE);
INSERT INTO t0(c0) VALUES(TRUE);
INSERT INTO t0(c2) VALUES(-1);
DELETE FROM t0 WHERE (t0.c0) = FALSE;
INSERT INTO t0(c1, c0, c2) VALUES(TRUE, ((+ (- (1)))>(charindex(CAST(0.3 AS STRING), ((CAST(TRUE AS STRING(771)))||(0.2)), length(r'd')))), -1);
UPDATE t0 SET c2 = 1 WHERE ((((t0.c1)OR(CAST(t0.c2 AS BOOLEAN))))OR((CAST(0.6 AS DECIMAL)) NOT IN (0.1)));
SELECT t0.c0 FROM t0 WHERE ((CAST(t0.c2 AS INT)) NOT  BETWEEN ASYMMETRIC (abs(t0.c2)) AND (((t0.c2)/(t0.c2)))) NOT  BETWEEN ASYMMETRIC (t0.c0) AND ((t0.c2) NOT IN (t0.c2));
SELECT t0.c0 FROM t0 WHERE (t0.c2) BETWEEN (t0.c0) AND ((t0.c2) NOT IN (t0.c2));
DROP TABLE t0;

CREATE TABLE "sys"."t0" (
	"c0" BOOLEAN,
	"c1" BOOLEAN,
	"c2" INTEGER,
	CONSTRAINT "t0_c2_pkey" PRIMARY KEY ("c2"),
	CONSTRAINT "t0_c0_c1_unique" UNIQUE ("c0", "c1")
);
INSERT INTO "sys"."t0" VALUES (NULL, true, 10),
 (NULL, false, 11),
 (true, NULL, 12),
 (NULL, false, 13),
 (NULL, true, 14),
 (true, false, 15),
 (NULL, true, 16),
 (true, true, 17),
 (NULL, true, 18),
 (NULL, false, 19),
 (true, NULL, 20),
 (true, NULL, 21),
 (NULL, NULL, 22),
 (false, true, 23);
TRUNCATE t0;

-- The following copy into shouldn't trigger a constrain violation error (it's the same insert above)
COPY 14 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
NULL	true	10
NULL	false	11
true	NULL	12
NULL	false	13
NULL	true	14
true	false	15
NULL	true	16
true	true	17
NULL	true	18
NULL	false	19
true	NULL	20
true	NULL	21
NULL	NULL	22
false	true	23

DROP TABLE t0;

START TRANSACTION;
CREATE TABLE "sys"."t0" (
	"c0" DECIMAL(18,3) NOT NULL DEFAULT cast(cast("sys"."sql_sub"("sys"."sql_neg"(1933820187),"sys"."charindex"(cast(0.235784 as clob(182)),"sys"."concat"('rt\\b&oOT',1174691962),"sys"."locate"('!oLqvKg恺','!G+tZ9\'A\'LZ*滻mW^',1174691962))) as int) as decimal(18,3)),
	"c1" DECIMAL(18,3),
	"c2" CHARACTER LARGE OBJECT,
	CONSTRAINT "t0_c0_pkey" PRIMARY KEY ("c0"),
	CONSTRAINT "t0_c0_unique" UNIQUE ("c0"),
	CONSTRAINT "t0_c2_unique" UNIQUE ("c2"),
	CONSTRAINT "t0_c0_c2_c1_unique" UNIQUE ("c0", "c2", "c1")
);
COMMENT ON COLUMN "sys"."t0"."c2" IS 'vi';
COPY 1 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
-1933820187.000	NULL	"-1554387152"

select t0.c0 from t0 where not (true) union all select all t0.c0 from t0 where not (not (true)) union all select t0.c0 from t0 where (not (true)) is null;
ROLLBACK;

START TRANSACTION;
create table t0 (a int, b int);
insert into t0 values (1,1), (2,2);
select min(t0.a), pi() from t0 group by t0.b;

SELECT 1 FROM t0 WHERE DATE '1970-01-01' = NULL;
SELECT 1 FROM t0 WHERE NULL IN (DATE '1970-01-01');
SELECT ALL DATE '1970-01-01', CAST(COUNT(ALL TIMESTAMP '1970-01-01 01:06:52') AS INT) FROM t0 WHERE (NULL) NOT IN (DATE '1970-01-01') GROUP BY ((CAST(0.6 AS STRING))||(0.75)), INTERVAL '-13' SECOND;
ROLLBACK;

START TRANSACTION;
create table t0 (a time default time '10:15:32', b date default date '2010-01-31', c timestamp default timestamp '1980-11-04 08:49:25');
insert into t0;
insert into t0 values (default, default, default);
select a,b,c from t0;
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t0" (
	"c0" TIME,
	"c1" CHARACTER LARGE OBJECT NOT NULL,
	CONSTRAINT "t0_c1_pkey" PRIMARY KEY ("c1"),
	CONSTRAINT "t0_c1_unique" UNIQUE ("c1")
);
COPY 14 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
19:29:38	""
05:51:00	"#B"
NULL	".n"
NULL	"0.0"
20:29:28	"-601098762"
20:59:23	")TD)Dnö"
22:09:19	"aaJ즳#B!sJNG㡩"
09:10:09	"W"
23:43:33	"k"
15:43:27	"-0.0"
20:02:19	"0.7126186870446843"
05:23:53	"1498390845"
00:17:15	"{"
06:51:52	"41230238"

SELECT t0.c0 FROM t0 WHERE ((t0.c0)<>(t0.c0));
	--empty
SELECT t0.c0 FROM t0 WHERE NOT (((t0.c0)<>(t0.c0)));
	--12 tuples (all rows except ones with c0 null)
SELECT t0.c0 FROM t0 WHERE (((t0.c0)<>(t0.c0))) IS NULL;
	--NULL
	--NULL
ROLLBACK;

START TRANSACTION; -- Bug 6926
CREATE TABLE t0(c0 TIME, c1 VARCHAR(1000) DEFAULT (upper(CAST((('')||(DATE '1970-01-19')) AS VARCHAR(152)))) PRIMARY KEY UNIQUE NULL);
INSERT INTO t0(c0, c1) VALUES(TIME '19:29:38', '');
INSERT INTO t0(c1, c0) VALUES(CAST(TIME '06:50:34' AS VARCHAR(256)), TIME '01:39:55');
INSERT INTO t0(c1, c0) VALUES(CAST(0.6 AS VARCHAR(411)), TIME '22:07:22'), ('#B', TIME '05:51:00'), (((((CAST('434' AS VARCHAR(849)))||(0.4)))||(TIME '04:05:28')), TIME '06:50:34');
INSERT INTO t0(c1) VALUES(CAST(INTERVAL '42' SECOND AS VARCHAR(102)));
INSERT INTO t0(c0, c1) VALUES(TIME '16:29:13', 'J'), (TIME '05:57:44', '49䄎y_}');
INSERT INTO t0(c1, c0) VALUES('2', TIME '07:15:50'), (CAST(TIME '16:29:13' AS VARCHAR(1000)), TIME '03:00:56');
INSERT INTO t0(c1) VALUES('O큑LSGAM||Z赐'), ('.n');
INSERT INTO t0(c1, c0) VALUES('c蠷웵', TIME '04:59:13');
INSERT INTO t0(c1) VALUES('0.0');
INSERT INTO t0(c0, c1) VALUES(TIME '20:29:28', '-343'), (TIME '01:19:51', 'j'), (TIME '11:37:23', ((((((((CAST(DATE '1970-01-23' AS VARCHAR(849)))||(INTERVAL '23' MONTH)))||(INTERVAL '-535' SECOND)))||(lower((('鮥*Qß4')||(DATE '1970-01-01'))))))||(0.4)));
INSERT INTO t0(c0, c1) VALUES(TIME '02:38:14', lower(CAST(INTERVAL '342' SECOND AS VARCHAR(1000)))), (TIME '23:43:33', '64');
DELETE FROM t0 WHERE ((((1 IS NOT NULL)AND(FALSE)))OR(((CAST(0.3 AS VARCHAR(836)))<(upper(t0.c1)))));
INSERT INTO t0(c0, c1) VALUES(TIME '20:59:23', ')TD)Dnö'), (TIME '22:09:19', 'aaJ즳#B!sJNG㡩');
INSERT INTO t0(c0, c1) VALUES(TIME '20:02:19', CAST(0.1 AS VARCHAR(927)));
INSERT INTO t0(c0, c1) VALUES(TIME '00:17:15', '{'), (TIME '06:51:52', CAST(4.1230238E7 AS VARCHAR(459)));
SELECT ALL t0.c0 FROM t0 WHERE (((t0.c0)<>(t0.c0))) IS NULL;
	--NULL
	--NULL
ROLLBACK;

START TRANSACTION;
CREATE TEMPORARY TABLE t0(c0 integer AUTO_INCREMENT UNIQUE NOT NULL, c1 FLOAT DEFAULT (0.9323624));
select t0.c0 from t0 where -t0.c0 <= 1 and t0.c0 between t0.c0 and -t0.c0;
ROLLBACK;

START TRANSACTION; --Bug 6927
CREATE TABLE "sys"."t0" ("c0" CHARACTER LARGE OBJECT NOT NULL,CONSTRAINT "t0_c0_pkey" PRIMARY KEY ("c0"),CONSTRAINT "t0_c0_unique" UNIQUE ("c0"),CONSTRAINT "t0_c0_unique" UNIQUE ("c0"));
COPY 5 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
"1970-01-19"
"0.9940522485469018"
"Sn"
""
",骭2T*h[99#஺M\nBCϹ㦚X"

CREATE TABLE "sys"."t1" ("c0" CHARACTER LARGE OBJECT,"c1" BOOLEAN NOT NULL,CONSTRAINT "t1_c1_unique" UNIQUE ("c1"));
COPY 2 RECORDS INTO "sys"."t1" FROM stdin USING DELIMITERS E'\t',E'\n','"';
"*"	true
"Xh{%LTF"	false

SELECT 1 FROM t0 CROSS JOIN t1 WHERE (t1.c1 AND (t0.c0 > t0.c0)) IS NULL;
SELECT cast(SUM(agg0) as decimal(10,2)) FROM (SELECT ALL SUM(ALL 0.97) as agg0 FROM t0 CROSS JOIN t1 WHERE ((((t1.c1)AND(t1.c1)))AND(((t0.c0)>(t0.c0)))) 
UNION ALL SELECT SUM(ALL 0.97) as agg0 FROM t0 CROSS JOIN t1 WHERE NOT (((((t1.c1)AND(t1.c1)))AND(((t0.c0)>(t0.c0))))) 
UNION ALL SELECT SUM(ALL 0.97) as agg0 FROM t0 CROSS JOIN t1 WHERE (((((t1.c1)AND(t1.c1)))AND(((t0.c0)>(t0.c0))))) IS NULL) as asdf;
ROLLBACK;

START TRANSACTION; --Bug 6928
CREATE TABLE "sys"."t0" ("c0" DECIMAL(18,3) DEFAULT 0.968720);
COPY 5 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
0.938
0.958
0.877
0.550
0.916

select coalesce(1 = true, false);
select coalesce(1 = true, t0.c0 > 0) from t0;
select count(all coalesce ((case coalesce (1, 2) when case cast(t0.c0 as double) when sql_max(r'', null) 
then ((12)/(23)) end then cast("truncate"(r'1', 54) as boolean) else (coalesce (true, true, r'1', true)) = false end) = true, (t0.c0) not in (t0.c0))) from t0;
ROLLBACK;

START TRANSACTION; --Bug 6929
CREATE TEMPORARY TABLE IF NOT EXISTS t0(c0 TIMESTAMP) ON COMMIT PRESERVE ROWS;
SELECT COALESCE(1, dayofmonth(t0.c0)) FROM t0;
SELECT CAST(SUM(COALESCE(0.67, dayofmonth(t0.c0))) AS BIGINT) FROM t0;
SELECT ALL CAST(SUM(ALL COALESCE (CAST(0.67090863 AS REAL), dayofmonth(t0.c0))) AS BIGINT) FROM t0;
ROLLBACK;

START TRANSACTION; --Bug 6930
CREATE TABLE t0(c0 VARCHAR(319) NOT NULL, c1 TIME, c2 TIMESTAMP PRIMARY KEY UNIQUE NULL, UNIQUE(c0, c2, c1));
CREATE TABLE t1(c0 CHARACTER LARGE OBJECT,c1 DATE);
select t1.c0 from t1 join t0 on coalesce(trim(t0.c0), 1) like t0.c0;
select all t1.c0 from t1 right outer join t0 on ((coalesce (t1.c0, trim(t0.c0), "insert"(splitpart(t0.c0, t0.c0, -618693953), - (-382400246), coalesce (1840724133, 1854087569, 1686971701, 576180091), t1.c0), 
cast(abs(0.160418955416609) as string), cast(coalesce (greatest(interval '-1022285655' second, interval '-1047501443' second), interval '641174375' second, sql_max(interval '-1539884267' second, interval '-685917930' second)) as string)))not ilike(t0.c0));
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t1" ("c0" TIMESTAMP);
COPY 4 RECORDS INTO "sys"."t1" FROM stdin USING DELIMITERS E'\t',E'\n','"';
"1970-01-14 14:26:27.000000"
"1970-01-18 02:50:56.000000"
"1970-01-06 21:36:37.000000"
"1970-01-14 01:01:12.000000"

select all sum(all cast("concat"(cast("month"(t1.c0) as string), r'1313451898') as interval month)) from t1;
ROLLBACK;

START TRANSACTION; -- Unknown barrier type error
CREATE TABLE "sys"."t0" ("c0" INTEGER);
COPY 13 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
-952561247
668236378
-2045848771
-1790523044
-1543588024
-1750414901
1790114978
-274432932
874627516
-452950065
303960197
1
20

create view v0(c0, c1, c2, c3) as (
	select distinct cast(case time '03:52:21' when time '05:04:36' then r'0.2' end as date), 
	coalesce (t0.c0, length(coalesce (r't%QB', replace(r' ,yO_5G刵i稶bDßᶏ''', r'0.8', r'-1e500')))), 1, timestamp '1970-01-16 13:47:20' from t0) with check option;
select v0.c0 from v0 join t0 on (0.3) not in 
(least(cast(t0.c0 as decimal), 
case least(time '19:32:57', time '16:10:04') when coalesce (time '22:25:53', time '00:14:31', time '18:12:09', time '01:59:38') 
then sql_min(0.7, 0.03) else 0.3 end), coalesce (case - (t0.c0) when cast(v0.c2 as real) then abs(0.4) else 0.5 end, cast(t0.c0 as decimal)));
ROLLBACK;

START TRANSACTION; --SIGFPE
CREATE TABLE "sys"."t0" (
	"c0" BIGINT NOT NULL,
	"c1" DOUBLE        NOT NULL,
	"c2" INTERVAL SECOND,
	CONSTRAINT "t0_c0_pkey" PRIMARY KEY ("c0"),
	CONSTRAINT "t0_c0_unique" UNIQUE ("c0"),
	CONSTRAINT "t0_c2_unique" UNIQUE ("c2"),
	CONSTRAINT "t0_c1_c2_c0_unique" UNIQUE ("c1", "c2", "c0")
);
COPY 19 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
99360484	0.8104160489147377	NULL
434886876	2003187499	NULL
1868593144	0.605787503265435	-721601140.000
1061127048	888903964	1369533413.000
-320985624	0.7758661909853402	0.423
-559098799	0.589701133253508	40364999.000
1065193340	0.41440171821837046	1426163499.000
1712034073	0.17915355536697286	-514338316.000
1526621371	0.5435870488621911	-3797659.000
130081317	0.4014279036721254	NULL
2048481116	0.2107093605121693	1704117927.000
-2067368391	0.5763887172257189	-452165183.000
0	0.9286759330434932	NULL
1021996113	0.737198399943565	NULL
-713573774	0.3021457500334628	NULL
-1680724988	280992707	NULL
1411861402	83084647	NULL
-1710710010	-90593292	-1255979722.000
1844355385	0.6101178479960011	1733503642.000

select cast(group_concat(all r'0.5787210717348131') as decimal) from t0 group by - (abs(- (- (1061572565)))), least(t0.c0, least(cast(0.09300166 as int), t0.c0));
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t0" ("c0" DECIMAL(18,3));
COMMENT ON COLUMN "sys"."t0"."c0" IS 'jc~\006}ℵH{\015﻿^aBPxpf+sP';
COPY 8 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
0.626
0.634
0.133
0.244
19.000
0.455
0.715
0.369

SELECT ALL CASE t0.c0 WHEN VAR_POP(ALL t0.c0) THEN (t0.c0) BETWEEN SYMMETRIC (t0.c0) AND (t0.c0) END FROM t0 GROUP BY t0.c0;
ROLLBACK;

START TRANSACTION;
CREATE TABLE "sys"."t0" ("c0" INT);
COPY 8 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
62183
-2658
-1258
40690
-198
12260
-1827
-604

CREATE TABLE "sys"."t1" ("c0" INT);
COPY 7 RECORDS INTO "sys"."t1" FROM stdin USING DELIMITERS E'\t',E'\n','"';
4440
4440
4440
4440
14228
-4740
NULL

SELECT CASE TIMESTAMP '1970-01-02 23:16:17' WHEN DATE '1970-01-12' THEN 1 END;
SELECT TIME '08:16:10' FROM t1 JOIN t0 ON (t1.c0) NOT BETWEEN SYMMETRIC (t1.c0) AND (charindex(CAST(TIME '04:39:29' AS STRING), CASE COALESCE (TIMESTAMP '1970-01-02 23:16:17', TIMESTAMP '1970-01-02 23:07:33') 
WHEN COALESCE (DATE '1970-01-12', DATE '1970-01-02', DATE '1970-01-02') THEN COALESCE (r'/6望', r'hr?r3QDF*OD%6癰if}䃒5') END, t0.c0)) GROUP BY t1.c0;
ROLLBACK;

START TRANSACTION; -- Bug 6924
CREATE TABLE "sys"."t0" ("a" INTEGER, "b" INTEGER NOT NULL, CONSTRAINT "t0_a_b_unique" UNIQUE ("a","b"));
--This copy into must succeed 
COPY 39 RECORDS INTO "sys"."t0" FROM stdin USING DELIMITERS E'\t',E'\n','"';
-88162543	18
-88162543	20
-15649686	-544149211
-88162543	1544983640
NULL	-22365094
NULL	1606640302
NULL	-2022118335
-706411503	-1573662742
-88162543	117340240
NULL	14
1724946985	-1967779742
NULL	-1500350327
NULL	-174249097
-88162543	29
-88162543	42
10	0
NULL	1861748843
NULL	-1709541615
NULL	-143945879
NULL	1
NULL	1158178587
-88162543	14
-846070788	0
-88162543	1242658499
1149990738	-106077877
NULL	-70926511
NULL	138623502
NULL	-1613851459
NULL	-724706022
NULL	1259669628
NULL	0
NULL	-297079149
1545824064	16
NULL	0
NULL	1526452554
NULL	1813972190
NULL	-30
NULL	-1536805627
NULL	1602659226

SELECT 1 FROM t0 GROUP BY 1, 2 HAVING MAX(TRUE);

SELECT ALL COUNT(ALL DATE '1970-01-02'), ((rtrim(CAST(0.4 AS STRING), trim(r'W', r'1')))||(lower(CAST(((r'3')||(INTERVAL '4' MONTH)) AS STRING)))) FROM t0 WHERE ((t0.b)<=(t0.a)) GROUP BY 0.1, TRUE HAVING MAX(ALL TRUE)
UNION ALL
SELECT COUNT(ALL DATE '1970-01-02'), ((rtrim(CAST(0.4 AS STRING), trim(r'W', r'1')))||(lower(CAST(((r'3')||(INTERVAL '4' MONTH)) AS STRING)))) FROM t0 WHERE ((t0.b)<=(t0.a)) GROUP BY 0.1, TRUE HAVING NOT (MAX(ALL TRUE))
UNION ALL
SELECT ALL COUNT(ALL DATE '1970-01-02'), ((rtrim(CAST(0.4 AS STRING), trim(r'W', r'1')))||(lower(CAST(((r'3')||(INTERVAL '4' MONTH)) AS STRING)))) FROM t0 WHERE ((t0.b)<=(t0.a)) GROUP BY 0.1, TRUE HAVING (MAX(ALL TRUE)) IS NULL;
ROLLBACK;

START TRANSACTION;
CREATE TABLE t0 (c0 BOOLEAN);
create view v1(c0, c1, c2, c3) as (select 1, lower('1'), 1, cot(1) from t0);
SELECT v1.c0 FROM v1 WHERE v1.c1 LIKE v1.c1 AND v1.c3 BETWEEN v1.c3 AND v1.c3 = TRUE;

create view v2(c0, c1, c3) as (select distinct 1, lower('1'), cot(1) from t0);
SELECT v2.c0 FROM v2 WHERE v2.c1 = '1' AND v2.c3 BETWEEN v2.c3 AND v2.c3;

create view v0(c0, c1, c2, c3) as (select distinct 0.1, ((lower((((('&')||(2)))||(0.1))))||((('-1')||(abs(cast(r'1' as int)))))), 0.1, cot(((((- (((2)&(3))))+(abs(4))))*(- (cast(cast(5 as string) as int))))) from t0);
SELECT v0.c0 FROM v0 WHERE NOT (NOT (((((((((NOT (((v0.c1)LIKE(v0.c1))))AND(((v0.c2)>=(v0.c0)))))AND(((v0.c3) BETWEEN SYMMETRIC (v0.c3) AND (v0.c3)) = TRUE)))AND
((((v0.c1)||(((v0.c0)<(v0.c0))))) BETWEEN SYMMETRIC (v0.c1) AND (v0.c1))))AND((0.2) BETWEEN SYMMETRIC (v0.c0) AND (v0.c0)))));
ROLLBACK;

START TRANSACTION;
CREATE TABLE t0(c0 INT);
insert into t0(c0) values (1 between 2 and 3);
insert into t0(c0) values(13), (((cast((0.1) between symmetric (0.2) and (0.3) as int))%(length(upper(r'u鋔wsD30pYi&ᴮ*2*W쉉t+詫sD^#cjX{'))))), (cast(cast(cast(0.12 as int) as string(646)) as int));

SELECT COUNT(t0.c0 = t0.c0 OR 1 BETWEEN ASYMMETRIC 1 AND 1) FROM t0;
SELECT 0.9, COUNT(ALL (((((((CAST(TRUE AS INT))-(t0.c0)))=(t0.c0))) = TRUE)OR((CAST(char_length(r'H') AS INT)) BETWEEN ASYMMETRIC (CAST(-1.3 AS INT)) AND (+ (length(r'0')))))), 0.3 FROM t0 GROUP BY 0.5, 0.4;
ROLLBACK;
