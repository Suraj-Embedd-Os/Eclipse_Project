#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main(void) {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "your_user", "your_password",
                           "your_database", 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    if (mysql_query(con, "DROP TABLE IF EXISTS TestTable")) {
        finish_with_error(con);
    }

    if (mysql_query(con, "CREATE TABLE TestTable(Id INT, Name TEXT)")) {
        finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO TestTable VALUES(1, 'John Doe')")) {
        finish_with_error(con);
    }

    if (mysql_query(con, "INSERT INTO TestTable VALUES(2, 'Jane Doe')")) {
        finish_with_error(con);
    }

    if (mysql_query(con, "SELECT * FROM TestTable")) {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);
    mysql_close(con);

    exit(0);
}
