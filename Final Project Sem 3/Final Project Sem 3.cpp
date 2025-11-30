
#include <iostream>
#include<raylib.h>
#include<string>
using namespace std;
// -------------------------
// Screen Base Class
// -------------------------
class TitleScreen;
class Task;
class Calendar;
class Clock;
class LockIn;

class screen {
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

screen* ptr = nullptr; //pointer which points to whichever screen is currently active

// Factory
screen* createTitleScreen(); //creates a title screen when needed

// -------------------------
// TASK PAGE
// -------------------------
class Task : public screen {
    Texture2D back;
    Texture2D backarrow;

public:
    Task() {
        back = LoadTexture("resources/background.png");
        backarrow = LoadTexture("resources/arrow.png");
    }

    void Update() {
        Vector2 mouse = GetMousePosition(); //struct from raylib that holds two flaoting point used here to get mouse position
        Rectangle BackBtn{ 0,0,(float)backarrow.width * 0.25f,(float)backarrow.height * 0.25f };
        // creating a backbutton starting from top left and is 25% of actual size of image/graphic uploaded

        if (CheckCollisionPointRec(mouse, BackBtn) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) //checks if backbtn is clicked
        {
            ptr = createTitleScreen(); //if yes then goes back to title screen
        }
        
    }

    void Draw() //used to draw the page
    {
        DrawTexture(back, 0, 0, WHITE); //basic tecture ( backgrnd)
        DrawTextureEx(backarrow, { 0,0 }, 0, 0.25f, WHITE); //gives more control over what texture is drawn
        DrawText("Task Page", 230, 50, 48, WHITE);
    }
};

// -------------------------
// CALENDAR PAGE
// -------------------------
class Calendar : public screen {
    Texture2D back, backarrow;
public:
    Calendar() {
        back = LoadTexture("resources/background.png");
        backarrow = LoadTexture("resources/arrow.png");
    }

    void Update() {
        Vector2 mouse = GetMousePosition();
        Rectangle BackBtn{ 0,0,(float)backarrow.width * 0.25f,(float)backarrow.height * 0.25f };

        if (CheckCollisionPointRec(mouse, BackBtn) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ptr = createTitleScreen();
        }
    }

    void Draw() {
        DrawTexture(back, 0, 0, WHITE);
        DrawTextureEx(backarrow, { 0,0 }, 0, 0.25f, WHITE);
        DrawText("Calendar Page", 200, 50, 48, WHITE);
    }
};

// -------------------------
// CLOCK PAGE
// -------------------------
class Clock : public screen {
    Texture2D back, backarrow;
public:
    Clock() {
        back = LoadTexture("resources/background.png");
        backarrow = LoadTexture("resources/arrow.png");
    }

    void Update() {
        Vector2 mouse = GetMousePosition();
        Rectangle BackBtn{ 0,0,(float)backarrow.width * 0.25f,(float)backarrow.height * 0.25f };

        if (CheckCollisionPointRec(mouse, BackBtn) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ptr = createTitleScreen();
        }
    }

    void Draw() {
        DrawTexture(back, 0, 0, WHITE);
        DrawTextureEx(backarrow, { 0,0 }, 0, 0.25f, WHITE);
        DrawText("Clock Page", 240, 50, 48, WHITE);
    }
};

// -------------------------
// LOCK-IN PAGE
// -------------------------
class LockIn : public screen {
    Texture2D back, backarrow;
public:
    LockIn() {
        back = LoadTexture("resources/background.png");
        backarrow = LoadTexture("resources/arrow.png");
    }

    void Update() {
        Vector2 mouse = GetMousePosition();
        Rectangle BackBtn{ 0,0,(float)backarrow.width * 0.25f,(float)backarrow.height * 0.25f };

        if (CheckCollisionPointRec(mouse, BackBtn) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ptr = createTitleScreen();
        }
    }

    void Draw() {
        DrawTexture(back, 0, 0, WHITE);
        DrawTextureEx(backarrow, { 0,0 }, 0, 0.25f, WHITE);
        DrawText("Study Session", 200, 50, 48, WHITE);
    }
};

// -------------------------
// TITLE SCREEN
// -------------------------
class TitleScreen : public screen {
    Texture2D back;
    Texture2D taskIcon;
    Texture2D calIcon;
    Texture2D clockIcon;
    Texture2D lockIcon;
    Texture2D exitIcon;

public:
    TitleScreen() {
        back = LoadTexture("resources/background.png");
        taskIcon = LoadTexture("resources/book.png");
        calIcon = LoadTexture("resources/calendar.png");
        clockIcon = LoadTexture("resources/clock.png");
        lockIcon = LoadTexture("resources/lockin.png");
        exitIcon = LoadTexture("resources/exiticon.png");
    }

    void Update() {
        Vector2 mouse = GetMousePosition();

        Rectangle taskBtn = { 100,250,(float)taskIcon.width,(float)taskIcon.height };
        Rectangle calBtn = { 300,250,(float)calIcon.width,(float)calIcon.height };
        Rectangle clockBtn = { 500,250,(float)clockIcon.width,(float)clockIcon.height };
        Rectangle lockBtn = { 700,250,(float)lockIcon.width,(float)lockIcon.height };
        Rectangle exitBtn = { 0, 0, exitIcon.width * 0.265f, exitIcon.height * 0.265f };

        if (CheckCollisionPointRec(mouse, taskBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            ptr = new Task;

        if (CheckCollisionPointRec(mouse, calBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            ptr = new Calendar;

        if (CheckCollisionPointRec(mouse, clockBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            ptr = new Clock;

        if (CheckCollisionPointRec(mouse, lockBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            ptr = new LockIn;

        if (CheckCollisionPointRec(mouse, exitBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            exit(0);
    }

    void Draw() {
        DrawTexture(back, 0, 0, WHITE);
        DrawText("STUDY HUB", 180, 100, 72, WHITE);

        DrawTextureEx(exitIcon, { 0,0 }, 0, 0.265f, WHITE);
        DrawTexture(taskIcon, 100, 250, WHITE);
        DrawTexture(calIcon, 300, 250, WHITE);
        DrawTexture(clockIcon, 500, 250, WHITE);
        DrawTexture(lockIcon, 700, 250, WHITE);
    }
};

// -------------------------
// FACTORY METHODS
// -------------------------
screen* createTitleScreen() { return new TitleScreen(); }

// -------------------------
// MAIN
// -------------------------
int main() {
    InitWindow(800, 700, "Study UI");
    SetTargetFPS(60);

    ptr = createTitleScreen();

    while (!WindowShouldClose()) {
        ptr->Update();
        BeginDrawing();
        ClearBackground(BLACK);
        ptr->Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

