#ifndef CONNECTION_H
#define CONNECTION_H


class Connection {
public:
    Connection(int personID, int computerID);
    int getID(); // get sql id
    int getPersonID(); // get person id
    int getComputerID(); // get computer id
    void setID(int id); // sets the sql id
private:
    int id;
    int personID;
    int computerID;
};

#endif // CONNECTION_H
