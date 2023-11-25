#include <iostream>
#include <time.h>
#include <windows.h>
#define MAX_TRIES 6
using namespace std;


void setup();
void game();
void menu();
void color(unsigned int);
bool check_number(unsigned int);
unsigned int generate_secret(bool);
void get_digits(int vector[5], unsigned int number);
bool exists(int vector[5], int digit);

const char* menu_options[3] = {
    "Play With Random Digits",
    "Play With Unique Digits",
    "Exit"
};

void setup()
{
    srand(time(NULL));
}

void game(bool random_digits)
{
    unsigned int secret = generate_secret(random_digits);
    int secret_digits[5];
    int guess_digits[5];
    get_digits(secret_digits, secret);
    unsigned int guess;
    int i;
    for(i = 0; i < MAX_TRIES; i++)
    {
        cout << " \nYour Guess: ";
        do 
        {
            cin >> guess;
        }
        while(check_number(guess) == false);

        get_digits(guess_digits, guess);
        for(int j = 0; j < 5; j++)
        {
            if(secret_digits[j] == guess_digits[j])
            {
                color(2);
                cout << guess_digits[j];
            }
            else if(exists(secret_digits, guess_digits[j]))
            {
                color(6);
                cout << guess_digits[j];
            }
            else
            {
                color(7);
                cout << guess_digits[j];
            }
            color(7);


        }
            
            

        if(guess == secret)
        {
            cout << " gg\n";
            system("pause");
            break;
        }
    }    
    
    if(i == MAX_TRIES + 1000)
    {
        cout << "bg";
    }



    getchar();
}

void menu()
{
    unsigned int index = 0;
    while(true)
    {
        system("cls");
        for(int i = 0; i < 3; i++)
        {
            if(i == index)
            {
                color(2);
            }
            else
            {
                color(7);
            }
            cout << menu_options[i];
            if(i == index)
            {
                cout << " <--";
            }
            cout << '\n';
            color(7);
            
        }
        if(GetAsyncKeyState(VK_UP))
        {
            if(index == 0)
            {
                index = 2;
            }
            else
            {
                index--;
            }
            Sleep(300);
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            if(index == 2)
            {
                index = 0;
            }
            else
            {
                index++;
            }
            Sleep(300);
        }
        if(GetAsyncKeyState(VK_CONTROL))
        {
            if(index == 0)
            {
                game(true);
            }
            else if(index == 1)
            {
                game(false);
            }
            else
            {
                exit(0);
            }
            Sleep(300);
        }
    }
}

void color(unsigned int id)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), id);
}

unsigned int generate_secret(bool random_digits)
{
    unsigned int secret = rand() % 90000 + 10000;
    if(random_digits == false)
    {  
        unsigned int freq[10] = {};
        unsigned int aux = secret;
        while(aux != 0)
        {
            unsigned int digit = aux % 10;
            freq[digit]++;
            aux = aux / 10;
        }
        for(int i = 0; i < 10; i++)
        {
            if(freq[i] > 1)
            {
                return generate_secret(random_digits);
            }
        }
    }
    return secret;
}

bool check_number(unsigned int n)
{
    if(n > 10000 && n < 99999)
    {
        return true;
    }
    else
    {
        return false;
    }
 
}

void get_digits(int vector[5], unsigned int number)
{
    vector[4] = number % 10;    
    vector[3] = (number / 10) % 10;
    vector[2] = (number / 100) % 10;
    vector[1] = (number / 1000) % 10;
    vector[0] = number / 10000;

}

bool exists(int vector[5], int digit)
{
    for(int i = 0; i < 5; i++)
    {
        if(vector[i] == digit)
        {
            return true;
        }

    }
    return false;
}

int main()
{
    setup();
    menu();
}