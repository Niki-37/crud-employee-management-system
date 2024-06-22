#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

void insert_new_employee(MYSQL *conn, char *name, int salary, char *position,
                         char *department) {
  MYSQL_STMT *stmt;
  MYSQL_BIND param[4];

  char query[1024] =
      "INSERT INTO employees (name, salary, position, "
      "department) VALUES (?, ?, ?, ?)";

  stmt = mysql_stmt_init(conn);
  if (!stmt) {
    fprintf(stderr, "mysql_stmt_init failed\n");
    exit(0);
  }

  if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
    fprintf(stderr, "mysql_stmt_prepare failed!\n");
    mysql_stmt_close(stmt);
    exit(0);
  }

  memset(param, 0, sizeof(param));

  param[0].buffer_type = MYSQL_TYPE_STRING;
  param[0].buffer = name;
  param[0].buffer_length = strlen(name);

  param[1].buffer_type = MYSQL_TYPE_LONG;
  param[1].buffer = &salary;

  param[2].buffer_type = MYSQL_TYPE_STRING;
  param[2].buffer = position;
  param[2].buffer_length = strlen(position);

  param[3].buffer_type = MYSQL_TYPE_STRING;
  param[3].buffer = department;
  param[3].buffer_length = strlen(department);

  if (mysql_stmt_bind_param(stmt, param) != 0) {
    fprintf(stderr, "myqsl_stmt_bin_param is failed\n");
    mysql_stmt_close(stmt);
    exit(0);
  }

  if (mysql_stmt_execute(stmt) != 0) {
    fprintf(stderr, "mysql_stmt_execute failed\n");
    mysql_stmt_close(stmt);
    exit(0);
  }

  if (mysql_stmt_close(stmt)) {
    fprintf(stderr, " failed while closing the statement\n");
    fprintf(stderr, " %s\n", mysql_error(conn));
    exit(0);
  }
}
