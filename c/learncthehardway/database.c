#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


#define MAX_DATA 512
#define MAX_ROWS 100

typedef struct {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
} Address;

typedef struct {
    Address rows[MAX_ROWS];
} Database;

typedef struct {
    FILE *file;
    Database *db;
} Connection;


void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void
database_load(Connection *conn)
{
    int rc = fread(conn->db, sizeof(Database), 1, conn->file);
    if(rc != 1) die("Failed to load database.");
}

void
database_close(Connection *conn)
{
    if (conn)
    {
        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
}

Connection *
database_open(const char *filename, char mode)
{
    Connection *conn = malloc(sizeof(Connection));
    if (!conn) die("Memory error");

    conn->db = malloc(sizeof(Database));
    if (!conn->db) die("Memory error");

    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    }
    else {
        conn->file = fopen(filename, "r+");
        if(conn->file) {
            database_load(conn);
        }
    }

    if(!conn->file) die("Failed to open the file");
    return conn;
}

void
address_print(Address *addr)
{
    printf("ID\t%d\tName\t%s\tEmail\t%s\n", addr->id, addr->name, addr->email);
}

void
database_get(Connection *conn, int id)
{
    Address *addr = &conn->db->rows[id];
    if (addr->set)
        address_print(addr);
    else
        die("ID not set.");
}


void
database_create(Connection *conn)
{
    for (int i=0; i < MAX_ROWS; ++i)
    {
        Address addr = {.id = i, .set = 0};
        conn->db->rows[i] = addr;
    }
}

void
database_list(Connection *conn)
{
    for (int i=0; i < MAX_ROWS; ++i)
    {
        Address *addr = &conn->db->rows[i];
        if (addr->set)
        {
            address_print(addr);
        }
    }
}

void
database_set(Connection *conn, int id, const char *name, const char *email)
{
    Address *addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first");

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, MAX_DATA);
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed");

    res = strncpy(addr->email, email, MAX_DATA);
    if(!res) die("Email copy failed");

    printf("Database SET OK ID:%d Name:%s\n", id, name);
}

void
database_delete(Connection *conn, int id)
{
    Address *addr = &conn->db->rows[id];
    if(!addr->set) die("Record does not exist");
    addr->set = 0;
    printf("Record deleted ID:%d Name:%s\n", id, addr->name);
}

void
database_write(Connection *conn)
{
    rewind(conn->file);
    int rc = fwrite(conn->db, sizeof(Database), 1, conn->file);
    if(rc != 1) die("Failed to write database.");

    rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.");
}


int
main(int argc, char *argv[])
{
    if (argc < 3)
        die("USAGE: ./database <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    Connection *conn = database_open(filename, action);
    int id = 0;
    if (argc > 3) id = atoi(argv[3]);
    if(id >= MAX_ROWS) die("There's not that many records.");

    switch(action) {
        case 'c':
            database_create(conn);
            database_write(conn);
            break;
        case 's':
            if(argc != 6) die("Need id, name, email to set");
            database_set(conn, id, argv[4], argv[5]);
            database_write(conn);
            break;
        case 'd':
            if(argc != 4) die("Need id to delete");
            database_delete(conn, id);
            database_write(conn);
            break;
        case 'g':
            if(argc != 4) die("Need an id to get");
            database_get(conn, id);
            break;
        case 'l':
            database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    database_close(conn);

    return 0;
}
