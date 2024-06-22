#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

void delete_employee_by_id(MYSQL *conn, int employee_id) {
  MYSQL_STMT *stmt;

  char query[1024] = "DELETE FROM employees WHERE id = ?";

  stmt = mysql_stmt_init(conn);
  if (!stmt) {
    fprintf(stderr, "failed mysql_stmt_init\n");
    exit(0);
  }

  if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
    fprintf(stderr, "mysql_stmt_prepare failed\n");
    mysql_stmt_close(stmt);
    exit(0);
  }

  MYSQL_BIND param[1];
  memset(param, 0, sizeof(param));

  param[0].buffer_type = MYSQL_TYPE_LONG;
  param[0].buffer = &employee_id;

  if (mysql_stmt_bind_param(stmt, param) != 0) {
    fprintf(stderr, "mysql_stmt_bind_param failed\n");
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

void delete_employee_by_name(MYSQL *conn, char *name) {
  MYSQL_STMT *stmt;

  char query[1024] = "DELETE FROM employees WHERE name = ?";

  stmt = mysql_stmt_init(conn);
  if (!stmt) {
    fprintf(stderr, "mysql_stmt_init failed");
    exit(0);
  }

  if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
    fprintf(stderr, "mysql_stmt_prepare failed\n");
    mysql_stmt_close(stmt);
    exit(0);
  }

  MYSQL_BIND param[1];
  memset(param, 0, sizeof(param));

  param[0].buffer_type = MYSQL_TYPE_STRING;
  param[0].buffer = name;
  param[0].buffer_length = strlen(name);

  if (mysql_stmt_bind_param(stmt, param) != 0) {
    fprintf(stderr, "mysql_stmt_bind_param failed\n");
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