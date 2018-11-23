START TRANSACTION;
CREATE TABLE OID_TBL(f1 oid);
INSERT INTO OID_TBL(f1) VALUES ('1234');
INSERT INTO OID_TBL(f1) VALUES ('1235');
SELECT * FROM OID_TBL WHERE f1 = 1234;
SELECT * FROM OID_TBL WHERE f1 <> 1234;
SELECT * FROM OID_TBL WHERE f1 = '1234';

INSERT INTO OID_TBL(f1) VALUES (NULL);
SELECT * FROM OID_TBL WHERE f1 = 1234;
SELECT * FROM OID_TBL WHERE f1 <> 1234;
SELECT * FROM OID_TBL WHERE f1 = '1234';
ROLLBACK;
