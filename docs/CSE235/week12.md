# CSE235 Week 12: Database with SQLite
Python is commonly used for data processing and data management. Python ships with SQLite3, a lightweight database engine that is optimized for single user access. CPD121 and CPD123 are required for most students who are taking this class, so hopefully you some familiarity with SQL. We will first provide an overview and review of SQL and databases before exploring how it integrates with Python.

## SQLite3
SQLite3 is the third major version of the SQLite database engine. SQLite stores databases as single files, making (small) SQLite databases very portable. The databases used by SQLite are relational databases that are created and queried using SQL. Let's define some terms:   
- SQL - stands for "Structured Query Language". It is the dominant query language for creating, accessing, and modifying relational databases.
- Relational Database - a relational database stores data in "tables" which have schemas. The schemas are the "columns" of these tables. They are called relational databases since different tables are often related to each other via these columns.
- Primary Key - a column (or set of columns) in a database table that is used as the ID for a row. The primary key must be unique and not null (empty). Typically, an integer column that counts up from 0 is used as a primary key.
- Foreign Key - a column (or set of columns) that is used to relate one table to another
- Database - A collection of tables that are used to store data.
- Table - A collection of columns and rows that store data
- Column - A 
- Row - A single data entry in a table 

### Database SQL Commands

### Table SQL Commands

### Querying SQL Commands
These are the commands for querying data from existing tables. 

#### Select
The `SELECT` statement is used to read data from a table. The syntax for a basic `SELECT` statement is as follows:
```sql
SELECT columns FROM table_name;
```
The `columns` can be one to many columns that exist in the table being queried. The `FROM` clause specifies the table being queried. For example, if we had the following "fruit" table:   
  
| id | fruit_name | price |
| -- | ---------- | ----- |
| 1 | Apple | 1.25 |
| 2 | Banana | 1.05 |
| 3 | Orange | 1.50 |

If we only wanted to get the names from the table, we can run the following query:
```sql
SELECT fruit_name FROM fruits;
```
If we want to select all the columns, we can list them all out:
```sql
SELECT id, fruit_name, price FROM fruits;
```
We could also use `SELECT *`, but I don't recommend doing this. If the table is changed later on, the data returned by this query will be changed and could break client code. 

##### Constraints
We can constrain the rows returned by a query using a `WHERE` clause. A `WHERE` clause is added after the `FROM` clause, and allows additional conditions to be added. For example, we can query all fruits that have a price less than or equal to $1.25:
```sql
SELECT fruit_name FROM fruits WHERE price <= 1.25;
```
This will return:  
| fruit_name |
| ---------- |
| Apple |
| Banana |
A `WHERE` clause can consist of any number of 

#### Insert
The `INSERT` statement is used to add new a row(s) to a table. The syntax for an `INSERT` statement is:
```sql
INSERT INTO table_name(column_list) VALUES (value_list);
```
After `INSERT INTO` is the name of the table that the new values will be inserted into. After the table name is the list of columns that the data will be inserted into. 

## Python SQLite3 API
Python provides an API (abstract programming interface) for SQLite3. Like Tkinter, the SQLite3 API ships with Python. To use it, it can be imported like any of the other built-in modules:
```py
import sqlite3
```
The first thing to do is to create a database connection. With SQLite, this is simple, since there is no database server/engine running in the background; the database is just a plain file. The `sqlite3.connect()` function is passed the path to a database file and creates a connection to it.
```py
import sqlite3

connection = sqlite3.connect()
```
The next thing to do is to create a cursor object to execute queries against the database. The `sqlite3.cursor()` function is passed a connection as an argument, and returns a new cursor:
```py
import sqlite3

connection = sqlite3.connect()
cursor = sqlite3.cursor(connection)
```
The cursor object has the method `execute()` associated with it. This can be used to execute SQL commands. For example, we can use the cursor to create a table:
```py
import sqlite3

connection = sqlite3.connect()
cursor = sqlite3.cursor(connection)

# executing a CREATE TABLE command
cursor.execute("""
CREATE TABLE if not exists fruits(
    id INT PRIMARY KEY AUTOINCREMENT,
    fruit_name TEXT NOT NULL,
    price FLOAT NOT NULL
);""")

# inserting values into the table
cursor.execute("""
INSERT INTO fruits(id, fruit_name, price) 
VALUES ()
""")
```
This will create the fruit table from the examples.
