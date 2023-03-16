#pragma once
#include <iostream>
class Pipe
{
    int id;
    static int MaxID;
public:
    double length;
    double diameter;
    bool status;

    Pipe();
    //Pipe(const Pipe& t);
    //~Pipe();

    static int get_MaxID();
    static void set_MaxID(int new_maxID);

    int get_ID() const;
    void set_ID(int ID);

    friend std::ostream& operator << (std::ostream& out, const Pipe& p);
    friend std::istream& operator >> (std::istream& in, Pipe& p);
};