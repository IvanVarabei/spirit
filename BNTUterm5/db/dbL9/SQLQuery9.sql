﻿use ticket;
--1.	Создать скалярную функцию для вычисления выручки от продажи билетов на рейс, номер и дата которого вводятся.
go
--alter FUNCTION countRevenue(@flightNuber int, @flightDate date)
--RETURNS smallmoney
--AS
--BEGIN
--DECLARE @revenue smallmoney
--set @revenue = (select sum(cost) from log
--join flight on convert(date, flightDate) = @flightDate 
--and @flightNuber = flightNumber)
--Return @revenue
--END
--go
--Select dbo.countRevenue(24, Cast('10/10/2020' as date))
--2.	Создать табличную  функцию для вывода списка пассажиров на рейс, номер и дата которого вводятся.
--go
--drop function dbo.findClientList;
--go
--create FUNCTION findClientList(@flightNuber int, @flightDate date)
--RETURNS table
--AS
--return (select client.* from log
--join flight on convert(date, flightDate) = @flightDate 
--and @flightNuber = flightNumber
--join client on log.clientId = client.clientId)
--go
--Select * from dbo.findClientList(24, Cast('10/10/2020' as date))
--3.	Создать многострочную табличную функцию для формирования списка рейсов и выручки от продажи билетов на них за прошлый месяц.
--drop function dbo.findFlightListAndRevenueLastMonth;
--go
--create FUNCTION findFlightListAndRevenueLastMonth()
--RETURNS @flightRevenue table(
--	flightId int,
--	flightNumber int,
--	cost smallmoney,
--	revenue smallmoney
--)
--AS
--BEGIN
--	insert @flightRevenue
--		select log.flightId, flightNumber, cost, sum(cost)  from log 
--		join flight on log.flightId = flight.flightId 
--		and month(saleDate) = month(dateAdd(m, -1, getDate())) 
--		and year(saleDate) = year(GETDATE())
--		group by log.flightId, flightNumber, cost
--Return 
--END
--go
Select * from dbo.findFlightListAndRevenueLastMonth()