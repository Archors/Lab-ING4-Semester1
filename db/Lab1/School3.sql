CREATE DATABASE school3;
use school;
create table students(
    id varchar(20),
    firstname varchar(20),
    lastname varchar(20),
    schoolyear INT,
    CHECK (schoolyear >= 1 and schoolyear <= 5)
);
create TABLE courses(
    id varchar(20),
    name varchar(20),
    duration TIME,
    schoolyear INT,
);
CREATE table students_courses(
    studentID varchar(20),
    courseID varchar(20),
    grade int,
    UNIQUE (studentID, courseID)
);
