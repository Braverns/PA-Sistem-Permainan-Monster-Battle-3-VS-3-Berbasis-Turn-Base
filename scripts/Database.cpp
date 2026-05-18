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

            // status
            getline(ss, temp, ',');
            m.status.id = stoi(temp);
            getline(ss, m.status.nama, ',');
            getline(ss, temp, ',');
            m.status.hp = stoi(temp);
            getline(ss, temp, ',');
            m.status.attack = stoi(temp);
            getline(ss, temp, ',');
            m.status.defense = stoi(temp);
            getline(ss, temp, ',');
            m.status.speed = stoi(temp);
            getline(ss, m.type.tipe, ',');
            getline(ss, m.rarity.rarity, ',');

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

    file << "id,nama,hp,attack,defense,speed,type,rarity\n";

    for(int i = 0; i < jumlah; i++)
    {
        file
        << monsters[i].status.id << ","
        << monsters[i].status.nama << ","
        << monsters[i].status.hp << ","
        << monsters[i].status.attack << ","
        << monsters[i].status.defense << ","
        << monsters[i].status.speed << ","
        << monsters[i].type.tipe << ","
        << monsters[i].rarity.rarity
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


            getline(ss, temp, ',');
            u.id = stoi(temp);
            getline(ss, u.username, ',');
            getline(ss, u.password, ',');
            getline(ss, u.role, ',');
            getline(ss, temp, ',');
            u.gold = stoi(temp);
            getline(ss, temp, ',');
            u.active_team[0] = stoi(temp);
            getline(ss, temp, ',');
            u.active_team[1] = stoi(temp);
            getline(ss, temp, ',');
            u.active_team[2] = stoi(temp);

            u.deck.jumlah = 0;
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

    file << "id,username,password,role,gold,team1,team2,team3\n";

    for(int i = 0; i < jumlah; i++)
    {
        file
        << users[i].id << ","
        << users[i].username << ","
        << users[i].password << ","
        << users[i].role << ","
        << users[i].gold << ","
        << users[i].active_team[0] << ","
        << users[i].active_team[1] << ","
        << users[i].active_team[2]
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

    file << "user_id,monster_id,nama,hp,attack,defense,speed,type,rarity," << "skill1_id,skill2_id,skill3_id\n";

    for(int i = 0; i < jumlah_user; i++)
    {
        for(int j = 0; j < users[i].deck.jumlah; j++)
        {
            UserMonster m = users[i].deck.monsters[j];

            file
            << users[i].id << ","
            << m.monster_id << ","
            << m.nama << ","
            << m.hp << ","
            << m.attack << ","
            << m.defense << ","
            << m.speed << ","
            << m.type << ","
            << m.rarity << ","
            << m.skills[0].id << ","
            << m.skills[1].id << ","
            << m.skills[2].id
            << "\n";
        }
    }

    file.close();
}

Skill cariSkillByID(Skill skills[], int jumlah_skill, int id)
{
    for(int i = 0; i < jumlah_skill; i++)
    {
        if(skills[i].id == id)
        {
            return skills[i];
        }
    }

    Skill kosong;

    kosong.id = -1;
    kosong.nama = "Unknown";
    kosong.element = "None";
    kosong.tipe = "None";
    kosong.power = 0;

    return kosong;
}

void loadDeckCSV(User users[], Skill skills[], int jumlah_user, int jumlah_skill)
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
            int skill1;
            int skill2;
            int skill3;
            stringstream ss(line);
            string temp;
            int user_id;
            UserMonster m;

            getline(ss, temp, ',');
            user_id = stoi(temp);
            getline(ss, temp, ',');
            m.monster_id = stoi(temp);
            getline(ss, m.nama, ',');
            getline(ss, temp, ',');
            m.hp = stoi(temp);
            getline(ss, temp, ',');
            m.attack = stoi(temp);
            getline(ss, temp, ',');
            m.defense = stoi(temp);
            getline(ss, temp, ',');
            m.speed = stoi(temp);
            getline(ss, m.type, ',');
            getline(ss, m.rarity, ',');
            getline(ss, temp, ',');
            skill1 = stoi(temp);
            getline(ss, temp, ',');
            skill2 = stoi(temp);
            getline(ss, temp, ',');
            skill3 = stoi(temp);

            m.skills[0] = cariSkillByID(skills, jumlah_skill, skill1);
            m.skills[1] = cariSkillByID(skills, jumlah_skill, skill2);
            m.skills[2] = cariSkillByID(skills, jumlah_skill, skill3);

            // cari user
            for(int i = 0; i < jumlah_user; i++)
            {
                if(users[i].id == user_id)
                {
                    int idx = users[i].deck.jumlah;

                    if(idx < 30)
                    {
                        users[i].deck.monsters[idx] = m;
                        users[i].deck.jumlah++;
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

void loadSkillCSV(Skill skills[], int &jumlah)
{
    ifstream file("data/skill.csv");

    if(!file.is_open())
    {
        cout << "skill.csv tidak ditemukan!\n";
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
            Skill s;

            
            getline(ss, temp, ',');
            s.id = stoi(temp);
            getline(ss, s.nama, ',');
            getline(ss, s.element, ',');
            getline(ss, s.tipe, ',');
            getline(ss, temp, ',');
            s.power = stoi(temp);

            skills[jumlah] = s;
            jumlah++;
        }
        catch(...)
        {
            continue;
        }
    }

    file.close();
}

void saveSkillCSV(Skill skills[], int jumlah)
{
    ofstream file("data/skill.csv");

    if(!file.is_open())
    {
        cout << "Gagal membuka skill.csv!\n";
        return;
    }

    file << "id,nama,element,tipe,power\n";

    for(int i = 0; i < jumlah; i++)
    {
        file
        << skills[i].id << ","
        << skills[i].nama << ","
        << skills[i].element << ","
        << skills[i].tipe << ","
        << skills[i].power
        << "\n";
    }

    file.close();
}