# Examples

Currently, this program does not allow data insertion. Therefore, I have a builtin relation called **Employee** with two attributes id: integer, name: string. 

You can run the following command in ssql:

```sql
select id from Employee;
select name from Employee;
select E1.id, E2.name from Employee E1, Employee E2;
```

## TODO

It does not support fancy features of modern DBMS like joins, where clause, group by clause, having clause and so on.
These features might come later (or never).
