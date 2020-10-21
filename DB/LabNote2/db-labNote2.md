# Lab Note 2: Transaction in SQL

[Subject](db-lab4-subject.pdf)

### Preamble

Follow these steps to get your database ready :
1. Toggle your auto-commit mode to 0 : `set autocommit = 0;`
2. Check if the auto-commit is in the right mode : `select @@autocommit;`

## Tasks

### 1. Commit and rollback

I inserted a new dept `INSERT INTO dept VALUES ('50', 'COMPUTING', 'PARIS');` and when i did `SELECT * FROM dept` in the same window the new dept appeared. However in an other window i couldn't see the new department.
When i did a `ROLLBACK` the new department was no longer visible.

### 2. Client failure

I started a new transaction by inserting a new dept `INSERT INTO dept VALUES ('50', 'COMPUTING', 'PARIS');`. I then closed the window and when i reopened it, my dept was not visible.
```
+-----+------------+----------+
| DID | DNAME      | DLOC     |
+-----+------------+----------+
|  10 | ACCOUNTING | NEW-YORK |
|  20 | RESEARCH   | DALLAS   |
|  30 | SALES      | CHICAGO  |
|  40 | OPERATIONS | BOSTON   |
+-----+------------+----------+
```
The same happened when i closed my MySQL Workbench using the task manager, i got the same output.

### 3. Transaction isolation

I executed the following command `show variables like '%isolation%'` and i got this output :
```
+-----------------------+-----------------+
| Variable_name         | Value           |
+-----------------------+-----------------+
| transaction_isolation | REPEATABLE-READ |
| tx_isolation          | REPEATABLE-READ |
+-----------------------+-----------------+
```
In order to prove that the modifications a transaction makes are only visible to that transaction I've opened two MySql Workbench :  
In the first one, in transaction mode, I'm making some changes by adding a computing department : `INSERT INTO dept VALUES ('50', 'COMPUTING', 'PARIS');`  
If i want to see all the department : `SELECT * FROM dept;` from that Workbench :

```
+-----+------------+----------+
| DID | DNAME      | DLOC     |
+-----+------------+----------+
|  10 | ACCOUNTING | NEW-YORK |
|  20 | RESEARCH   | DALLAS   |
|  30 | SALES      | CHICAGO  |
|  40 | OPERATIONS | BOSTON   |
|  50 | COMPUTING  | PARIS    |
+-----+------------+----------+
```
We can see that the new department appear.  
However now I'm making the same query from the second Workbench :
```
+-----+------------+----------+
| DID | DNAME      | DLOC     |
+-----+------------+----------+
|  10 | ACCOUNTING | NEW-YORK |
|  20 | RESEARCH   | DALLAS   |
|  30 | SALES      | CHICAGO  |
|  40 | OPERATIONS | BOSTON   |
+-----+------------+----------+
```
And now the department doesn't appear.  
Now I'm removing this department from the first Workbench : `DELETE FROM dept WHERE did = 50;` and the output is now the same in both Workbench :
```
+-----+------------+----------+
| DID | DNAME      | DLOC     |
+-----+------------+----------+
|  10 | ACCOUNTING | NEW-YORK |
|  20 | RESEARCH   | DALLAS   |
|  30 | SALES      | CHICAGO  |
|  40 | OPERATIONS | BOSTON   |
+-----+------------+----------+
```

### 4. Isolation levels

I repeated the previous experiment but i changed the transaction isolation : `SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;`  
I once again opened two Workbench and i added a new department in the first one: `INSERT INTO dept VALUES ('50', 'COMPUTING', 'PARIS');`  
In the first Workbench the new department appear as expected `SELECT * FROM dept`:

```
+-----+------------+----------+
| DID | DNAME      | DLOC     |
+-----+------------+----------+
|  10 | ACCOUNTING | NEW-YORK |
|  20 | RESEARCH   | DALLAS   |
|  30 | SALES      | CHICAGO  |
|  40 | OPERATIONS | BOSTON   |
|  50 | COMPUTING  | PARIS    |
+-----+------------+----------+
```
In the second Workbench the new department also appeared `SELECT * FROM dept`:

```
+-----+------------+----------+
| DID | DNAME      | DLOC     |
+-----+------------+----------+
|  10 | ACCOUNTING | NEW-YORK |
|  20 | RESEARCH   | DALLAS   |
|  30 | SALES      | CHICAGO  |
|  40 | OPERATIONS | BOSTON   |
|  50 | COMPUTING  | PARIS    |
+-----+------------+----------+
```
So we can conclude that this isolation level allow uncommitted changed to be read by other transactions.  
We can see all the different isolation level [here](https://www.geeksforgeeks.org/transaction-isolation-levels-dbms/#:~:text=Read%20Uncommitted%20%E2%80%93%20Read%20Uncommitted%20is,not%20isolated%20from%20each%20other.&text=Serializable%20%E2%80%93%20This%20is%20the%20Highest%20isolation%20level.).

### 5. Isolation levels - Continued

I repeated the previous experiment but i changed the transaction isolation : `SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;`  
I once again opened two Workbench and i added a new department in the first one: `INSERT INTO dept VALUES ('50', 'COMPUTING', 'PARIS');`  
If i want to see all the department : `SELECT * FROM dept;` from that Workbench :

```
+-----+------------+----------+
| DID | DNAME      | DLOC     |
+-----+------------+----------+
|  10 | ACCOUNTING | NEW-YORK |
|  20 | RESEARCH   | DALLAS   |
|  30 | SALES      | CHICAGO  |
|  40 | OPERATIONS | BOSTON   |
|  50 | COMPUTING  | PARIS    |
+-----+------------+----------+
```
We can see that the new department appear.  
However now I'm making the same query from the second Workbench :
```
+-----+------------+----------+
| DID | DNAME      | DLOC     |
+-----+------------+----------+
|  10 | ACCOUNTING | NEW-YORK |
|  20 | RESEARCH   | DALLAS   |
|  30 | SALES      | CHICAGO  |
|  40 | OPERATIONS | BOSTON   |
+-----+------------+----------+
```
Serializable is the highest isolation level. It avoid to get errors like Dirty Reads, Non-repeatable read and Phantoms. It's the same source as above [Source](https://www.geeksforgeeks.org/transaction-isolation-levels-dbms/#:~:text=Read%20Uncommitted%20%E2%80%93%20Read%20Uncommitted%20is,not%20isolated%20from%20each%20other.&text=Serializable%20%E2%80%93%20This%20is%20the%20Highest%20isolation%20level.)

### 6. JDBC code
