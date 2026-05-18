#include "global.h"
#include <cctype>

void menuHome(int &state, bool &program_jalan)
{
    int cursor = 0;

    string menu[4] =
    {
        "Login",
        "Daftar",
        "Setting",
        "Exit"
    };

    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n __________________________________\n";
        cout << "|                                  |\n";
        cout << "|         BATTLE MONSTER           |\n";
        cout << "|__________________________________|\n";

        for(int i = 0; i < 4; i++)
        {
            cout << "| ";

            if(cursor == i)
                cout << ">> ";
            else
                cout << "   ";

            cout << left << setw(28) << menu[i]  << "  |\n";
        }

        cout << "|__________________________________|\n";

        cout << "\nGunakan UP/DOWN dan ENTER\n";

        char tombol = _getch();

        // ARROW
        if(tombol == -32)
        {
            tombol = _getch();

            // ATAS
            if(tombol == 72)
            {
                playSFX(L"music/cursor3.wav");

                cursor--;

                if(cursor < 0)
                    cursor = 3;
            }

            // BAWAH
            else if(tombol == 80)
            {
                playSFX(L"music/cursor3.wav");

                cursor++;

                if(cursor > 3)
                    cursor = 0;
            }
        }

        // ENTER
        else if(tombol == 13)
        {
            switch(cursor)
            {
                case 0:
                    state = 1;
                    return;

                case 1:
                    state = 2;
                    return;

                case 2:
                    menuSetting();
                    break;

                case 3:
                    program_jalan = false;
                    return;
            }
        }
    }
}



void daftarUser(User users[], int &jumlah_user, int &state)
{
    CLEAR_SCREEN;

    cout << "\n______________________\n";
    cout << "|   HALAMAN DAFTAR   |\n";
    cout << "|____________________|\n";

    try {
        if(jumlah_user >= 100)
        {
            tampilPesan("Database user penuh!");
            state = 0;
            return;
        }

        string username;
        string password;
    
        username = inputClean("Username : ");
        password = inputClean("Password : ");
        validasiDaftarUser(username, password);
    
        bool username_ada = false;
    
        for(int i = 0; i < jumlah_user; i++)
        {
            if(users[i].username == username)
            {
                username_ada = true;
            }
        }
    
        if(username_ada)
        {
            tampilPesan("Username sudah dipakai!");
        }
        else
        {
            users[jumlah_user].id = jumlah_user;
            users[jumlah_user].username = username;
            users[jumlah_user].password = password;
            users[jumlah_user].role = "user";
    
            users[jumlah_user].gold = 1000;
            users[jumlah_user].next_deck_id = 1;
            users[jumlah_user].deck.jumlah = 0;
    
            for(int i = 0; i < 3; i++)
            {
                users[jumlah_user].active_team[i] = -1;
            }
    
            if(jumlah_user > 0)
            {
                users[jumlah_user - 1].next = &users[jumlah_user];
            }
    
            users[jumlah_user].next = NULL;
    
            jumlah_user++;
            saveUserCSV(users, jumlah_user);
    
            tampilPesan("User berhasil dibuat");
        }

        state = 0;

    } catch (const invalid_argument& e) {
        tampilPesan(e.what());
        state = 2;
    }
}

bool loginUser(User users[], int jumlah_user, int &current_user, int &state, bool &program_jalan)
{
    CLEAR_SCREEN;
 
    int percobaan = 0;
    bool login_berhasil = false;
 
    while(percobaan < 3 && !login_berhasil)
    {
        CLEAR_SCREEN;
 
        cout << "\n______________________\n";
        cout << "|   HALAMAN LOGIN    |\n";
        cout << "|____________________|\n";
        cout << "Percobaan ke-" << percobaan + 1 << " dari 3\n";
 
        try
        {
            string username;
            string password;
 
            username = inputClean("Username : ");
            password = inputClean("Password : ");
            validasiLogin(username, password);
 
            User* user_sekarang = &users[0];
            int index = 0;
 
            while(user_sekarang != NULL)
            {
                if(user_sekarang->username == username &&
                   user_sekarang->password == password)
                {
                    login_berhasil = true;
                    current_user   = index;
 
                    if(user_sekarang->role == "admin")
                        state = 3;
                    else
                        state = 4;
 
                    break;
                }
 
                user_sekarang = user_sekarang->next;
                index++;
            }
            if(!login_berhasil)
            {
                percobaan++;
                tampilPesan("Username atau password salah! Sisa percobaan: " + to_string(3 - percobaan));
            }
        }
        catch(const invalid_argument& e)
        {
            tampilPesan(e.what());
        }
    }
 
    if(!login_berhasil)
    {
        tampilPesan("Login gagal 3 kali");
        program_jalan = false;
    }
 
    return login_berhasil;
}










// ULUNG
