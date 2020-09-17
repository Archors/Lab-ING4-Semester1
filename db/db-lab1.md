# Lab1 - Creating a database

[subject](db-lab1-subject.pdf)

## 1. Database modeling
```
Student(#lastName, #firstName, schoolYear)
Course(#name, schoolYear, duration)
Enrollment(_studentLastName, _studentFirstName, _courseName, finalGrade)
```


###### Does your schema allows a student to be enrolled in several courses, or a course to have no enrolled student? How is this represented?
* Yes, we can insert several entries for the same `Student` in `Enrollment`.
* Yes, we can create a `Course` without using it into the `Enrollment` table.
Those result are explained by the `Enrollment` table which contain all of the foreign keys.


## 2. Database modeling - alternate solution
```
Student(#id, lastName, firstName, schoolYear)
Course(#code, name, schoolYear, duration)
Enrollment(_studentId, _courseCode, finalGrade)
```


## 3. Comparing the two models
###### Disk space usage.
The disk space usage is quite similar. There is only one more field in the alternate solution.


## 4. Creating and Populating the Database
Creating tables:
```
create table Student(
  id int,
  firstName varchar(200),
  lastName varchar(200),
  schoolYear int
  );

create table Course(
  code varchar(200),
  name varchar(200),
  schoolYear int,
  duration int
  );

create table Enrollment(
  studentId int,
  courseCode varchar(200),
  finalGrade int
  );
```

Populating tables:
```
insert into Student(id, firstName, lastName, schoolYear)
values
(123456789, "Salim", "DUPONT", 4);

insert into Course(code, name, school, duration)
values
("INGPA-INF4000-13", "Database", 27);

insert into Enrollment(studentId, courseCode, schoolYear, finalGrade)
values
(123456789, "INGPA-INF4000-13", 4, 18)
```

Checking tables:
```
select * from Student;

select * from Course;

select * from Enrollment;
```

There isn't any link between tables but we can still do whatever we want on each one.


## 5. Database script
school.SQL
```
create table Student(
  id int,
  firstName varchar(200),
  lastName varchar(200),
  schoolYear int
  );

alter table Student
add constraint pm1 primary key(id);

create table Course(
  code varchar(200),
  name varchar(200),
  schoolYear int,
  duration int
  );

alter table Course
add constraint pm2 primary key(code);

create table Enrollment(
  studentId int,
  courseCode varchar(200),
  finalGrade int
  );

alter table Enrollment
add (foreign key(studentId) references Student(id),
     foreign key(courseCode) references Course(code));

insert into Student(id, firstName, lastName, schoolYear)
values
(123456789, "Salim", "DUPONT", 4);

insert into Course(code, name, schoolYear, duration)
values
("INGPA-INF4000-13", "Database", 4, 27);

insert into Enrollment(studentId, courseCode, finalGrade)
values
(123456789, "INGPA-INF4000-13", 18)
```
We need to create Student and Course and define their primary keys to define foreign key on Enrollment. It's also work for populating tables.


## 5. Database script
* Insert a new student whose school year is not known (2 methods)
```
insert into Student(id, firstName, lastName)
values
(18, "Pierre", "DU");

insert into Student(19, "Paul", "DO", 0);
```

* Change the duration of the Database course from 27 to 30 hours.
```
set duration=30
where name=’Database’;
```

* Change the name of the Databases course to Advanced Databases.
```
set name="Advanced Databases"
where name="Database";
```


## 8. Database script
This attribute should go into the Enrollment table. We can simply add it to the current database with the alter table function.
```
alter table Enrollment
add courseWorkGrade int;
```
