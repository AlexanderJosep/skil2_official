#include "storage.h"

Storage::Storage() {
    this -> dbName = dbName;
    this -> database = QSqlDatabase::addDatabase("QSQLITE");
    this -> database.setDatabaseName("verk_db.sqlite");
    this -> database.open();
}

vector<Person> Storage::getPersons() {
    vector<Person> persons;
    QSqlQuery query(database);
    query.exec("SELECT * FROM persons");
    while(query.next()){
        string name = query.value("name").toString().toStdString();
        int gender = query.value("gender").toUInt();
        int birthYear = query.value("birth_year").toUInt();
        int deathYear = query.value("death_year").toInt();
        cout << name << " " << gender << " " << birthYear << " " << deathYear << endl;
        persons.push_back(Person(name, gender, birthYear, deathYear));
    }
    return persons;
}

bool Storage::savePerson(Person &person) {
    QSqlQuery query(database);
    query.prepare("INSERT INTO persons (name,gender,birth_year,death_year) VALUES "
                  "('"+QString::fromStdString(person.getName())+"',?,?,?)");
    query.addBindValue(QString::fromStdString(to_string(person.getGender())));
    query.addBindValue(QString::fromStdString(to_string(person.getBirthYear())));
    query.addBindValue(QString::fromStdString(to_string(person.getDeathYear())));
    return query.exec();
}

bool Storage::editPerson(Person &person, int index) {
    QSqlQuery query(database);
    query.prepare("UPDATE persons SET name='"+QString::fromStdString(person.getName())+"',gender=?,birth_year=?,death_year=? WHERE id = ?");
    query.addBindValue(QString::fromStdString(to_string(person.getGender())));
    query.addBindValue(QString::fromStdString(to_string(person.getBirthYear())));
    query.addBindValue(QString::fromStdString(to_string(person.getDeathYear())));
    query.addBindValue(QString::fromStdString(to_string(index)));
    return query.exec();
}

bool Storage::removePerson(int index) {
    QSqlQuery query(database);
    query.prepare("DELETE FROM persons WHERE id = ?");
    query.addBindValue(QString::fromStdString(to_string(index)));
    return query.exec();
}



