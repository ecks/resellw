resellw
=======

Database for Reseller's Warehouse

There are two apps, "admin" and "client". The admin app is for managing the database and allows you to add, modify and delete tuples. The client app does not modify the database. It is there only to facilitate searching through the database. The path to the folder containing the apps is /usa/hasenov/Database_Systems/resellw.

How to compile:

In the current directory type:

make

To clean the object files, type:

make clean

To compile only one app, for instance the client, type:

make client

To compile only the admin app, type:

make admin

How to run:

Assuming you are in the directory containing the binaries, you can type:

./admin

This will run the admin app. You can select through the relevant menus to add, modify and delete tuples. You will not be able to store an Item in more than one Room. You will not be able to use a Price for Listing more than one Item.

To run the client app, simply type:

./client

There are three searches currently implemented. I assume that the table is already populated and all appropriate Items are Stored and Listed. For instance, if you search by Model on a specific Item and it exists in the database but is not added to a Room, the Item will not show up in the search results.

Indexing:

In addition to primary indexes, I chose secondary indexes based on what is most frequently searched for. I initially wanted for equality searching to use hash-based indexing, however it turns out that InnoDB, the current MySQL engine, does not support indexing by hash. Thus, in the database all indexing is stored as a Btree. For the Item table, I chose UPC as a secondary index. For Electronics table, I chose model as a secondary index. For Clothing table, I chose clothing_brand as secondary index. For BathBody table I chose bathbody_brand as secondary index. For Price table I chose sell_price as secondary index. In the Price table, it actually makes sense to store sell_price as Btree, since the the query is a range search. The SQL statements for generating the tables are stored in create_tables.txt file.
