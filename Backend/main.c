#define DEBUG_LEVEL 0

#define TOKEN_DUMP if(DEBUG_LEVEL & 1)
#define TRACE_PARSER if(DEBUG_LEVEL & 2)
#define TRACE_AST if(DEBUG_LEVEL & 4)
#define VAR_DUMP if(DEBUG_LEVEL & 8)
#define TRACE_VARS if(DEBUG_LEVEL & 16)
#define DUMP_PATHS if(DEBUG_LEVEL & 32)
#define DUMP_SQL_GETTER if(DEBUG_LEVEL & 64)
#define TRACE_SYS_FILE_READ_CALLS if(DEBUG_LEVEL & 128)



#define LIST_2D(...) (char *[]){__VA_ARGS__}


#include "https/https.c"




int main() {
    
    bind_signal_handlers();
/*
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Connect to MySQL
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        //return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "127.0.0.1", "admin", "Aa123456!@#",
                           "web", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        //return EXIT_FAILURE;
    } */

/*
    if(0) printf("Insert Done.\nRows affected: %d.\n", 
        insert_row(conn, "web", "users", 
            LIST_2D("username","password","full_name"), 
            LIST_2D("test","test","INSERT GOOD"), 
            3
        ).affected_rows);

    SQL_RESULT result_seq = 
        select_rows(conn, 
            "web", "users", 
            "full_name, seq",
            LIST_2D("username", "password"), 
            LIST_2D("itamar", "Aa123456"), 
            2,
            "and"
        );

    // print_sql_result(&result_seq);
    free_sql_result(&result_seq);

   

    
    
    
    if(0) printf("Update Done.\nRows affected: %d.\n", 
        update_row(conn, "web", "users", 
            LIST_2D("username","password","full_name"), 
            LIST_2D("test","test","UPDATE GOOD"), 
            3,
            "seq", 
            "12"
        ).affected_rows);



    SQL_RESULT result;
    get_rows_sql_file(conn, "/home/itamar/Workspace/sql/users.sql", &result);
    print_sql_result(&result);
    free_sql_result(&result);

//*/
    https_start();
  //  mysql_close(conn);
    return 0;
}


//*

//*/
