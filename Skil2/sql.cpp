#include "sql.h"
#include <QtSql>

SQL::SQL() {

}

void connect() {
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "student_db.sqlite";
    db.setDatabaseName(dbName);
}
