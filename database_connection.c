#include <mysql/mysql.h>
#include <stdio.h>

MYSQL *open_connection(const char *host, const char *user, const char *password,
                       const char *database) {
  MYSQL *conn = mysql_init(NULL);
  if (conn == NULL) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(0);
  }
  printf("Opening MySQL connection...\n\n");

  if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) ==
      NULL) {
    printf("error: %s\n", mysql_error(conn));
    mysql_close(conn);
    exit(0);
  }
  return conn;
}

void close_connection(MYSQL *conn) {
  printf("\nClosing the connection...\n");
  mysql_close(conn);
}