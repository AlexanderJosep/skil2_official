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

bool Storage::editPerson(Person &person, string name, short gender, short birthYear, short deathYear) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM persons WHERE name='"+QString::fromStdString(name)+"' AND gender=? AND "
                  "birth_year=? AND death_year=?");
    query.addBindValue(QString::fromStdString(to_string(gender)));
    query.addBindValue(QString::fromStdString(to_string(birthYear)));
    query.addBindValue(QString::fromStdString(to_string(deathYear)));
    query.exec();

    while(query.next()) { // so it edits only one if there are multiple persons
        query.prepare("UPDATE persons SET name='"+QString::fromStdString(person.getName())+"',gender=?,birth_year=?,death_year=? WHERE id = "+QString::fromStdString(to_string(query.value("id").toUInt())));
        query.addBindValue(QString::fromStdString(to_string(person.getGender())));
        query.addBindValue(QString::fromStdString(to_string(person.getBirthYear())));
        query.addBindValue(QString::fromStdString(to_string(person.getDeathYear())));
        return  query.exec();
    }
    return false;
}

bool Storage::removePerson(Person &person) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM persons WHERE name='"+QString::fromStdString(person.getName())+"' AND gender=? AND "
                  "birth_year=? AND death_year=?");
    query.addBindValue(QString::fromStdString(to_string(person.getGender())));
    query.addBindValue(QString::fromStdString(to_string(person.getBirthYear())));
    query.addBindValue(QString::fromStdString(to_string(person.getDeathYear())));

    query.exec();
    while(query.next()) { // so it deletes only 1 if there are multiple people with the same details
        return query.exec("DELETE FROM persons WHERE id = "+QString::fromStdString(to_string(query.value("id").toUInt())));
    }
    return false;
}



