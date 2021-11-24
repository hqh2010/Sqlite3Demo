# 说明

This is a demo for sqlite3.

sqlite3 基础知识

sqlite3 命令分两类

系统命令 以  .  开头的命令

.q    退出sqlite3命令模式

.open 创建一个数据库

.databases 列出数据库

.schema 列出表结构

.tables 列出数据库中的表

.help帮助命令

sql命令 以 分号 ; 结尾的命令

增删改查请参考代码

# 使用方式

sudo `apt install libsqlite3-dev`

sudo `apt install sqlite3`

创建数据库

sqlite3

.open userinfo.db

uthuqinghong@uthuqinghong:/media/uthuqinghong/EEECE1A7ECE169F3/13.sqlite/src$ sqlite3
SQLite version 3.27.2 2019-02-25 16:06:06
Enter ".help" for usage hints.
Connected to a transient in-memory database.
Use ".open FILENAME" to reopen on a persistent database.
sqlite> .open userinfo.db
sqlite> .tables
student
sqlite> .databases
main: /media/uthuqinghong/EEECE1A7ECE169F3/13.sqlite/src/userinfo.db
sqlite> .schema
CREATE TABLE student(         ID INTEGER PRIMARY KEY AUTOINCREMENT,         name VARCHAR(32) NOT NULL,         sex CHAR(10),         score INTEGER         );
CREATE TABLE sqlite_sequence(name,seq);
sqlite> select * from student
...> ;
1|zhangsan|男|78
2|lili|女|80
3|wangwu|女|81

`g++ main.cpp -g -I/usr/include -lsqlite3 -o main`

# 运行

./main

# 参考文档

[https://www.runoob.com/sqlite/sqlite-autoincrement.html]()
