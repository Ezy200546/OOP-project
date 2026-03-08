#include "raylib.h"
#include "User.h"
#include "Product.h"
#include "Cart.h"
#include "Order.h"

#include <cstring>
#include <fstream>
#include <string>

using namespace std;

void saveUserToFile(const string& role, const string& username, const string& password)
{
    ofstream file("users.txt", ios::app);

    if(file.is_open())
    {
        file << role << "," << username << "," << password << endl;
        file.close();
    }
}

bool Button(Rectangle rec, const char* text)
{
    DrawRectangleRec(rec, LIGHTGRAY);
    DrawRectangleLinesEx(rec, 2, DARKGRAY);
    DrawText(text, rec.x + 10, rec.y + 10, 20, BLACK);

    return CheckCollisionPointRec(GetMousePosition(), rec) &&
           IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

enum Screen
{
    HOME,
    LOGIN_MENU,
    REGISTER_MENU,
    LOGIN_BUYER,
    LOGIN_ADMIN,
    REGISTER,
    ADMIN_SCREEN,
    ADMIN_ADD_PRODUCT,
    BUYER_SCREEN
};

int main()
{
    InitWindow(900, 600, "MAHO E-Commerce");
    SetTargetFPS(60);

    Buyer buyers[20];
    Buyer pendingBuyers[20];

    int buyerCount = 0;
    int pendingBuyerCount = 0;

    Buyer* loggedBuyer = NULL;
    Product products[50];

    char username[20] = "";
    char password[20] = "";

    int userLen = 0;
    int passLen = 0;

    bool typingUsername = false;
    bool typingPassword = false;

    const char ADMIN_PASSWORD[] = "admin123";
    char adminPass[20] = "";
    int adminLen = 0;
    bool adminError = false;

    Screen currentScreen = HOME;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScreen == HOME)
        {
            DrawText("MAHO E-COMMERCE", 300, 80, 32, DARKBLUE);

            if (Button({350,220,200,50},"Login"))
                currentScreen = LOGIN_MENU;

            if (Button({350,300,200,50},"Register"))
                currentScreen = REGISTER_MENU;
        }

        else if (currentScreen == LOGIN_MENU)
        {
            DrawText("Login Menu", 360, 100, 30, BLACK);

            if (Button({350,220,200,50},"Login Buyer"))
                currentScreen = LOGIN_BUYER;

            if (Button({350,290,200,50},"Login Admin"))
                currentScreen = LOGIN_ADMIN;

            if (Button({350,360,200,40},"Back"))
                currentScreen = HOME;
        }

        else if (currentScreen == REGISTER_MENU)
        {
            DrawText("Register", 380, 100, 30, BLACK);

            if (Button({350,250,200,50},"Register Buyer"))
                currentScreen = REGISTER;

            if (Button({350,320,200,40},"Back"))
                currentScreen = HOME;
        }

 
        else if (currentScreen == REGISTER)
        {
            DrawText("Buyer Registration", 320, 80, 30, BLACK);

            Rectangle userBox = {360,195,250,35};
            Rectangle passBox = {360,255,250,35};

            DrawText("Username:",240,200,20,BLACK);
            DrawRectangleRec(userBox,LIGHTGRAY);
            DrawRectangleLinesEx(userBox,2,BLACK);
            DrawText(username,370,202,20,BLACK);

            DrawText("Password:",240,260,20,BLACK);
            DrawRectangleRec(passBox,LIGHTGRAY);
            DrawRectangleLinesEx(passBox,2,BLACK);

            char hidden[20] = "";
            for(int i=0;i<passLen;i++) hidden[i] = '*';
            hidden[passLen] = '\0';

            DrawText(hidden,370,262,20,BLACK);

            if(CheckCollisionPointRec(GetMousePosition(), userBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                typingUsername = true;
                typingPassword = false;
            }

            if(CheckCollisionPointRec(GetMousePosition(), passBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                typingUsername = false;
                typingPassword = true;
            }

            int key = GetCharPressed();

            while(key > 0)
            {
                if(key >= 32 && key <= 125)
                {
                    if(typingUsername && userLen < 19)
                    {
                        username[userLen++] = key;
                        username[userLen] = '\0';
                    }

                    if(typingPassword && passLen < 19)
                    {
                        password[passLen++] = key;
                        password[passLen] = '\0';
                    }
                }

                key = GetCharPressed();
            }

            if(IsKeyPressed(KEY_BACKSPACE))
            {
                if(typingUsername && userLen > 0)
                    username[--userLen] = '\0';

                if(typingPassword && passLen > 0)
                    password[--passLen] = '\0';
            }

            if (Button({350,330,200,40},"Submit Registration"))
            {
                pendingBuyers[pendingBuyerCount++] = Buyer(username,password);

                saveUserToFile("Buyer", username, password);

                userLen = 0;
                passLen = 0;

                username[0] = '\0';
                password[0] = '\0';

                currentScreen = HOME;
            }

            if (Button({350,390,200,40},"Back"))
                currentScreen = REGISTER_MENU;
        }

        else if (currentScreen == LOGIN_BUYER)
        {
            DrawText("Buyer Login", 360, 80, 30, BLACK);

            DrawText("Username:",240,200,20,BLACK);
            DrawRectangle(360,195,250,35,LIGHTGRAY);
            DrawText(username,370,202,20,BLACK);

            DrawText("Password:",240,260,20,BLACK);
            DrawRectangle(360,255,250,35,LIGHTGRAY);

            char hidden[20] = "";
            for(int i=0;i<passLen;i++) hidden[i]='*';
            hidden[passLen]='\0';

            DrawText(hidden,370,262,20,BLACK);

            if (Button({350,330,200,40},"Login"))
            {
                for(int i=0;i<buyerCount;i++)
                {
                    if(buyers[i].login(username,password))
                    {
                        loggedBuyer=&buyers[i];
                        currentScreen=BUYER_SCREEN;
                    }
                }
            }

            if(Button({350,390,200,40},"Back"))
                currentScreen=LOGIN_MENU;
        }

        else if(currentScreen==LOGIN_ADMIN)
        {
            DrawText("Admin Login",360,100,30,BLACK);

            DrawRectangle(320,220,260,40,LIGHTGRAY);

            char hidden[20]="";
            for(int i=0;i<adminLen;i++)
                hidden[i]='*';

            DrawText(hidden,330,230,20,BLACK);

            int key=GetCharPressed();

            while(key>0)
            {
                if(key>=32 && key<=125 && adminLen<19)
                {
                    adminPass[adminLen++]=key;
                    adminPass[adminLen]='\0';
                }
                key=GetCharPressed();
            }

            if(IsKeyPressed(KEY_BACKSPACE)&&adminLen>0)
                adminPass[--adminLen]='\0';

            if(Button({350,300,200,40},"Login"))
            {
                if(strcmp(adminPass,ADMIN_PASSWORD)==0)
                {
                    currentScreen=ADMIN_SCREEN;
                    adminError=false;
                }
                else
                    adminError=true;
            }

            if(adminError)
                DrawText("Wrong Password!",350,360,20,RED);

            if(Button({350,400,200,40},"Back"))
                currentScreen=LOGIN_MENU;
        }

        else if(currentScreen==ADMIN_SCREEN)
        {
            DrawText("Admin Dashboard",320,40,30,DARKBLUE);

            DrawText("Pending Buyers:",60,120,22,BLACK);

            int y=160;

            for(int i=0;i<pendingBuyerCount;i++)
            {
                DrawText(pendingBuyers[i].getUsername().c_str(),60,y,20,BLACK);

                if(Button({300,(float)y,90,30},"Accept"))
                {
                    buyers[buyerCount++]=pendingBuyers[i];

                    for(int j=i;j<pendingBuyerCount-1;j++)
                        pendingBuyers[j]=pendingBuyers[j+1];

                    pendingBuyerCount--;
                }

                if(Button({400,(float)y,90,30},"Reject"))
                {
                    for(int j=i;j<pendingBuyerCount-1;j++)
                        pendingBuyers[j]=pendingBuyers[j+1];

                    pendingBuyerCount--;
                }
                

                y+=40;
            }
            if(Button({650,200,200,40},"Add Product"))
            {
                currentScreen = ADMIN_ADD_PRODUCT;
            }

            if(Button({650,320,200,40},"Logout"))
                currentScreen=HOME;
        }
        

        else if(currentScreen == BUYER_SCREEN)
        {
            DrawText("Buyer Dashboard",320,50,30,BLACK);

            if(loggedBuyer != NULL)
            {
                DrawText(
                    TextFormat("Welcome %s",
                    loggedBuyer->getUsername().c_str()),
                    330,100,20,DARKGREEN);
            }

            if(Button({350,500,200,40},"Logout"))
                currentScreen = HOME;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
