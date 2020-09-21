#Lab 2: Advanced SQL queries
[subject](db-lab2-subject.pdf)

select * from emp where comm is not null;
select count(ename) from emp;
select count(ename) from emp where comm is not null;
select avg(comm) from emp where comm is not null;
