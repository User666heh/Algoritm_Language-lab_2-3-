
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
        << "����� = " << p.length << endl
        << "������� = " << p.diameter << endl
        << "��������� ������: ";
    if (p.status) { out << "��������" << endl; }
    else { out << "�� ��������" << endl; }
    return out;
}

istream& operator >> (istream& in, Pipe& p)
{
    cout << "������� �����: ";
    p.length = GetCorrectNumber(0.0000001, 9999999.0);
    cout << "������� �������: ";
    p.diameter = GetCorrectNumber(0.0000001, 9999999.0);
    cout << "���� ����� ��������, ������� 1. ���� ����� � ��������� ���������, ������� 0. ";
    p.status = GetCorrectNumber(0, 1);
    return in;
}