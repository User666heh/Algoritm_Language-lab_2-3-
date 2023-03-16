#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Pipe.h"
#include "CS.h"
#include "utils.h"
#include <unordered_map>
#include <algorithm>

using namespace std;



void PrintMenu()
{
    cout << "1.Добавить трубу" << endl
        << "2.Добавить КС" << endl
        << "3.Вывести" << endl
        << "4.Редактировать трубу" << endl
        << "5.Редактировать КС" << endl
        << "6.Сохранить" << endl
        << "7.Загрузить" << endl
        << "8.Удалить элемент" << endl
        << "9.Удалить все" << endl
        << "10. Фильтры и пакетное редактирование" << endl
        << "0. Exit" << endl
        << "Выберите действие:";
}

void edit_Pipe(Pipe& t)
{
    cout << "Если труба работает, введите 1. Если труба в нерабочем состоянии, введите 0 ";
    t.status = GetCorrectNumber(0, 1);
}

void save_Pipe(ofstream& file_out, const Pipe& t)
{
    file_out << t.get_ID() << endl << t.length << endl << t.diameter << endl << t.status << endl;
}

void save_CS(ofstream& file_out, const CS& c)
{
    file_out << c.get_ID() << endl << c.name << endl << c.number_of_shops << endl
        << c.number_of_shops_in_work << endl << c.efficiency << endl;
}

void load_Pipe(ifstream& file_in, Pipe& t)
{
    int new_id;
    file_in >> new_id;
    t.set_ID(new_id);
    file_in >> t.length;
    file_in >> t.diameter;
    file_in >> t.status;
}

void load_CS(ifstream& file_in, CS& c)
{
    int new_id;
    file_in >> new_id;
    c.set_ID(new_id);
    getline(file_in >> ws, c.name);
    file_in >> c.number_of_shops;
    file_in >> c.number_of_shops_in_work;
    file_in >> c.efficiency;
}




void edit_CS(CS& t)
{
    int oper;
    cout << "+1 для добавления цеха, -1 для убавления " << endl;
    cin >> oper;
    switch (oper)
    {
    case -1:
        if ((t.number_of_shops_in_work - 1) < 0)
        {
            cout << "Число цехов в работе не может быть меньше 0" << endl;
            edit_CS(t);
        }
        else { t.number_of_shops_in_work -= 1; }
        break;
    case 1:
        if (t.number_of_shops < (t.number_of_shops_in_work + 1))
        {
            cout << "Число цехов в работе не может быть больше числа цехов" << endl;
            edit_CS(t);
        }
        else { t.number_of_shops_in_work += 1; }
        break;
    default:
        cout << "Ошибка, введите указанные выше значения" << endl;;
        cin.clear();
        cin.ignore(1000, '\n');
        edit_CS(t);
        break;
    }
}

Pipe& select_Pipe(unordered_map<int, Pipe>& p)
{
    cout << "Введите индекс(ID): ";
    unsigned int index = GetCorrectNumber(0u, (unsigned int)(Pipe::get_MaxID()));
    return p[index];
}

CS& select_CS(unordered_map<int, CS>& c)
{
    cout << "Введите индекс(ID): ";
    unsigned int index = GetCorrectNumber(0u, (unsigned int)(CS::get_MaxID()));
    return c[index];
}

unsigned int select_Pipe_index(unordered_map<int, Pipe>& p)
{
    cout << "Введите индекс(ID): ";
    unsigned int index = GetCorrectNumber(0u, (unsigned int)(Pipe::get_MaxID()));
    return (index);
}

unsigned int select_CS_index(unordered_map<int, CS>& c)
{
    cout << "Введите индекс(ID): ";
    unsigned int index = GetCorrectNumber(0u, (unsigned int)(CS::get_MaxID()));
    return (index);
}

void del_item(unordered_map<int, Pipe>& p, unordered_map<int, CS>& c)
{
    bool select;
    cout << "Введите: 0 - удалить трубы, 1 - удалить КС" << endl;
    select = GetCorrectNumber(false, true);
    if (select)
    {
        unsigned int select_c = select_CS_index(c);
        if (c.count(select_c) == 1)
            c.erase(select_c);
        else
            cout << "Нет такого элемента" << endl;
    }
    else
    {
        unsigned int select_p = select_Pipe_index(p);
        if (p.count(select_p) == 1)
            p.erase(select_p);
        else
            cout << "Нет такого элемента" << endl;
    }
}

template<typename T>
using Pipe_filter = bool(*)(const Pipe& c, T param);

bool check_by_status(const Pipe& c, bool param)
{
    return c.status == param;
}

template<typename T>
vector<int> find_Pipe_by_filter(const unordered_map<int, Pipe>& Pipes, Pipe_filter<T> f, T param)
{
    vector<int> ID;
    for (auto& c : Pipes)
    {
        if (f(c.second, param))
            ID.push_back(c.first);
    }
    return ID;
}

template<typename T>
using CS_filter = bool(*)(const CS& c, T param);

bool check_by_name(const CS& c, string param)
{
    return (c.name.find(param) != std::string::npos);
}

bool check_by_percent(const CS& c, double param)
{
    return (1 - (double)c.number_of_shops_in_work / (double)c.number_of_shops) * 100 >= param;
}

template<typename T>
vector<int> find_CS_by_filter(const unordered_map<int, CS>& CStations, CS_filter<T> f, T param)
{
    vector<int> ID;
    for (auto& c : CStations)
    {
        if (f(c.second, param))
            ID.push_back(c.first);
    }
    return ID;
}

void change(Pipe& t, const bool& new_status)
{
    if (new_status == 0)
        t.status = 0;
    else
        t.status = 1;
}

void change(CS& c, const bool& edit)
{
    if (edit == 1)
    {
        if (c.number_of_shops_in_work < c.number_of_shops)
            c.number_of_shops_in_work++;
    }
    else
    {
        if (c.number_of_shops_in_work > 0)
            c.number_of_shops_in_work--;
    }
}

vector <int> edit_Pipe_by_ID(unordered_map<int, Pipe>& Pipes, const vector <int>& filted_ID, const bool& with_filter)
{
    vector<int> ID_new;
    cout << "Введите ID нужных труб, для завершения выбора введите -1" << endl;
    unsigned int select;
    while (1)
    {
        select = GetCorrectNumber(-1, (int)(Pipe::get_MaxID()));
        if (select == -1)//Если ввели -1
            break;
        if (Pipes.count(select) == 1)//Если ввели существующий ID
        {
            if (with_filter)//Если передали отфильтрованные
            {
                if (!(std::find(ID_new.begin(), ID_new.end(), select) != ID_new.end()) && (std::find(filted_ID.begin(), filted_ID.end(), select) != filted_ID.end()))// Если элемент есть в filted_ID и ещё не записан в ID_new
                    ID_new.push_back(select);
                else
                    cout << "ID уже выбран или такого ID нет в списке отфильтрованных" << endl;
            }
            else//Если передали все элементы
            {
                if (!(std::find(ID_new.begin(), ID_new.end(), select) != ID_new.end()))// Если элемент ещё не записан в ID_new
                    ID_new.push_back(select);
                else
                    cout << "ID уже был выбран" << endl;
            }
        }
        else
        {
            cout << "Нет такого элемента" << endl;
        }
    }//В этот момент есть вектор нужных для редактирования ID_new
    return ID_new;
}

void batch_editing(unordered_map<int, Pipe>& Pipes)
{
    cout << "Для применения фильтра перед пакетным редактированием введите 1, для работы со всеми трубами введите 0" << endl;
    bool choice_filt;
    choice_filt = GetCorrectNumber(0, 1);
    if (choice_filt)
    {
        vector <int> Pipes_filt;
        cout << "Какие трубы отобрать? 1 - рабочие, 0 - в ремонте " << endl;
        bool status = GetCorrectNumber(0, 1);
        for (int i : find_Pipe_by_filter(Pipes, check_by_status, status))
        {
            cout << Pipes[i] << endl;
            Pipes_filt.push_back(i);
        }
        cout << "Введите 1 для выбора элементов редактирования по ID, для редактирования только отфильтрованных введите 0" << endl;
        bool choice_by_ID = GetCorrectNumber(0, 1);
        if (choice_by_ID) //С выбором ID после фильтра
        {
            vector<int> ID_new = edit_Pipe_by_ID(Pipes, Pipes_filt, 1);
            if (ID_new.size() > 0)
            {
                cout << "Изменение состояния: 1 - выбранные работают, 0 - в нерабочем состоянии, 2 - удалить" << endl;
                int choiсe_status = GetCorrectNumber(0, 2);
                if (choiсe_status == 2)
                {
                    for (int& i : ID_new)
                        Pipes.erase(i);
                }
                else
                {
                    for (int& i : ID_new)
                        change(Pipes[i], choiсe_status);
                }
            }
            else
                cout << "Не выбрано элементов для редактирования" << endl;
        }
        else //Только с фильтром
        {
            if (Pipes_filt.size() > 0)
            {
                cout << "Изменение состояния: 1 - выбранные работают, 0 - в нерабочем состоянии, 2 - удалить" << endl;
                int choiсe_status = GetCorrectNumber(0, 2);
                if (choiсe_status == 2)
                {
                    for (int& i : Pipes_filt)
                        Pipes.erase(i);
                }
                else
                {
                    for (int& i : Pipes_filt)
                        change(Pipes[i], choiсe_status);
                }
            }
            else
                cout << "Не выбрано элементов для редактирования" << endl;
        }
    }
    else //Без фильтра по ID
    {
        cout << "Введите 1 для выбора элементов редактирования по ID, для редактирования всех 0" << endl;
        bool choice_by_ID = GetCorrectNumber(0, 1);
        if (choice_by_ID) //С выбором ID
        {
            vector<int> ID_new = edit_Pipe_by_ID(Pipes, {}, 0);
            if (ID_new.size() > 0)
            {
                cout << "Изменение состояния: 1 - выбранные работают, 0 - в нерабочем состоянии, 2 - удалить" << endl;
                int choiсe_status = GetCorrectNumber(0, 2);
                if (choiсe_status == 2)
                {
                    for (int& i : ID_new)
                        Pipes.erase(i);
                }
                else
                {
                    for (int& i : ID_new)
                        change(Pipes[i], choiсe_status);
                }
            }
            else
                cout << "Не выбрано элементов для редактирования" << endl;
        }
        else//Изменить вообще все
        {
            cout << "Изменение состояния: 1 - выбранные работают, 0 - в нерабочем состоянии, 2 - удалить" << endl;
            int choiсe_status = GetCorrectNumber(0, 2);
            if (choiсe_status == 2)
            {
                for (auto& t : Pipes)
                    Pipes.erase(t.first);
            }
            else
            {
                for (auto& t : Pipes)
                    change(t.second, choiсe_status);
            }
        }
    }
}

vector <int> edit_CS_by_ID(unordered_map<int, CS>& CStations, const vector <int>& filted_ID, const bool& with_filter)
{
    vector<int> ID_new;
    cout << "Введите ID нужных КС, для завершения выбора введите -1" << endl;
    unsigned int select;
    while (1)
    {
        select = GetCorrectNumber(-1, (int)(CS::get_MaxID()));
        if (select == -1)//Если ввели -1
            break;
        if (CStations.count(select) == 1)//Если ввели существующий ID
        {
            if (with_filter)//Если передали отфильтрованные
            {
                if (!(std::find(ID_new.begin(), ID_new.end(), select) != ID_new.end()) && (std::find(filted_ID.begin(), filted_ID.end(), select) != filted_ID.end()))// Если элемент есть в filted_ID и ещё не записан в ID_new
                    ID_new.push_back(select);
                else
                    cout << "ID уже выбран или такого ID нет в списке отфильтрованных" << endl;
            }
            else//Если передали все элементы
            {
                if (!(std::find(ID_new.begin(), ID_new.end(), select) != ID_new.end()))// Если элемент ещё не записан в ID_new
                    ID_new.push_back(select);
                else
                    cout << "ID уже был выбран" << endl;
            }
        }
        else
        {
            cout << "Нет такого элемента" << endl;
        }
    }//В этот момент есть вектор нужных для редактирования ID_new
    return ID_new;
}

void edit_CS_by_ID_with_filter(unordered_map<int, CS>& CStations, vector <int>& CStations_filt)
{
    cout << "Введите 1 для выбора элементов редактирования по ID, для редактирования всех 0" << endl;
    bool choice_by_ID = GetCorrectNumber(0, 1);
    if (choice_by_ID) //С выбором ID с фильтром
    {
        vector<int> ID_new = edit_CS_by_ID(CStations, CStations_filt, 1);
        if (ID_new.size() > 0)
        {
            cout << "Изменение количества работающих цехов: 1 - включить 1 цех, 0 - выключить, 2 - удалить" << endl;
            int choiсe_status = GetCorrectNumber(0, 2);
            if (choiсe_status == 2)
            {
                for (int& i : ID_new)
                    CStations.erase(i);
            }
            else
            {
                for (int& i : ID_new)
                    change(CStations[i], choiсe_status);
            }
        }
        else
            cout << "Не выбрано элементов для редактирования" << endl;
    }
    else//Без ID с фильтром
    {
        cout << "Изменение количества работающих цехов: 1 - включить 1 цех, 0 - выключить, 2 - удалить" << endl;
        int choiсe_status = GetCorrectNumber(0, 2);
        if (choiсe_status == 2)
        {
            for (int& i : CStations_filt)
                CStations.erase(i);
        }
        else
        {
            for (int& i : CStations_filt)
                change(CStations[i], choiсe_status);
        }
    }
}



void batch_editing(unordered_map<int, CS>& CStations)
{
    cout << "0.Работа со всеми КС" << endl
        << "1.Фильтр по названию" << endl
        << "2.Фильтр по проценту незадействованных цехов" << endl;
    switch (GetCorrectNumber(0, 2))
    {
    case 0:
    {
        cout << "Введите 1 для выбора элементов редактирования по ID, для редактирования всех 0" << endl;
        bool choice_by_ID = GetCorrectNumber(0, 1);
        if (choice_by_ID) //С выбором ID без фильтра
        {
            vector<int> ID_new = edit_CS_by_ID(CStations, {}, 0);
            if (ID_new.size() > 0)
            {
                cout << "Изменение количества работающих цехов: 1 - включить 1 цех, 0 - выключить, 2 - удалить" << endl;
                int choiсe_status = GetCorrectNumber(0, 2);
                if (choiсe_status == 2)
                {
                    for (int& i : ID_new)
                        CStations.erase(i);
                }
                else
                {
                    for (int& i : ID_new)
                        change(CStations[i], choiсe_status);
                }
            }
            else
                cout << "Не выбрано элементов для редактирования" << endl;
        }
        else//Без ID и фильтра
        {
            cout << "Изменение количества работающих цехов: 1 - включить 1 цех, 0 - выключить, 2 - удалить" << endl;
            int choiсe_status = GetCorrectNumber(0, 2);
            if (choiсe_status == 2)
            {
                for (auto& c : CStations)
                    CStations.erase(c.first);
            }
            else
            {
                for (auto& c : CStations)
                    change(c.second, choiсe_status);
            }
            break;
        }
    }
    case 1:
    {
        vector <int> CStations_filt;
        cout << "Введите, что должно включать название КС" << endl;
        string name;
        getline(cin >> ws, name);
        for (int i : find_CS_by_filter(CStations, check_by_name, name))
        {
            cout << CStations[i] << endl;
            CStations_filt.push_back(i);
        }
        edit_CS_by_ID_with_filter(CStations, CStations_filt);
        break;
    }
    case 2:
    {
        vector <int> CStations_filt;
        cout << "Введите минимальный процент незадействованных цехов в КС" << endl;
        double min_percent = GetCorrectNumber(0.0, 100.0);
        for (int i : find_CS_by_filter(CStations, check_by_percent, min_percent))
        {
            cout << CStations[i] << endl;
            CStations_filt.push_back(i);
        }
        edit_CS_by_ID_with_filter(CStations, CStations_filt);
        break;
    }
    }//Конец switch
}





int main()
{
    setlocale(0, "");
    unordered_map<int, Pipe> Pipes;
    unordered_map<int, CS> CStations;
    while (true)
    {
        PrintMenu();
        switch (GetCorrectNumber(0, 10))
        {
        case 1:
        {
            Pipe t;
            cin >> t;
            Pipes.emplace(t.get_ID(), t);
            break; //Добавить трубу
        }
        case 2:
        {
            CS c;
            cin >> c;
            CStations.emplace(c.get_ID(), c);
            break; //Добавить КС
        }
        case 3:
        {
            cout << "Трубы: " << endl;
            for (auto& t : Pipes)
                cout << t.second << endl;
            cout << "КС: " << endl;
            for (auto& c : CStations)
                cout << c.second << endl;
            break; //Просмотр объектов
        }
        case 4:
        {
            if (Pipes.size() > 0)
                edit_Pipe(select_Pipe(Pipes));
            else
                cout << "Нет труб для редактирования" << endl;
            break; //Редактировать трубу
        }
        case 5:
        {
            if (CStations.size() > 0)
                edit_CS(select_CS(CStations));
            else
                cout << "Нет КС для редактирования" << endl;
            break; //Редактировать КС
        }
        case 6:
        {
            cout << "Введите название файла для сохранения, на конце укажите формат .txt" << endl;
            string file_name;
            cin >> file_name;
            ofstream file_out;
            file_out.open(file_name, ios::out);
            if (file_out.is_open())
            {
                file_out << Pipes.size() << endl;
                for (auto& t : Pipes)
                    save_Pipe(file_out, t.second);
                file_out << Pipe::get_MaxID() << endl;
                file_out << CStations.size() << endl;
                for (auto& c : CStations)
                    save_CS(file_out, c.second);
                file_out << CS::get_MaxID() << endl;
                file_out.close();
            }
            break; //Сохранить
        }
        case 7:
        {
            cout << "Введите название файла для загрузки, на конце укажите формат .txt" << endl;
            string file_name;
            cin >> file_name;
            ifstream file_in;
            file_in.open(file_name, ios::in);
            if (file_in.is_open())
            {
                int count;
                file_in >> count;
                Pipes.reserve(count);
                while (count--)
                {
                    Pipe t;
                    load_Pipe(file_in, t);
                    Pipes.emplace(t.get_ID(), t);
                }
                int Pipe_max;
                file_in >> Pipe_max;
                Pipe::set_MaxID(Pipe_max);
                file_in >> count;
                //CStations.clear();
                CStations.reserve(count);
                while (count--)
                {
                    CS c;
                    load_CS(file_in, c);
                    CStations.emplace(c.get_ID(), c);
                }
                int CS_max;
                file_in >> CS_max;
                CS::set_MaxID(Pipe_max);
                file_in.close();
            }
            break; //Загрузить
        }
        case 8:
        {
            if ((CStations.size() + Pipes.size()) > 0)
                del_item(Pipes, CStations);
            else
            {
                cout << "Нет элементов для удаления" << endl;
            }
            break;
        }
        case 9:
        {
            Pipes.clear();
            CStations.clear();
            break;
        }
        case 10:
        {
            if (Pipes.size() + CStations.size() != 0)
            {
                cout << "Для работы с трубами, введите 0. Для работы с КС, введите 1" << endl;
                bool choice_CS;
                choice_CS = GetCorrectNumber(0, 1);
                if (choice_CS)
                {
                    if (CStations.size() > 0)
                        batch_editing(CStations);
                    else
                        cout << "Нет КС для редактирования" << endl;
                }
                else
                {
                    if (Pipes.size() > 0)
                        batch_editing(Pipes);
                    else
                        cout << "Нет труб для редактирования" << endl;
                }
            }
            else
                cout << "Нет элементов" << endl;
            break;
        }
        case 0:
        {
            return 0; //Выход
        }
        default:
        {
            cout << "Ошибка, введена несуществующая команда" << endl;
        }
        }
    }
}


