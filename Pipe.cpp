
#include "Pipe.h"
#include "utils.h"
using namespace std;

int Pipe::MaxID = 0;

Pipe::Pipe()
{
    //cout << "Pipe::Pipe()" << endl;
    id = ++MaxID;
    length = 0;
    diameter = 0;
    status = false;
}

//Pipe::Pipe(const Pipe& t)
//{
//	//cout << "Pipe::Pipe(const Pipe& t)" << endl;
//    id = t.id;
//    length = t.length;
//    diameter = t.diameter;
//    status = t.status;
//}

int Pipe::get_MaxID()
{
    return MaxID;
}

void Pipe::set_MaxID(int new_maxID)
{
    MaxID = new_maxID;
}

int Pipe::get_ID() const
{
    return id;
}

void Pipe::set_ID(int ID)
{
    id = ID;
}

ostream& operator << (ostream& out, const Pipe& p)
{
    out << "ID = " << p.id << endl
        << "MaxID = " << Pipe::MaxID << endl
        << "Длина = " << p.length << endl
        << "Диаметр = " << p.diameter << endl
        << "Состояние работы: ";
    if (p.status) { out << "Работает" << endl; }
    else { out << "Не работает" << endl; }
    return out;
}

istream& operator >> (istream& in, Pipe& p)
{
    cout << "Введите длину: ";
    p.length = GetCorrectNumber(0.0000001, 9999999.0);
    cout << "Введите диаметр: ";
    p.diameter = GetCorrectNumber(0.0000001, 9999999.0);
    cout << "Если труба работает, введите 1. Если труба в нерабочем состоянии, введите 0. ";
    p.status = GetCorrectNumber(0, 1);
    return in;
}