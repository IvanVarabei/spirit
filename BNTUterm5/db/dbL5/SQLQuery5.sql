﻿use ticket;
--Используя операции соединения построить следующие запросы:
--1.	Составить список рейсов, вылетающих из Минска с указанием аэропорта прибытия.
--select flight.flightId, flight.sourceAirportId, flight.cost, airport.airport as arriving 
--from flight
--join airport 
--on flight.sourceAirportId = (select airportId from airport where airport like 'Minsk1')
--	and airport.airportId = flight.destAirportId;
--2.	Составить список клиентов, которые вчера вылетали в Амстердам.
--select client.clientId, client.firstName from 
--client
--join log on client.clientId = log.clientId 
--	and convert(date,flightDate) =convert(date,getDate()-1)
--join flight on log.flightId = flight.flightId
--join airport on flight.destAirportId = airport.airportId 
--	and flight.destAirportId = (select airportId from airport where airport = 'Amsterdam');
--3.	Вывести список продаж за сегодня с указанием номеров рейса, цены, аэропортов отправки и прибытия, данных клиента.
--select log.saleId, flight.flightNumber, flight.cost, airport.airport sourceAirport, 
--secondAirport.airport arrivingAirport, client.firstName, client.lastName
--from log 
--join flight on log.flightId = flight.flightId and saleDate = convert(date,getDate())
--join airport on flight.sourceAirportId = airport.airportId
--join (select * from airport) secondAirport on flight.destAirportId = secondAirport.airportId
--join client on log.clientId = client.clientId;
--4.	Составить список рейсов, прибывающих в Минск сегодня.
--select flight.flightId, log.saleId from flight
--join log on flight.flightId = log.flightId 
--	and  convert(date, flightDate) =  convert(date,getDate())
--join airport on flight.destAirportId = airport.airportId
--	and airport.airportId = (select airportId from airport where airport like 'Minsk1');

--Используя операции UNION, EXCEPT, INTERSECT построить следующие запросы:
--1.	Составить список клиентов, которые приобрели более 1 билета за прошедший месяц.
--select * from client where clientId in(
--	select clientId from log
--	where month(saleDate) = month(dateAdd(m, -1, getDate()))
--	group by clientId
--	having count(*) > 1
--	intersect
--	select clientId from log
--);
--2.	Составить список клиентов, которые приобретали билеты на рейсы, вылетавшие  на прошлой неделе и приобрели 
----билеты на рейсы вылетающие на следующей неделе.
--select client.* from client
--join log on client.clientId = log.clientId and datePart(wk, log.flightDate) = datePart(wk, dateAdd(wk, -1, getDate()))
--	and year(saleDate) = year(getDate())
--intersect
--select client.* from client
--join log on client.clientId = log.clientId and datePart(wk, log.flightDate) = datePart(wk, dateAdd(wk, +1, getDate()))
--	and year(saleDate) = year(getDate());
--3.	Составить список клиентов-однофамильцев.
--select * from client where lastName in(
--select lastName from client
--except
--select lastName from (
--SELECT lastName
--FROM client
--GROUP BY lastName
--HAVING COUNT(*) = 1
--)as T);

--select * from client where lastName in (
--SELECT lastName
--FROM client
--GROUP BY lastName
--HAVING COUNT(*) > 1
--);

