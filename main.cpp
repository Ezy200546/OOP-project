#include "raylib.h"
#include "User.h"
#include "Product.h"
#include "Cart.h"
#include "Order.h"
#include <cstring>
#include <fstream>
using namespace std;

// ---------------- Button Helper ----------------
bool Button(Rectangle rec, const char* text) {
    DrawRectangleRec(rec, LIGHTGRAY);
    DrawRectangleLinesEx(rec, 2, DARKGRAY);
    DrawText(text, rec.x + 10, rec.y + 10, 20, BLACK);

    return CheckCollisionPointRec(GetMousePosition(), rec) &&
           IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

// ---------------- Screens ----------------
enum Screen {
    HOME,
    LOGIN,
    REGISTER,
    BUYER_SCREEN,
    SELLER_SCREEN,
    ADMIN_LOGIN,
    ADMIN_SCREEN
};

// ---------------- Save User ----------------
void saveUserToFile(const string& role, const string& username, const string& password) {
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << role << "," << username << "," << password << endl;
        file.close();
    }
}

int main() {
    InitWindow(900, 600, "MAHO E-Commerce (raylib)");
    SetTargetFPS(60);

    // ---------------- USERS ----------------
    Buyer buyers[10];
    Seller sellers[10];
    Buyer pendingBuyers[10];

    int buyerCount = 0;
    int sellerCount = 0;
    int pendingBuyerCount = 0;

    Buyer* loggedBuyer = nullptr;
    Seller* loggedSeller = nullptr;

    // ---------------- INPUT ----------------
    char username[20] = "";
    char password[20] = "";
    int userLen = 0, passLen = 0;
    bool error = false;

    // ---------------- ADMIN ----------------
    const char ADMIN_PASSWORD[] = "admin123";
    char adminPass[20] = "";
    int adminLen = 0;
    bool adminError = false;

    Screen currentScreen = HOME;

    // ---------------- MAIN LOOP ----------------
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // -------- HOME --------
        if (currentScreen == HOME) {
            DrawText("MAHO E-COMMERCE", 280, 50, 32, DARKBLUE);

            if (Button({350, 150, 200, 45}, "Login"))
                currentScreen = LOGIN;

            if (Button({350, 220, 200, 45}, "Register"))
                currentScreen = REGISTER;

            if (Button({350, 290, 200, 45}, "Admin"))
                currentScreen = ADMIN_LOGIN;
        }

        // -------- REGISTER --------
        else if (currentScreen == REGISTER) {
            DrawText("Register Buyer / Seller", 280, 60, 30, BLACK);

            DrawText("Username:", 250, 160, 20, BLACK);
            DrawRectangle(380, 155, 250, 35, LIGHTGRAY);
            DrawText(username, 390, 162, 20, BLACK);

            DrawText("Password:", 250, 210, 20, BLACK);
            DrawRectangle(380, 205, 250, 35, LIGHTGRAY);

            char hidden[20] = "";
            for (int i = 0; i < passLen; i++) hidden[i] = '*';
            hidden[passLen] = '\0';
            DrawText(hidden, 390, 212, 20, BLACK);

            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125 && userLen < 19) {
                    username[userLen++] = key;
                    username[userLen] = '\0';
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_TAB)) { }

            key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125 && passLen < 19) {
                    password[passLen++] = key;
                    password[passLen] = '\0';
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (passLen > 0) password[--passLen] = '\0';
                else if (userLen > 0) username[--userLen] = '\0';
            }

            if (Button({350, 270, 200, 40}, "Register Buyer")) {
                pendingBuyers[pendingBuyerCount++] = Buyer(username, password);
                saveUserToFile("Buyer", username, password);
                userLen = passLen = 0;
                username[0] = password[0] = '\0';
                currentScreen = HOME;
            }

            if (Button({350, 320, 200, 40}, "Register Seller")) {
                sellers[sellerCount++] = Seller(username, password);
                saveUserToFile("Seller", username, password);
                userLen = passLen = 0;
                username[0] = password[0] = '\0';
                currentScreen = HOME;
            }

            if (Button({350, 380, 200, 40}, "Back"))
                currentScreen = HOME;
        }

        // -------- LOGIN --------
        else if (currentScreen == LOGIN) {
            DrawText("Login", 420, 60, 30, BLACK);

            DrawText("Username:", 250, 160, 20, BLACK);
            DrawRectangle(380, 155, 250, 35, LIGHTGRAY);
            DrawText(username, 390, 162, 20, BLACK);

            DrawText("Password:", 250, 210, 20, BLACK);
            DrawRectangle(380, 205, 250, 35, LIGHTGRAY);

            char hidden[20] = "";
            for (int i = 0; i < passLen; i++) hidden[i] = '*';
            DrawText(hidden, 390, 212, 20, BLACK);

            if (Button({350, 270, 200, 40}, "Login Buyer")) {
                error = true;
                for (int i = 0; i < buyerCount; i++) {
                    if (buyers[i].login(username, password)) {
                        loggedBuyer = &buyers[i];
                        currentScreen = BUYER_SCREEN;
                        error = false;
                        break;
                    }
                }
            }

            if (Button({350, 320, 200, 40}, "Login Seller")) {
                error = true;
                for (int i = 0; i < sellerCount; i++) {
                    if (sellers[i].login(username, password)) {
                        loggedSeller = &sellers[i];
                        currentScreen = SELLER_SCREEN;
                        error = false;
                        break;
                    }
                }
            }

            if (error)
                DrawText("Invalid login!", 380, 370, 20, RED);

            if (Button({350, 420, 200, 40}, "Back"))
                currentScreen = HOME;
        }

        // -------- ADMIN LOGIN --------
        else if (currentScreen == ADMIN_LOGIN) {
            DrawText("Admin Login", 360, 80, 30, BLACK);

            DrawText("Password:", 300, 170, 20, BLACK);
            DrawRectangle(300, 200, 300, 40, LIGHTGRAY);

            char hidden[20] = "";
            for (int i = 0; i < adminLen; i++) hidden[i] = '*';
            DrawText(hidden, 310, 210, 20, BLACK);

            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125 && adminLen < 19) {
                    adminPass[adminLen++] = key;
                    adminPass[adminLen] = '\0';
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && adminLen > 0)
                adminPass[--adminLen] = '\0';

            if (Button({350, 270, 200, 40}, "Login")) {
                if (strcmp(adminPass, ADMIN_PASSWORD) == 0) {
                    currentScreen = ADMIN_SCREEN;
                    adminError = false;
                } else adminError = true;
            }

            if (adminError)
                DrawText("Wrong Admin Password!", 320, 330, 20, RED);

            if (Button({350, 380, 200, 40}, "Back"))
                currentScreen = HOME;
        }

        // -------- ADMIN DASHBOARD --------
        else if (currentScreen == ADMIN_SCREEN) {
            DrawText("Admin Dashboard", 30, 30, 28, DARKPURPLE);
            DrawText("Pending Buyer Registrations:", 30, 100, 22, BLACK);

            int y = 140;
            for (int i = 0; i < pendingBuyerCount; i++) {
                DrawText(TextFormat("%d. %s",
                    i + 1,
                    pendingBuyers[i].getUsername().c_str()),
                    30, y, 20, DARKGRAY);
                y += 30;
            }

            if (Button({30, 500, 180, 40}, "Logout"))
                currentScreen = HOME;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

