# LabNote2: Transaction in SQL

[Subject](db-lab4-subject.pdf)

### Preamble

Follow these steps to get your database ready :
1. Toggle your autocommit mode to 0 : `set autocommit = 0`
2. Check if the autocommit is in the right mode : `select @@autocommit`

## Tasks

### Commit and rollback

I inserted a new dept `INSERT INTO dept VALUES ('50', 'COMPUTING', 'PARIS');` and when i did `SELECT * FROM dept` in the same window the new dept appeared. However in an other window i could'nt see the new department.
When i did a `ROLLBACK` the new department was no longer visible.

### Client failure

I started a new transaction inserted a new dept and i then closed the window. When i reopend it, my dept was not visible. The same happend when i closed my MySQL Workbench.
