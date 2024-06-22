#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

void update_employee_by_name(MYSQL *conn, char *name) {
  MYSQL_STMT *stmt;

  char query[1024] =
      "UPDATE employees SET name = ?, salary = ?, position = ?, department = "
      "? "
      "WHERE name = ?";

  char new_name[50];
  double salary;
  char position[50];
  char department[50];
  char salary_string[50];

  printf("Enter name: ");
  fgets(new_name, sizeof(new_name), stdin);
  new_name[strcspn(new_name, "\n")] = 0;

  printf("Enter salary: ");
  fgets(salary_string, sizeof(salary_string), stdin);
  salary = atoi(salary_string);

  printf("Enter position: ");
  fgets(position, sizeof(position), stdin);
  position[strcspn(position, "\n")] = 0;

  printf("Enter department: ");
  fgets(department, sizeof(department), stdin);
  department[strcspn(department, "\n")] = 0;

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

  MYSQL_BIND result[5];
  memset(result, 0, sizeof(result));

  result[0].buffer_type = MYSQL_TYPE_STRING;
  result[0].buffer = new_name;
  result[0].buffer_length = strlen(new_name);

  result[1].buffer_type = MYSQL_TYPE_DOUBLE;
  result[1].buffer = &salary;

  result[2].buffer_type = MYSQL_TYPE_STRING;
  result[2].buffer = position;
  result[2].buffer_length = strlen(position);

  result[3].buffer_type = MYSQL_TYPE_STRING;
  result[3].buffer = department;
  result[3].buffer_length = sizeof(department) - 1;

  result[4].buffer_type = MYSQL_TYPE_STRING;
  result[4].buffer = name;
  result[4].buffer_length = strlen(name);

  if (mysql_stmt_bind_param(stmt, result)) {
    fprintf(stderr, " mysql_stmt_bind_param() failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }

  if (mysql_stmt_execute(stmt)) {
    fprintf(stderr, " mysql_stmt_execute(), failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }

  if (mysql_stmt_close(stmt)) {
    fprintf(stderr, " failed while closing the statement\n");
    fprintf(stderr, " %s\n", mysql_error(conn));
    exit(0);
  }
}

void update_employee_by_id(MYSQL *conn, int employee_id) {
  MYSQL_STMT *stmt;

  char query[1024] =
      "UPDATE employees SET name = ?, salary = ?, position = ?, department = ? "
      "WHERE id = ?";

  char name[50];
  double salary;
  char position[50];
  char department[50];
  char salary_string[50];

  printf("Enter name: ");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = 0;

  printf("Enter salary: ");
  fgets(salary_string, sizeof(salary_string), stdin);
  salary = atoi(salary_string);

  printf("Enter position: ");
  fgets(position, sizeof(position), stdin);
  position[strcspn(position, "\n")] = 0;

  printf("Enter department: ");
  fgets(department, sizeof(department), stdin);
  department[strcspn(department, "\n")] = 0;

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

  MYSQL_BIND result[5];
  memset(result, 0, sizeof(result));

  result[0].buffer_type = MYSQL_TYPE_STRING;
  result[0].buffer = name;
  result[0].buffer_length = strlen(name);

  result[1].buffer_type = MYSQL_TYPE_DOUBLE;
  result[1].buffer = &salary;

  result[2].buffer_type = MYSQL_TYPE_STRING;
  result[2].buffer = position;
  result[2].buffer_length = strlen(position);

  result[3].buffer_type = MYSQL_TYPE_STRING;
  result[3].buffer = department;
  result[3].buffer_length = sizeof(department) - 1;

  result[4].buffer_type = MYSQL_TYPE_LONG;
  result[4].buffer = &employee_id;

  if (mysql_stmt_bind_param(stmt, result)) {
    fprintf(stderr, " mysql_stmt_bind_param() failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }

  if (mysql_stmt_execute(stmt)) {
    fprintf(stderr, " mysql_stmt_execute(), failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }

  if (mysql_stmt_close(stmt)) {
    fprintf(stderr, " failed while closing the statement\n");
    fprintf(stderr, " %s\n", mysql_error(conn));
    exit(0);
  }
}
