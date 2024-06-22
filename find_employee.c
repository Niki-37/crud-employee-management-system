#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

void find_employee_by_name(MYSQL *conn, char *name) {
  MYSQL_STMT *stmt;

  char query[1024] = "SELECT * FROM employees WHERE name = ?";

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

  MYSQL_BIND result[5];
  memset(result, 0, sizeof(result));

  int id;
  char employee_name[50];
  char position[50];
  char department[50];
  double salary;

  result[0].buffer_type = MYSQL_TYPE_LONG;
  result[0].buffer = &id;

  result[1].buffer_type = MYSQL_TYPE_STRING;
  result[1].buffer = employee_name;
  result[1].buffer_length = sizeof(employee_name);

  result[2].buffer_type = MYSQL_TYPE_DOUBLE;
  result[2].buffer = &salary;

  result[3].buffer_type = MYSQL_TYPE_STRING;
  result[3].buffer = position;
  result[3].buffer_length = sizeof(position);

  result[4].buffer_type = MYSQL_TYPE_STRING;
  result[4].buffer = department;
  result[4].buffer_length = sizeof(department);

  if (mysql_stmt_bind_result(stmt, result) != 0) {
    fprintf(stderr, "mysql_stmt_bind_result failed\n");
    mysql_stmt_close(stmt);
    exit(0);
  }

  if (mysql_stmt_fetch(stmt) == MYSQL_NO_DATA) {
    printf("No data found\n");
  } else {
    printf("Id: %d\nName: %s\nSalary: %.2f\nPosition: %s\nDepartment: %s\n\n",
           id, employee_name, salary, position, department);
  }

  if (mysql_stmt_close(stmt)) {
    fprintf(stderr, " failed while closing the statement\n");
    fprintf(stderr, " %s\n", mysql_error(conn));
    exit(0);
  }
}

void find_employee_by_id(MYSQL *conn, int employee_id) {
  MYSQL_STMT *stmt;

  char query[1024] = "SELECT * FROM employees WHERE id = ?";

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

  param[0].buffer_type = MYSQL_TYPE_LONG;
  param[0].buffer = (char *)&employee_id;
  param[0].length = 0;
  param[0].is_null = 0;

  if (mysql_stmt_bind_param(stmt, param) != 0) {
    fprintf(stderr, "mysql_stmt_bind_param_faield\n");
    mysql_stmt_close(stmt);
    exit(0);
  }

  if (mysql_stmt_execute(stmt) != 0) {
    fprintf(stderr, "mysql_stmt_execute failed\n");
    mysql_stmt_close(stmt);
    exit(0);
  }

  MYSQL_BIND result[5];
  memset(result, 0, sizeof(result));

  int id;
  char employee_name[50];
  char position[50];
  char department[50];
  double salary;

  result[0].buffer_type = MYSQL_TYPE_LONG;
  result[0].buffer = &id;

  result[1].buffer_type = MYSQL_TYPE_STRING;
  result[1].buffer = employee_name;
  result[1].buffer_length = sizeof(employee_name);

  result[2].buffer_type = MYSQL_TYPE_DOUBLE;
  result[2].buffer = &salary;

  result[3].buffer_type = MYSQL_TYPE_STRING;
  result[3].buffer = position;
  result[3].buffer_length = sizeof(position);

  result[4].buffer_type = MYSQL_TYPE_STRING;
  result[4].buffer = department;
  result[4].buffer_length = sizeof(department);

  if (mysql_stmt_bind_result(stmt, result) != 0) {
    fprintf(stderr, "mysql_stmt_bind_result failed\n");
    mysql_stmt_close(stmt);
    exit(0);
  }

  if (mysql_stmt_fetch(stmt) == MYSQL_NO_DATA) {
    printf("No data found\n");
  } else {
    printf("Id: %d\nName: %s\nSalary: %.2f\nPosition: %s\nDepartment: %s\n\n",
           id, employee_name, salary, position, department);
  }

  if (mysql_stmt_close(stmt)) {
    fprintf(stderr, " failed while closing the statement\n");
    fprintf(stderr, " %s\n", mysql_error(conn));
    exit(0);
  }
}