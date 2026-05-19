#include "global.h"
#include <windows.h>

void menuTidakValid()
{
    CLEAR_SCREEN;
    cout << "Pilihan tidak valid!\n";
    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void tampilPesan2(string pesan)
{
    CLEAR_SCREEN;
    int panjangPesan = pesan.length();
    int lebarBox = panjangPesan + 10;

    if(lebarBox < 40)
        lebarBox = 40;

    cout << "\n ";

    for(int i = 2; i < lebarBox; i++)
    {
        cout << "_";
    }

    cout << endl;
    cout << "|";

    for(int i = 0; i < lebarBox - 2; i++)
    {
        cout << " ";
    }

    cout << "|\n";

    int sisa = lebarBox - 2 - panjangPesan;
    int kiri = sisa / 2;
    int kanan = sisa - kiri;

    cout << "|";

    for(int i = 0; i < kiri; i++)
        cout << " ";

    cout << pesan;

    for(int i = 0; i < kanan; i++)
        cout << " ";

    cout << "|\n";
    cout << "|";

    for(int i = 0; i < lebarBox - 2; i++)
    {
        cout << " ";
    }

    cout << "|\n";
    cout << "|";

    for(int i = 0; i < lebarBox - 2; i++)
        cout << "_";

    cout << "|\n";
    tungguEnter();
}

void tampilPesan(string pesan)
{
    CLEAR_SCREEN;
    int panjangPesan = pesan.length();
    int lebarBox = panjangPesan + 10;

    if(lebarBox < 40)
        lebarBox = 40;

    cout << "\n ";

    for(int i = 2; i < lebarBox; i++)
    {
        cout << "_";
    }

    cout << endl;
    cout << "|";

    for(int i = 0; i < lebarBox - 2; i++)
    {
        cout << " ";
    }

    cout << "|\n";

    int sisa = lebarBox - 2 - panjangPesan;
    int kiri = sisa / 2;
    int kanan = sisa - kiri;

    cout << "|";

    for(int i = 0; i < kiri; i++)
        cout << " ";

    cout << pesan;

    for(int i = 0; i < kanan; i++)
        cout << " ";

    cout << "|\n";
    cout << "|";

    for(int i = 0; i < lebarBox - 2; i++)
    {
        cout << " ";
    }

    cout << "|\n";
    cout << "|";

    for(int i = 0; i < lebarBox - 2; i++)
        cout << "_";

    cout << "|\n";
    tunggu();
}

void logout(int &state)
{
    CLEAR_SCREEN;
    cout << " _____________________________________________\n";
    cout << "|                                             |\n";
    cout << "|               Logout Berhasil               |\n";
    cout << "|                                             |\n";
    cout << "|_____________________________________________|\n";
    state = 0;
    tunggu();
}

void tungguEnter()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nTekan ENTER untuk kembali...";
    cin.get();
}

void tunggu()
{
    cout << "\nTekan ENTER untuk kembali...";
    cin.get();
}
void tungguClear()
{
    cin.clear();
    cout << "\nTekan ENTER untuk kembali...";
    cin.get();
}   

void gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearArea()
{
    gotoXY(0,0);

    for(int i = 0; i < 50; i++)
    {
        cout << string(120, ' ') << endl;
    }

    gotoXY(0,0);
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor()
{
    setColor(7);
}

int getRarityColor(string rarity)
{
    if(rarity == "Common")
    return 2;
    
    if(rarity == "Rare")
    return 11;
    
    if(rarity == "Epic")
    return 13;
    
    if(rarity == "Legendary")
    return 14;
    
    return 7;
}

int getTypeColor(string rarity)
{
    if(rarity == "Earth")
    return 6;
    
    if(rarity == "Fire")
    return 4;
    
    if(rarity == "Rock")
    return 8;
    
    if(rarity == "Water")
    return 1;

    if(rarity == "Wind")
    return 3;
    
    return 7;
}

void menuSetting()
{
    while(true)
    {
        CLEAR_SCREEN;
        
        cout << "\n __________________________________\n";
        cout << "|            SETTING              |\n";
        cout << "|_________________________________|\n";
        cout << "| 1 | Volume Audio                |\n";
        cout << "| 0 | Kembali                     |\n";
        cout << "|___|_____________________________|\n";
        
        cout << "\nPilih: ";
        
        int pilih;
        cin >> pilih;
        
        if(cin.fail())
        {
            tampilPesan("Input tidak valid!");
            return;
        }
        
        switch(pilih)
        {
            case 1:
            {
                int volume;
                
                cout << "\nVolume (0-100): ";
                cin >> volume;
                
                setVolume(volume);
                tampilPesan("Volume berhasil diubah!");
                break;
            }
            
            case 0:
            return;
            
            default:
            tampilPesan("Menu tidak valid!");
        }
    }
}

// AJIS

string inputClean(string label)
{
    string input = "";
    char ch;

    cout << label;

    while(true)
    {
        ch = _getch();

        // ENTER
        if(ch == 13)
        {
            if(input.empty())
            {
                continue;
            }

            // hapus spasi di akhir
            if(input[input.length() - 1] == ' ')
            {
                input.pop_back();
            }

            cout << endl;
            return input;
        }

        // BACKSPACE
        else if(ch == 8)
        {
            if(!input.empty())
            {
                input.pop_back();
                cout << "\b \b";
            }
        }

        // SPASI
        else if(ch == ' ')
        {
            // blok spasi awal
            if(input.empty())
            {
                continue;
            }

            // blok double spasi
            if(input[input.length() - 1] == ' ')
            {
                continue;
            }

            input += ch;
            cout << ch;
        }

        // HANYA HURUF & ANGKA
        else if(isalnum(ch))
        {
            input += ch;
            cout << ch;
        }
    }
}

int inputAngka(string label)
{
    string input = "";
    char ch;

    cout << label;

    while(true)
    {
        ch = _getch();

        // ENTER
        if(ch == 13)
        {
            if(input.empty())
                continue;

            cout << endl;

            return stoi(input);
        }

        // BACKSPACE
        else if(ch == 8)
        {
            if(!input.empty())
            {
                input.pop_back();
                cout << "\b \b";
            }
        }

        // HANYA ANGKA
        else if(isdigit(ch))
        {
            input += ch;
            cout << ch;
        }
    }
}

void validasiDaftarUser(const string& username, const string& password)
{
    bool username_ada_spasi = false;
    bool password_ada_spasi = false;
    
    if (username.empty() || password.empty())
    {
        throw invalid_argument("Username dan password tidak boleh kosong!");
    }

    for (int i = 0; i < (int)username.length(); i++)
    {
        if (username[i] == ' ')
        {
            username_ada_spasi = true;
            break;
        }
    }

    for (int i = 0; i < (int)password.length(); i++)
    {
        if (password[i] == ' ')
        {
            password_ada_spasi = true;
            break;
        }
    }

    if (username_ada_spasi && password_ada_spasi)
    throw invalid_argument("Username dan password tidak boleh mengandung spasi!");
    else if (username_ada_spasi)
    throw invalid_argument("Username tidak boleh mengandung spasi!");
    else if (password_ada_spasi)
    throw invalid_argument("Password tidak boleh mengandung spasi!");

    if ((int)password.length() < 6)
    {
    throw invalid_argument("Password minimal 6 karakter!");
    }
}

void validasiLogin(const string& username, const string& password)
{
    if(username.empty() || password.empty())
        throw invalid_argument("Username dan password tidak boleh kosong!");
}

void validasiCreateMonster(const string& nama_str, const string& hp_str, const string& attack_str, const string& defense_str, const string& speed_str, const string& type_str, const string& rarity_str)
{
    if(nama_str.empty() || hp_str.empty() || attack_str.empty() || defense_str.empty() || speed_str.empty() || type_str.empty() || rarity_str.empty())
        throw invalid_argument("Semua field harus diisi!");

}

int validasiUserGacha(int jumlah_gacha)
{
    if(jumlah_gacha < 0 || jumlah_gacha > 10)
        throw invalid_argument("Jumlah gacha harus antara 1-10!");
    
    return jumlah_gacha;
}











// ULUNG
