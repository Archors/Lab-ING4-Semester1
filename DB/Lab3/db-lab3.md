# Lab3: Constraints and trigger

[subject](db-lab3-subject.pdf)

### Preamble

Please refer to http://dev.mysql.com/doc/refman/5.0/en/create-trigger.html for the MySQL-specific syntax for declaring triggers. Make sure you use proper SQL delimiters when defining a compound trigger body, as follows:
```
delimiter $$
create trigger MYTRIGGER
before insert on MYTABLE
for each row
begin
-- statement 1;
-- statement 2;
-- statement N;
end $$
delimiter ;
```

#### Exercice 1
Consider the table R(A: int, B: int). Enumerate the SQL statements that could violate the primary constraint.
Let us assume that the DBMS(DataBase Management System) we are using does not provide the primary key constraint. (This is actually the case with MySQL when we are using a storage engine other than InnoDB.)
Emulate the primary key constraint using other means, e.g. constraints and/or triggers.

The examples below are statements that violates the primary key constraint :
```
INSERT INTO R
VALUES (1,1),(1,2)
```

To emulate primary key constraint we can use the following constraints/triggers :
```
ALTER TABLE R
ADD CONSTRAINT U_R UNIQUE(A),
    CONSTRAINT N_R NOT NULL(A);
```



#### Exercice 2
Consider the tables R(A: int, #B: int) and S(B: int, C: int). Enumerate the SQL statements that could violate the foreign constraint. Which statements are always rejected by the DMBS, which other statements are subject to the set null, cascade and default policy?
Let us assume that the DBMS we are using does not provide the foreign key constraint either. Emulate this constraint with constraints and/or triggers for each of the three policies, in that order: set null, cascade and reject (default). We assume that the same policy is used for deletes and updates.


#### Exercice 3
Modify the SQL script that creates the Company database of the previous lab and include the (textual) constraints below.
2/2
* The salary of an employee must be a positive value
* The hire date of an employee must not be after today
* The name of an employee must be in upper case and must not be the empty string
When is the DBMS supposed to check the constraints you’ve just added? Run the modified script and check whether the constraints are effective. Conclude.

#### Exercice 4
Next, further modify the schema of the database to include the following (textual) constraints:
* The salary of an employee must be less than $ 7,500 except for top-level managers,
* The per-department average salary must not be greater than $ 5,000.

#### Exercice 5
Implement the constraint a. of exercise 3 using a trigger.

#### Exercice 6
Create a trigger that ensure that all employee names are stored in upper case.


#### Exercice 7
Create a trigger that keeps track of the salary history of all the employees, starting from the time they were hired to the time they left the company. The trigger fills in the table SALHIST(EID, UDATE, SAL), where EID is the ID of the employee whose salary is updated, UDATE is the date of the update and SAL is the new salary. An employee leaving the company is recorded in the SALHIST table with a null salary.
