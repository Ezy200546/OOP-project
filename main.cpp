#include "raylib.h"
#include "User.h"
#include "Product.h"
#include "Cart.h"
#include "Order.h"

// Simple button function
bool Button(Rectangle rec, const char* text) {
    DrawRectangleRec(rec, LIGHTGRAY);
    DrawRectangleLinesEx(rec, 2, DARKGRAY);
    DrawText(text, rec.x + 10, rec.y + 10, 20, BLACK);

    return CheckCollisionPointRec(GetMousePosition(), rec) &&
           IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

enum Screen {
    HOME,
    BUYER_SCREEN,
    SELLER_SCREEN,
    ADMIN_SCREEN
};

int main() {
    // Window setup
    InitWindow(900, 600, "MAHO E-Commerce (raylib)");
    SetTargetFPS(60);

    // Demo users
    Buyer buyer("adef", "1234");
    Seller seller("ezy", "1234");
    Admin admin("admin", "admin");

    // Demo products
    Product products[2] = {
        Product(1, "Laptop", "Electronics", 800, 10),
        Product(2, "Shoes", "Fashion", 50, 20)
    };

    Cart cart;

    Screen currentScreen = HOME;

    // Main loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // ---------------- HOME SCREEN ----------------
        if (currentScreen == HOME) {
            DrawText("MAHO E-COMMERCE", 300, 50, 32, DARKBLUE);
            DrawText("Select User Role", 340, 100, 20, GRAY);

            if (Button({350, 180, 200, 45}, "Buyer")) {
                currentScreen = BUYER_SCREEN;
            }
            if (Button({350, 250, 200, 45}, "Seller")) {
                currentScreen = SELLER_SCREEN;
            }
            if (Button({350, 320, 200, 45}, "Admin")) {
                currentScreen = ADMIN_SCREEN;
            }
        }

        // ---------------- BUYER SCREEN ----------------
        else if (currentScreen == BUYER_SCREEN) {
            DrawText("Buyer Dashboard", 30, 30, 28, DARKGREEN);
            DrawText(buyer.getUsername().c_str(), 30, 70, 20, GRAY);

            DrawText("Products:", 30, 120, 22, BLACK);

            int y = 160;
            for (int i = 0; i < 2; i++) {
                DrawText(TextFormat("%d. %s - $%.2f",
                         products[i].id,
                         products[i].name.c_str(),
                         products[i].price),
                         30, y, 20, BLACK);

                if (Button({350, y - 5, 140, 35}, "Add to Cart")) {
                    cart.addProduct(products[i], 1);
                }
                y += 50;
            }

            if (Button({30, 450, 180, 40}, "Back")) {
                currentScreen = HOME;
            }
        }

        // ---------------- SELLER SCREEN ----------------
        else if (currentScreen == SELLER_SCREEN) {
            DrawText("Seller Dashboard", 30, 30, 28, MAROON);
            DrawText(seller.getUsername().c_str(), 30, 70, 20, GRAY);

            DrawText("Seller can add / edit products here", 30, 150, 20, BLACK);

            if (Button({30, 450, 180, 40}, "Back")) {
                currentScreen = HOME;
            }
        }

        // ---------------- ADMIN SCREEN ----------------
        else if (currentScreen == ADMIN_SCREEN) {
            DrawText("Admin Dashboard", 30, 30, 28, DARKPURPLE);
            DrawText(admin.getUsername().c_str(), 30, 70, 20, GRAY);

            DrawText("Admin controls system-wide operations", 30, 150, 20, BLACK);

            if (Button({30, 450, 180, 40}, "Back")) {
                currentScreen = HOME;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

