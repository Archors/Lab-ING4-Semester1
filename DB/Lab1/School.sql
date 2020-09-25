CREATE DATABASE school;
use school;
create table students(
    id varchar(20),
    firstname varchar(20),
    lastname varchar(20),
    schoolyear INT,
    primary key (id),
    CHECK (schoolyear >= 1 and schoolyear <= 5)
);
create TABLE courses(
    id varchar(20),
    name varchar(20),
    duration TIME,
    schoolyear INT,
    PRIMARY KEY (id)
);
CREATE table students_courses(
    studentID varchar(20),
    courseID varchar(20),
    grade int,
    CONSTRAINT firstForeignKey FOREIGN KEY (studentID) REFERENCES students (id),
    CONSTRAINT secondForeignKey FOREIGN KEY (courseID) REFERENCES courses (id),
    UNIQUE (studentID, courseID)
);
