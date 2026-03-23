#include "raylib.h"
#include "User.h"
#include "Product.h"
#include "Cart.h"
#include "Payment.h"
#include "BKashPayment.h"
#include "CashOnDelivery.h"
#include "BKashAccounts.h"

#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

// -------- BUTTON --------
bool Button(Rectangle rec, const char* text)
{
    DrawRectangleRec(rec, LIGHTGRAY);
    DrawRectangleLinesEx(rec, 2, DARKGRAY);
    DrawText(text, rec.x + 10, rec.y + 10, 20, BLACK);

    return CheckCollisionPointRec(GetMousePosition(), rec) &&
           IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

// -------- SCREENS --------
enum Screen
{
    HOME,
    LOGIN,
    REGISTER,
    ADMIN_LOGIN,
    ADMIN,
    BUYER,
    ADD_PRODUCT,
    CART_SCREEN,
    PAYMENT_SCREEN
};

const char ADMIN_PASS[] = "admin123";

char adminInput[20] = "";
int adminLen = 0;

bool adminError = false;
int main()
{
    InitWindow(900, 600, "E-Commerce System");
    SetTargetFPS(60);

    // USERS
    Buyer buyers[20], pending[20];
    int buyerCount = 0, pendingCount = 0;
    Buyer* loggedBuyer = NULL;

    // CART
    Cart cart;

    // INPUT
    char username[20] = "";
    char password[20] = "";
    int userLen = 0, passLen = 0;

    // PRODUCT INPUT
    char pname[30] = "";
    char pcat[30] = "";
    char pprice[10] = "";
    char pstock[10] = "";

    int nameLen=0, catLen=0, priceLen=0, stockLen=0;

    // PAYMENT
    char bkashNumber[20] = "";
    int bkashLen = 0;

    // ADMIN
    const char ADMIN_PASS[] = "admin123";
    char adminPass[20] = "";
    int adminLen = 0;
    bool adminError = false;

    Screen screen = HOME;

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // ================= HOME =================
        if(screen == HOME)
        {
            DrawText("MAHO E-COMMERCE", 250, 80, 30, DARKBLUE);

            if(Button({350,200,200,50},"Login"))
                screen = LOGIN;

            if(Button({350,270,200,50},"Register"))
                screen = REGISTER;
        }

        // ================= REGISTER =================
        else if(screen == REGISTER)
        {
            DrawText("Register Buyer", 320, 80, 30, BLACK);

            DrawText("Username:",250,200,20,BLACK);
            DrawRectangle(380,195,250,35,LIGHTGRAY);
            DrawText(username,390,202,20,BLACK);

            DrawText("Password:",250,260,20,BLACK);
            DrawRectangle(380,255,250,35,LIGHTGRAY);
            DrawText(password,390,262,20,BLACK);

            int key = GetCharPressed();
            while(key > 0)
            {
                if(key >= 32 && key <= 125)
                {
                    if(userLen < 19)
                    {
                        username[userLen++] = key;
                        username[userLen] = '\0';
                    }
                }
                key = GetCharPressed();
            }

            if(IsKeyPressed(KEY_BACKSPACE) && userLen>0)
                username[--userLen]='\0';

            if(Button({350,330,200,40},"Submit"))
            {
                pending[pendingCount++] = Buyer(username,password);

                username[0]=password[0]='\0';
                userLen=passLen=0;

                screen = HOME;
            }

            if(Button({350,390,200,40},"Back"))
                screen = HOME;
        }

        // ================= LOGIN =================
        else if(screen == LOGIN)
        {
            DrawText("Login", 380, 80, 30, BLACK);

            if(Button({350,200,200,40},"Buyer Login"))
                screen = BUYER;

           if(Button({350,260,200,40},"Admin Login"))
                screen = ADMIN_LOGIN;
        }

        // ================= ADMIN =================
        else if(screen == ADMIN)
        {
            DrawText("Admin Panel", 330, 40, 30, DARKBLUE);

            int y = 120;

            for(int i=0;i<pendingCount;i++)
            {
                DrawText(pending[i].getUsername().c_str(), 50, y, 20, BLACK);

                if(Button({250,(float)y,80,30},"Accept"))
                {
                    buyers[buyerCount++] = pending[i];

                    for(int j=i;j<pendingCount-1;j++)
                        pending[j]=pending[j+1];

                    pendingCount--;
                }

                if(Button({350,(float)y,80,30},"Reject"))
                {
                    for(int j=i;j<pendingCount-1;j++)
                        pending[j]=pending[j+1];

                    pendingCount--;
                }

                y+=40;
            }

            if(Button({600,200,200,40},"Add Product"))
                screen = ADD_PRODUCT;

            if(Button({600,260,200,40},"Logout"))
                screen = HOME;
        }

        // ================= ADD PRODUCT =================
        else if(screen == ADD_PRODUCT)
        {
            DrawText("Add Product", 350, 80, 30, BLACK);

            DrawRectangle(300,200,250,35,LIGHTGRAY);
            DrawText(pname,310,205,20,BLACK);

            int key = GetCharPressed();
            while(key>0)
            {
                if(nameLen<29)
                {
                    pname[nameLen++] = key;
                    pname[nameLen]='\0';
                }
                key=GetCharPressed();
            }

            if(Button({350,300,200,40},"Save"))
            {
                Product p(rand()%1000, pname, "General", atof(pprice), 10);
                p.saveToFile();

                pname[0]='\0';
                nameLen=0;

                screen = ADMIN;
            }
        }

        // ================= BUYER =================
        else if(screen == BUYER)
        {
            DrawText("Buyer Dashboard", 320, 50, 30, BLACK);

            if(Button({350,200,200,40},"Add Fake Product"))
            {
                Product p(1,"Phone","Electronics",500,10);
                cart.addItem(p,1);
            }

            if(Button({350,260,200,40},"View Cart"))
                screen = CART_SCREEN;

            if(Button({350,320,200,40},"Logout"))
                screen = HOME;
        }

        // ================= CART =================
        else if(screen == CART_SCREEN)
        {
            DrawText("Cart", 400, 50, 30, BLACK);

            DrawText(
                TextFormat("Total: %.2f", cart.getTotal()),
                350,200,20,BLACK
            );

            if(Button({350,300,200,40},"Checkout"))
                screen = PAYMENT_SCREEN;

            if(Button({350,360,200,40},"Back"))
                screen = BUYER;
        }

        // ================= PAYMENT =================
        else if(screen == PAYMENT_SCREEN)
        {
            DrawText("Payment", 380, 80, 30, BLACK);

            if(Button({350,200,200,40},"bKash"))
            {
                BKashAccounts acc;
                acc.loadAccounts("bKashAccounts.txt");

                Payment* p = new BKashPayment(cart.getTotal(), "01700000000");

                if(p->validate())
                    p->process(acc);

                delete p;
                cart.clearCart();
            }

            if(Button({350,260,200,40},"Cash On Delivery"))
            {
                Payment* p = new CashOnDelivery(cart.getTotal());

                p->process(*(new BKashAccounts()));

                delete p;
                cart.clearCart();
            }

            if(Button({350,320,200,40},"Back"))
                screen = CART_SCREEN;
        }

               else if(screen == ADMIN_LOGIN)
{
    DrawText("Admin Login", 350, 80, 30, BLACK);

    DrawText("Password:", 250, 200, 20, BLACK);
    DrawRectangle(380,195,250,35,LIGHTGRAY);

    // hide password
    char hidden[20] = "";
    for(int i=0;i<adminLen;i++)
        hidden[i] = '*';
    hidden[adminLen] = '\0';

    DrawText(hidden,390,202,20,BLACK);

    // typing
    int key = GetCharPressed();
    while(key > 0)
    {
        if(key >= 32 && key <= 125 && adminLen < 19)
        {
            adminInput[adminLen++] = key;
            adminInput[adminLen] = '\0';
        }
        key = GetCharPressed();
    }

    if(IsKeyPressed(KEY_BACKSPACE) && adminLen > 0)
        adminInput[--adminLen] = '\0';

    // login button
    if(Button({350,260,200,40},"Login"))
    {
        if(strcmp(adminInput, ADMIN_PASS) == 0)
        {
            screen = ADMIN;
            adminError = false;

            adminLen = 0;
            adminInput[0] = '\0';
        }
        else
        {
            adminError = true;
        }
    }

    if(adminError)
        DrawText("Wrong Password!", 350, 320, 20, RED);

    if(Button({350,360,200,40},"Back"))
        screen = LOGIN;
}

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
