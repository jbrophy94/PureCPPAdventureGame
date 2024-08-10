#include <cstdio>
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    // Initialize Window
    int windowDimensions[2]{384, 384};
    int fps{60};
    InitWindow(windowDimensions[0], windowDimensions[1], "Call To Adventure!");
    SetTargetFPS(fps);

    // Initialize Audio
    InitAudioDevice();

    Texture2D map = LoadTexture("textures/nature_tileset/OpenWorldMap24x24.png");
    Music backgroundMusic = LoadMusicStream("Audio/background_music.wav");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowDimensions[0], windowDimensions[1]};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("textures/nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("textures/nature_tileset/Log.png")}};

    Enemy goblin{Vector2{800.f, 300.f},
                 LoadTexture("textures/characters/goblin_idle_spritesheet.png"),
                 LoadTexture("textures/characters/goblin_run_spritesheet.png")};

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("textures/characters/slime_idle_spritesheet.png"),
        LoadTexture("textures/characters/slime_run_spritesheet.png")};

    Enemy goblin2{
        Vector2{700.f, 1000.f},
        LoadTexture("textures/characters/goblin_idle_spritesheet.png"),
        LoadTexture("textures/characters/goblin_run_spritesheet.png")};

    Enemy goblin3{
        Vector2{200.f, 100.f},
        LoadTexture("textures/characters/goblin_idle_spritesheet.png"),
        LoadTexture("textures/characters/goblin_run_spritesheet.png")};

    Enemy goblin4{
        Vector2{150.f, 700.f},
        LoadTexture("textures/characters/goblin_idle_spritesheet.png"),
        LoadTexture("textures/characters/goblin_run_spritesheet.png")};

    Enemy goblin5{
        Vector2{300.f, 200.f},
        LoadTexture("textures/characters/goblin_idle_spritesheet.png"),
        LoadTexture("textures/characters/goblin_run_spritesheet.png")};

    Enemy goblin6{
        Vector2{400.f, 500.f},
        LoadTexture("textures/characters/goblin_idle_spritesheet.png"),
        LoadTexture("textures/characters/goblin_run_spritesheet.png")};

    Enemy slime2{
        Vector2{50.f, 70.f},
        LoadTexture("textures/characters/slime_idle_spritesheet.png"),
        LoadTexture("textures/characters/slime_run_spritesheet.png")};

    Enemy *enemies[] = {
        &goblin,
        &goblin2,
        &goblin3,
        &goblin4, &slime, &slime2};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    PlayMusicStream(backgroundMusic);

    // Game Loop
    while (!WindowShouldClose())
    {
        // Update music:
        UpdateMusicStream(backgroundMusic);

        // Draw Window
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1);

        // Draw Map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        // Draw props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, GREEN);
        }

        knight.tick(GetFrameTime());

        // Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowDimensions[0] > mapScale * map.width ||
            knight.getWorldPos().y + windowDimensions[1] > mapScale * map.height)
        {
            knight.undoMovement();
        }

        // Check prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        // attack
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            knight.playAttackScream();
        for (auto enemy : enemies)
        {
            if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
            {
                enemy->setAlive(false);
            }
        }

        EndDrawing();
    }

    UnloadMusicStream(backgroundMusic);

    CloseWindow();

    return 0;
};