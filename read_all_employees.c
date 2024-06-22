#include <mysql/mysql.h>
#include <stdio.h>

void read_all_employees(MYSQL *conn) {
  if (mysql_query(conn, "SELECT * FROM employees")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(0);
  }

  MYSQL_RES *result = mysql_store_result(conn);
  if (result == NULL) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(0);
  }

  MYSQL_ROW row;
  while ((row = mysql_fetch_row(result))) {
    printf("Id: %s\nName: %s\nSalary: %s\nPosition: %s\nDepartment: %s\n\n",
           row[0], row[1], row[2], row[3], row[4]);
  }
  mysql_free_result(result);
}