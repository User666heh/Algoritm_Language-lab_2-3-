#include "CS.h"
#include "utils.h"
using namespace std;


int CS::MaxID = 0;

CS::CS()
{
    //cout << "CS::CS()" << endl;
    id = ++MaxID;
    number_of_shops = 0;
    number_of_shops_in_work = 0;
    efficiency = 0;
    name = "����������";
}

//CS::CS(const CS& c)
//{
//    //cout << "CS::CS(const CS& c)" << endl;
//    number_of_shops = c.number_of_shops;
//    number_of_shops_in_work = c.number_of_shops_in_work;
//    efficiency = c.efficiency;
//    name = c.name;
//}

std::string CS::get_name() const
{
    return name;
}

void CS::set_name(std::string new_name)
{
    name = new_name;
}

int CS::get_MaxID()
{
    return MaxID;
}

void CS::set_MaxID(int new_maxID)
{
    MaxID = new_maxID;
}

int CS::get_ID() const
{
    return id;
}

void CS::set_ID(int ID)
{
    id = ID;
}

istream& operator >> (istream& in, CS& p)
{
    cout << "������� �������� ��: ";
    getline(cin >> ws, p.name);
    cout << "������� ����� �����: ";
    p.number_of_shops = GetCorrectNumber(1, 999999999);
    cout << "������� ����� ���������� �����: ";
    p.number_of_shops_in_work = GetCorrectNumber(0, p.number_of_shops);
    cout << "������� �������������: ";
    p.efficiency = GetCorrectNumber(0.0, 99999999.0);
    return in;
}

ostream& operator << (ostream& out, const CS& p)
{
    out << "ID = " << p.id << endl
        << "MaxID = " << CS::MaxID << endl
        << "�������� = " << p.name << endl
        << "����� ����� = " << p.number_of_shops << endl
        << "����� ����� � ������: " << p.number_of_shops_in_work << endl
        << "�������������:" << p.efficiency << endl;
    return out;
}
