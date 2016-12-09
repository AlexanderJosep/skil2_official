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
        Person p = Person(name, gender, birthYear, deathYear);
        p.setID(query.value("id").toUInt());
        persons.push_back(p);
    }
    return persons;
}

vector<Computer> Storage::getComputers() {
    vector<Computer> computers;
    QSqlQuery query(database);
    query.exec("SELECT * FROM computers");
    while(query.next()){
        string name = query.value("name").toString().toStdString();
        int yearBuilt = query.value("year_built").toUInt();
        int type = query.value("type").toUInt();
        Computer c = Computer(name, yearBuilt, type);
        c.setID(query.value("id").toUInt());
        computers.push_back(c);
    }
    return computers;
}

vector<Connection> Storage::getConnections() {
    vector<Connection> connections;
    QSqlQuery query(database);
    query.exec("SELECT * FROM connections");
    while(query.next()){
       int personID = query.value("person_id").toUInt();
       int computerID = query.value("computer_id").toUInt();
       Connection c = Connection(personID, computerID);
       c.setID(query.value("id").toUInt());
       connections.push_back(c);
    }
    return connections;
}

vector<SnakeScore> Storage::getSnakeScores(int grid) {
    vector<SnakeScore> scores;
    QSqlQuery query(database);
    query.exec("SELECT * FROM snake_hiscores WHERE grid_size = "+QString::fromStdString(to_string(grid))+"");
    while(query.next()){
       string name = query.value("name").toString().toStdString();
       int score = query.value("score").toUInt();
       int gridSize = query.value("grid_size").toUInt();
       SnakeScore s = SnakeScore(name, score, gridSize);
       scores.push_back(s);
    }
    return scores;
}

bool Storage::savePerson(Person &person) {
    QSqlQuery query(database);
    int id = 1;
    query.exec("SELECT * FROM sqlite_sequence WHERE name='persons'");
    while(query.next()) { // get next auto incr. id
        id = query.value("seq").toString().toUInt() + 1;
        break;
    }
    person.setID(id);

    query.prepare("INSERT INTO persons (name,gender,birth_year,death_year) VALUES "
                  "('"+QString::fromStdString(person.getName())+"',?,?,?)");
    query.addBindValue(QString::fromStdString(to_string(person.getGender())));
    query.addBindValue(QString::fromStdString(to_string(person.getBirthYear())));
    query.addBindValue(QString::fromStdString(to_string(person.getDeathYear())));
    return query.exec();
}

bool Storage::saveComputer(Computer &computer) {
    QSqlQuery query(database);

    int id = 1;
    query.exec("SELECT * FROM sqlite_sequence WHERE name='computers'");
    while(query.next()) { // get next auto incr. id
        id = query.value("seq").toString().toUInt() + 1;
        break;
    }
    computer.setID(id);

    query.prepare("INSERT INTO computers (name,year_built,type) VALUES "
                  "('"+QString::fromStdString(computer.getName())+"',?,?)");
    query.addBindValue(QString::fromStdString(to_string(computer.getYear())));
    query.addBindValue(QString::fromStdString(to_string(computer.getType())));
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

    while(query.next()) { // so it edits only one if there are multiple persons with the same details
        query.prepare("UPDATE persons SET name='"+QString::fromStdString(person.getName())+"',gender=?,birth_year=?,death_year=? WHERE id = "+QString::fromStdString(to_string(query.value("id").toUInt())));
        query.addBindValue(QString::fromStdString(to_string(person.getGender())));
        query.addBindValue(QString::fromStdString(to_string(person.getBirthYear())));
        query.addBindValue(QString::fromStdString(to_string(person.getDeathYear())));
        return  query.exec();
    }
    return false;
}

bool Storage::editComputer(Computer &computer, string name, short yearBuilt, short type) {
    QSqlQuery query(database);
    query.prepare("SELECT * FROM computers WHERE name='"+QString::fromStdString(name)+"' AND year_built=? AND "
                  "type=?");
    query.addBindValue(QString::fromStdString(to_string(yearBuilt)));
    query.addBindValue(QString::fromStdString(to_string(type)));
    query.exec();
    while(query.next()) { // so it edits only one if there are multiple computers with the same details
        query.prepare("UPDATE computers SET name='"+QString::fromStdString(computer.getName())+"',year_built=?,type=? WHERE id = "+QString::fromStdString(to_string(query.value("id").toUInt())));
        query.addBindValue(QString::fromStdString(to_string(computer.getYear())));
        query.addBindValue(QString::fromStdString(to_string(computer.getType())));
        return query.exec();
    }
    return false;
}

bool Storage::removePerson(Person &person) {
   QSqlQuery query(database);
   if(query.exec("DELETE FROM persons WHERE id = "+QString::fromStdString(to_string(person.getID())))) {
       return query.exec("DELETE FROM connections WHERE person_id = "+QString::fromStdString(to_string(person.getID())));
   } else {
       return false;
   }
}

bool Storage::removeComputer(Computer &computer) {
    QSqlQuery query(database);
    if(query.exec("DELETE FROM computers WHERE id = "+QString::fromStdString(to_string(computer.getID())))) {
        return query.exec("DELETE FROM connections WHERE computer_id = "+QString::fromStdString(to_string(computer.getID())));
    } else {
        return false;
    }
}

bool Storage::addConnection(Connection &connection){
    QSqlQuery query(database);
    int id = 1;
    query.exec("SELECT * FROM sqlite_sequence WHERE name='connections'"); // get next auto incr. id
    while(query.next()) {
        id = query.value("seq").toString().toUInt() + 1;
        break;
    }
    connection.setID(id);

    query.prepare("INSERT INTO connections (person_id,computer_id) VALUES "
                  "(?,?)");
    query.addBindValue(QString::fromStdString(to_string(connection.getPersonID())));
    query.addBindValue(QString::fromStdString(to_string(connection.getComputerID())));
    return query.exec();
}

bool Storage::removeConnection(Connection &connection) {
   QSqlQuery query(database);
   return query.exec("DELETE FROM connections WHERE id = "+QString::fromStdString(to_string(connection.getID())));
}


bool Storage::addSnakeScore(string name, int score, int gridSize){
    QSqlQuery query(database);
    query.prepare("SELECT * FROM snake_hiscores WHERE name='"+QString::fromStdString(name)+"' AND grid_size=?");
    query.addBindValue(QString::fromStdString(to_string(gridSize)));
    query.exec();
    int oScore = -1;
    int id = 0;
    while(query.next()) {
        oScore = query.value("score").toString().toUInt();
        id = query.value("id").toString().toUInt();
        break;
    }
    if(oScore > score) {
        return false;
    } else if(score > oScore) {
        if(oScore >= 0) {
            query.prepare("UPDATE snake_hiscores SET score=? WHERE id = "+QString::fromStdString(to_string(id)));
            query.addBindValue(QString::fromStdString(to_string(score)));
        } else {
            query.prepare("INSERT INTO snake_hiscores (name,score,grid_size) VALUES "
                          "('"+QString::fromStdString(name)+"',?,?)");
            query.addBindValue(QString::fromStdString(to_string(score)));
            query.addBindValue(QString::fromStdString(to_string(gridSize)));
            query.exec();
        }
        return true;
    }
    return false;
}

void Storage::close() {
    if(database.open()) {
        database.close(); // close the sql database connection
    }
}
