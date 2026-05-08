#include "global.h"

void menuHome(int &state, bool &program_jalan)
{
    CLEAR_SCREEN;
    int pilih;
    

    cout << "\n_________________________________\n";
    cout << "|             HOME              |\n";
    cout << "|_______________________________|\n";
    cout << "| 1 | Login                     |\n";
    cout << "| 2 | Daftar                    |\n";
    cout << "| 3 | Exit                      |\n";
    cout << "|___|___________________________|\n";
    cout << "Pilih: ";

    try {
        cin >> pilih;
        if(cin.fail())
            throw "Input harus berupa angka!";
    }
    catch(const char* msg) {
        tampilPesan(msg);
        return;
    }

    switch(pilih)
    {
        case 1:
            state = 1;
            break;

        case 2:
            state = 2;
            break;

        case 3:
            program_jalan = false;
            break;

        default:
            tampilPesan("Pilihan tidak valid!");
    }
}



void daftarUser(User users[], int &jumlah_user, int &state)
{
    CLEAR_SCREEN;

    cout << "\n______________________\n";
    cout << "|   HALAMAN DAFTAR   |\n";
    cout << "|____________________|\n";

    if(jumlah_user >= 100)
    {
        tampilPesan("Database user penuh!");
        state = 0;
        return;
    }

    string username;
    string password;

    cout << "Username baru : ";
    cin >> username;

    cout << "Password baru : ";
    cin >> password;

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
        users[jumlah_user].deck.jumlah = 0;

        if(jumlah_user > 0)
        {
            users[jumlah_user - 1].next = &users[jumlah_user];
        }

        users[jumlah_user].next = NULL;

        jumlah_user++;

        tampilPesan("User berhasil dibuat");
    }

    state = 0;

    tungguEnter();
}


bool loginUser(User users[], int jumlah_user, int &current_user, int &state, bool &program_jalan)
{
    CLEAR_SCREEN;

    int percobaan = 0;
    bool login_berhasil = false;

    while(percobaan < 3 && !login_berhasil)
    {
        cout << "\n______________________\n";
        cout << "|   HALAMAN LOGIN    |\n";
        cout << "|____________________|\n";

        string username;
        string password;

        cout << "Username : ";
        cin >> username;

        cout << "Password : ";
        cin >> password;

        User* user_sekarang = &users[0];
        int index = 0;

        while(user_sekarang != NULL)
        {
            if(user_sekarang->username == username &&
               user_sekarang->password == password)
            {
                login_berhasil = true;
                percobaan = 0;
                current_user = index;

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
            tampilPesan("Username atau password salah");
            cout << "Sisa percobaan: " << 3 - percobaan << endl;
        }
    }

    if(!login_berhasil)
    {
        tampilPesan("Login gagal 3 kali");
        program_jalan = false;
    }

    tungguEnter();

    return login_berhasil;
}






// AJIS











// ULUNG
