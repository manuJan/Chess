/********* CREACCION DE LA BASE DE DATOS CHESS *****/

if not exists (select * from master..sysdatabases where name = 'CHESS.dbo')
  BEGIN	
	CREATE DATABASE Chess
	ON 
	   ( NAME='Chess_Dat',
		FILENAME='E:\Microsoft SQL Server\MSSQL\Data\Chess_Dat.mdf',
		SIZE=50,
		MAXSIZE=100,
		FILEGROWTH=2MB ) 
	LOG ON
	  ( NAME = 'Chess_Log',
	  	FILENAME = 'E:\Microsoft SQL Server\MSSQL\Data\Chess_Log.ldf',
	   	SIZE = 10MB,
   		MAXSIZE = 20MB,
		FILEGROWTH = 1MB )
  END
GO

exec sp_dboption 'Chess', N'trunc. log', 'true'
GO

exec sp_dboption 'Chess' , autoshrink , 'true'
GO


if not exists (select * from master.dbo.syslogins where loginname = 'Chess')
BEGIN
	declare @logindb nvarchar(132), @loginlang nvarchar(132) select @logindb = 'Chess', @loginlang = 'us_english'
	if @logindb is null or not exists (select * from master.dbo.sysdatabases where name = @logindb)
		select @logindb = 'master'
	if @loginlang is null or (not exists (select * from master.dbo.syslanguages where name = @loginlang) and @loginlang <> 'us_english')
		select @loginlang = @@language
	exec sp_addlogin 'Chess', null, @logindb, @loginlang
END
GO

use Chess
GO

/****** Object:  Group  ******/
if not exists (select * from sysusers where name = 'Chess' and uid > 16399)
	EXEC sp_addgroup 'mslGroup'
GO

/****** Object:  User  ******/
if not exists (select * from sysusers where name = 'CHuser' and uid < 16382)
	EXEC sp_adduser 'Chess', 'CHuser', 'mslGroup'
GO






