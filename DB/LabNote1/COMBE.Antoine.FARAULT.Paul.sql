-- ------------------------------------------------------
-- NOTE: DO NOT REMOVE OR ALTER ANY LINE FROM THIS SCRIPT
-- ------------------------------------------------------

select 'Query 00' as '';
-- Show execution context
select current_date(), current_time(), user(), database();
-- Conform to standard group by constructs
set session sql_mode = 'ONLY_FULL_GROUP_BY';

-- Write the SQL queries that return the information below:
-- Ecrire les requêtes SQL retournant les informations ci-dessous:

select 'Query 01' as '';
-- The countries of residence the supplier had to ship products to in 2014
-- Les pays de résidence où le fournisseur a dû envoyer des produits en 2014

SELECT residence
FROM customers
NATURAL JOIN orders
WHERE customers.cid = orders.cid
AND YEAR(orders.odate) = 2014;


select 'Query 02' as '';
-- For each known country of origin, its name, the number of products from that country, their lowest price, their highest price
-- Pour chaque pays d'orgine connu, son nom, le nombre de produits de ce pays, leur plus bas prix, leur plus haut prix
SELECT pname, COUNT(*), MAX(price), MIN(price)
FROM products
GROUP BY origin;


select 'Query 03' as '';
-- The customers who ordered in 2014 all the products (at least) that the customers named 'Smith' ordered in 2013
-- Les clients ayant commandé en 2014 tous les produits (au moins) commandés par les clients nommés 'Smith' en 2013
SELECT c.cname
FROM customers c
NATURAL JOIN orders o1
WHERE YEAR(o1.odate) = 2014
AND o1.pid != ALL(
    SELECT DISTINCT o.pid
    FROM orders o
    NATURAL JOIN customers c
    WHERE YEAR(o.odate) = 2013
    AND c.cname = "Smith"
    );


select 'Query 04' as '';
-- For each customer and each product, the customer's name, the product's name, the total amount ordered by the customer for that product,
-- sorted by customer name (alphabetical order), then by total amount ordered (highest value first), then by product id (ascending order)
-- Par client et par produit, le nom du client, le nom du produit, le montant total de ce produit commandé par le client, 
-- trié par nom de client (ordre alphabétique), puis par montant total commandé (plus grance valeur d'abord), puis par id de produit (croissant)
SELECT c.cname, p.pname, SUM(o.quantity) AS totalOrder
FROM customers c
NATURAL JOIN products p
NATURAL JOIN orders o;
WHERE o.pid = p.pid
AND c.cid = o.cid
GROUP BY c.cname;
-- fonctionne pas


select 'Query 05' as '';
-- The customers who only ordered products originating from their country
-- Les clients n'ayant commandé que des produits provenant de leur pays
SELECT DISTINCT c.cname
FROM customers c
NATURAL JOIN orders o
WHERE c.residence = ALL(
    SELECT p.origin
    FROM products p
    NATURAL JOIN orders o
    WHERE o.pid = p.pid
    AND o.cid = c.cid
);


select 'Query 06' as '';
-- The customers who ordered only products originating from foreign countries 
-- Les clients n'ayant commandé que des produits provenant de pays étrangers
SELECT DISTINCT c.cname
FROM customers c
NATURAL JOIN orders o
WHERE c.residence != ALL(
    SELECT p.origin
    FROM products p
    NATURAL JOIN orders o
    WHERE o.pid = p.pid
    AND o.cid = c.cid
);


select 'Query 07' as '';
-- The difference between 'USA' residents' per-order average quantity and 'France' residents' (USA - France)
-- La différence entre quantité moyenne par commande des clients résidant aux 'USA' et celle des clients résidant en 'France' (USA - France)


select 'Query 08' as '';
-- The products ordered throughout 2014, i.e. ordered each month of that year
-- Les produits commandés tout au long de 2014, i.e. commandés chaque mois de cette année
SELECT p.pname, o.odate AS date
FROM products p
NATURAL JOIN orders o
WHERE YEAR(o.odate) = 2014
ORDER BY MONTH(o.odate), DAYOFMONTH(o.odate);

select 'Query 09' as '';
-- The customers who ordered all the products that cost less than $5
-- Les clients ayant commandé tous les produits de moins de $5
SELECT DISTINCT c.cname
FROM customers c
NATURAL JOIN orders o
WHERE o.pid = ALL(SELECT p.pid
    FROM products p
    WHERE p.price < 5);

select 'Query 10' as '';
-- The customers who ordered the greatest number of common products. Display 3 columns: cname1, cname2, number of common products, with cname1 < cname2
-- Les clients ayant commandé le grand nombre de produits commums. Afficher 3 colonnes : cname1, cname2, nombre de produits communs, avec cname1 < cname2
-- Les 2 clients qui ont achetés le plus de fois les mêmes produits
SELECT c1.cname, c2.cname, p.pname
FROM customers c1, customers c2
NATURAL JOIN orders o1
NATURAL JOIN orders o2
NATURAL JOIN products p
WHERE o1.pid = o2.pid
AND o1.cid = o2.cid
AND c1.cname < c2.cname
--fonctionne pas

select 'Query 11' as '';
-- The customers who ordered the largest number of products
-- Les clients ayant commandé le plus grand nombre de produits
SELECT c.cname, SUM(o.quantity) AS quantity
FROM customers c
NATURAL JOIN orders o
GROUP BY c.cname
ORDER by quantity DESC;

select 'Query 12' as '';
-- The products ordered by all the customers living in 'France'
-- Les produits commandés par tous les clients vivant en 'France'
SELECT p.pname
FROM products p
NATURAL JOIN orders o
NATURAL JOIN customers c
WHERE c.residence = "France";

select 'Query 13' as '';
-- The customers who live in the same country customers named 'Smith' live in (customers 'Smith' not shown in the result)
-- Les clients résidant dans les mêmes pays que les clients nommés 'Smith' (en excluant les Smith de la liste affichée)
SELECT c1.cname
FROM customers c1, customers c2
WHERE c1.residence = c2.residence
AND c1.cname != 'Smith'
AND c2.cname = 'Smith';


select 'Query 14' as '';
-- The customers who ordered the largest total amount in 2014
-- Les clients ayant commandé pour le plus grand montant total sur 2014 
SELECT c.cname, SUM(o.quantity) AS quantity
FROM customers c
NATURAL JOIN orders o
WHERE YEAR(o.odate) = 2014
GROUP BY c.cname
ORDER by quantity DESC;

select 'Query 15' as '';
-- The products with the largest per-order average amount 
-- Les produits dont le montant moyen par commande est le plus élevé
SELECT p.pname
FROM products p
NATURAL JOIN orders o
GROUP BY p.pid
ORDER BY AVG(o.quantity) DESC;


select 'Query 16' as '';
-- The products ordered by the customers living in 'USA'
-- Les produits commandés par les clients résidant aux 'USA'
SELECT p.pname
FROM products p
NATURAL JOIN orders o
NATURAL JOIN customers c
WHERE c.residence = "USA";


select 'Query 17' as '';
-- The pairs of customers who ordered the same product en 2014, and that product. Display 3 columns: cname1, cname2, pname, with cname1 < cname2
-- Les paires de client ayant commandé le même produit en 2014, et ce produit. Afficher 3 colonnes : cname1, cname2, pname, avec cname1 < cname2
SELECT c1.cname, c2.cname, p.pname
FROM customers c1, customers c2
NATURAL JOIN orders o1
NATURAL JOIN orders o2
NATURAL JOIN products p
WHERE o1.pid = o2.pid
AND o1.cid = o2.cid
AND c1.cname < c2.cname
AND YEAR(o1.date) = 2014
AND YEAR(o2.date) = 2014;


select 'Query 18' as '';
-- The products whose price is greater than all products from 'India'
-- Les produits plus chers que tous les produits d'origine 'India'
SELECT p.pname
FROM products p
WHERE p.price > ALL(
    SELECT p1.price
    FROM products p1
    WHERE p1.origin = "India");


select 'Query 19' as '';
-- The products ordered by the smallest number of customers (products never ordered are excluded)
-- Les produits commandés par le plus petit nombre de clients (les produits jamais commandés sont exclus)
SELECT p.pname, SUM(o.quantity) AS quantity
FROM products p
NATURAL JOIN orders o
GROUP BY p.pname
ORDER BY quantity ASC;



select 'Query 20' as '';
-- For all countries listed in tables products or customers, including unknown countries: the name of the country, the number of customers living in this country, the number of products originating from that country
-- Pour chaque pays listé dans les tables products ou customers, y compris les pays inconnus : le nom du pays, le nombre de clients résidant dans ce pays, le nombre de produits provenant de ce pays 

select c1.residence from customers c1 left join  products p1 on c1.residence=p1.origin
union
select c2.residence from customers c2 right join products p2 on c2.residence=p2.origin
union
select COUNT(c2.cid)
from customers c2
WHERE c2.residence = c1.residence;
--fonctionne pas