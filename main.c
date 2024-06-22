#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MYSQL *open_connection(const char *host, const char *user, const char *password,
                       const char *database);
void insert_new_employee(MYSQL *conn, char *name, int salary, char *position,
                         char *department);
void read_all_employees(MYSQL *conn);
void close_connection(MYSQL *conn);
void delete_employee_by_id(MYSQL *conn, int employee_id);
void delete_employee_by_name(MYSQL *conn, char *name);
void find_employee_by_name(MYSQL *conn, char *name);
void find_employee_by_id(MYSQL *conn, int employee_id);
void update_employee_by_id(MYSQL *conn, int employee_id);
void update_employee_by_name(MYSQL *conn, char *name);

enum Department { HR, IT, Sales, Marketing, Support };

struct Employee {
  int id;
  char name[50];
  double salary;
  char position[50];
  enum Department department;
};

int main() {
  MYSQL *conn = open_connection("localhost", "root", "password", "employees");

  printf("Welcome to the Employee Management System!\n");
  printf("0. Exit the system\n");
  printf("1. Add new employee\n");
  printf("2. Delete employee by id\n");
  printf("3. Delete employee by name\n");
  printf("4. Find employee by id\n");
  printf("5, Find employee by name\n");
  printf("6. Update employee by id\n");
  printf("7. Update employee by name\n");
  printf("8. List all employees\n");

  while (true) {
    int use_input;
    char string_user_input[50];

    fgets(string_user_input, sizeof(string_user_input), stdin);
    use_input = atoi(string_user_input);

    switch (use_input) {
      case 0:
        close_connection(conn);
        exit(0);
        break;

      case 1:
        int id;
        char id_string[50];
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

        insert_new_employee(conn, name, salary, position, department);
        break;

      case 2:
        printf("Enter id: ");
        fgets(id_string, sizeof(id_string), stdin);
        id = atoi(id_string);

        delete_employee_by_id(conn, id);
        break;

      case 3:
        printf("Enter name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        delete_employee_by_name(conn, name);
        break;

      case 4:
        printf("Enter id: ");
        fgets(id_string, sizeof(id_string), stdin);
        id = atoi(id_string);

        find_employee_by_id(conn, id);
        break;

      case 5:
        printf("Enter name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        find_employee_by_name(conn, name);
        break;

      case 6:
        printf("Enter id: ");
        fgets(id_string, sizeof(id_string), stdin);
        id = atoi(id_string);

        update_employee_by_id(conn, id);
        break;

      case 7:
        printf("Enter name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        update_employee_by_name(conn, name);
        break;

      case 8:
        read_all_employees(conn);
        break;

      default:
        break;
    }
  }

  close_connection(conn);
  exit(0);
}
