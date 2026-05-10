#include "global.h"

void loadMonsterCSV(Monster monsters[], int &jumlah)
{
    ifstream file("data/monster.csv");

    if(!file.is_open())
    {
        cout << "monster.csv tidak ditemukan!\n";
        return;
    }

    string line;

    getline(file, line);

    jumlah = 0;

    while(getline(file, line) && jumlah < 100)
    {
        if(line.empty())
            continue;

        try
        {
            stringstream ss(line);

            string temp;

            Monster m;

            // ID
            getline(ss, temp, ',');
            m.status.id = stoi(temp);

            // Nama
            getline(ss, m.status.nama, ',');

            // HP
            getline(ss, temp, ',');
            m.status.hp = stoi(temp);

            // Attack
            getline(ss, temp, ',');
            m.status.attack = stoi(temp);

            // Defense
            getline(ss, temp, ',');
            m.status.defense = stoi(temp);

            // Speed
            getline(ss, temp, ',');
            m.status.speed = stoi(temp);

            // Type
            getline(ss, m.type.tipe, ',');

            monsters[jumlah] = m;

            jumlah++;
        }
        catch(...)
        {
            continue;
        }
    }

    file.close();
}



void saveMonsterCSV(Monster monsters[], int jumlah)
{
    ofstream file("data/monster.csv");

    if(!file.is_open())
    {
        cout << "Gagal membuka monster.csv!\n";
        return;
    }

    file << "id,nama,hp,attack,defense,speed,type\n";

    for(int i = 0; i < jumlah; i++)
    {
        file
        << monsters[i].status.id << ","
        << monsters[i].status.nama << ","
        << monsters[i].status.hp << ","
        << monsters[i].status.attack << ","
        << monsters[i].status.defense << ","
        << monsters[i].status.speed << ","
        << monsters[i].type.tipe
        << "\n";
    }

    file.close();
}

void loadUserCSV(User users[], int &jumlah)
{
    ifstream file("data/user.csv");

    if(!file.is_open())
    {
        cout << "user.csv tidak ditemukan!\n";
        return;
    }

    string line;
    getline(file, line);

    jumlah = 0;

    while(getline(file, line) && jumlah < 100)
    {
        if(line.empty())
            continue;

        try
        {
            stringstream ss(line);

            string temp;

            User u;

            // ID
            getline(ss, temp, ',');
            u.id = stoi(temp);

            // Username
            getline(ss, u.username, ',');

            // Password
            getline(ss, u.password, ',');

            // Role
            getline(ss, u.role, ',');

            // Gold
            getline(ss, temp, ',');
            u.gold = stoi(temp);

            u.deck.jumlah = 0;

            for(int i = 0; i < 3; i++)
            {
                u.active_team[i] = -1;
            }

            u.next = NULL;

            users[jumlah] = u;

            jumlah++;
        }
        catch(...)
        {
            continue;
        }
    }

    for(int i = 0; i < jumlah - 1; i++)
    {
        users[i].next = &users[i + 1];
    }

    if(jumlah > 0)
    {
        users[jumlah - 1].next = NULL;
    }

    file.close();
}

void saveUserCSV(User users[], int jumlah)
{
    ofstream file("data/user.csv");

    if(!file.is_open())
    {
        cout << "Gagal membuka user.csv!\n";
        return;
    }

    file << "id,username,password,role,gold\n";

    for(int i = 0; i < jumlah; i++)
    {
        file
        << users[i].id << ","
        << users[i].username << ","
        << users[i].password << ","
        << users[i].role << ","
        << users[i].gold
        << "\n";
    }

    file.close();
}


void saveDeckCSV(User users[], int jumlah_user)
{
    ofstream file("data/deck.csv");

    if(!file.is_open())
    {
        cout << "Gagal membuka deck.csv!\n";
        return;
    }

    file << "user_id,monster_id,nama,hp,attack,defense,speed,type\n";

    for(int i = 0; i < jumlah_user; i++)
    {
        for(int j = 0;
            j < users[i].deck.jumlah;
            j++)
        {
            UserMonster m =
            users[i].deck.monsters[j];

            file
            << users[i].id << ","
            << m.monster_id << ","
            << m.nama << ","
            << m.hp << ","
            << m.attack << ","
            << m.defense << ","
            << m.speed << ","
            << m.type
            << "\n";
        }
    }

    file.close();
}

void loadDeckCSV(User users[], int jumlah_user)
{
    ifstream file("data/deck.csv");

    if(!file.is_open())
    {
        cout << "deck.csv tidak ditemukan!\n";
        return;
    }

    string line;

    getline(file, line);

    while(getline(file, line))
    {
        if(line.empty())
            continue;

        try
        {
            stringstream ss(line);

            string temp;

            int user_id;

            UserMonster m;

            // USER ID
            getline(ss, temp, ',');
            user_id = stoi(temp);

            // MONSTER ID
            getline(ss, temp, ',');
            m.monster_id = stoi(temp);

            // NAMA
            getline(ss, m.nama, ',');

            // HP
            getline(ss, temp, ',');
            m.hp = stoi(temp);

            // ATTACK
            getline(ss, temp, ',');
            m.attack = stoi(temp);

            // DEFENSE
            getline(ss, temp, ',');
            m.defense = stoi(temp);

            // SPEED
            getline(ss, temp, ',');
            m.speed = stoi(temp);

            // TYPE
            getline(ss, m.type);

            // cari user
            for(int i = 0; i < jumlah_user; i++)
            {
                if(users[i].id == user_id)
                {
                    int idx =
                    users[i].deck.jumlah;

                    if(idx < 30)
                    {
                        users[i]
                        .deck
                        .monsters[idx] = m;

                        users[i]
                        .deck
                        .jumlah++;
                    }
                }
            }
        }
        catch(...)
        {
            continue;
        }
    }

    file.close();
}