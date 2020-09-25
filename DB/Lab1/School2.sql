CREATE DATABASE school2;
use school2;
CREATE table students(
    firstname varchar(20),
    lastname varchar(20),
    schoolyear INT,
    coursename varchar(20),
    grade INT,
    UNIQUE(firstname,lastname)
);
CREATE TABLE courses(
    name varchar(20),
    duration TIME,
    schoolyear INT,
    UNIQUE (name)
);