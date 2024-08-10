#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter(); //constructor
    Vector2 getWorldPos(); //get position on the map
    void undoMovement(); //to prevent moving when path is obstructed
    Rectangle getCollisionRec(); //to measure collisions
    virtual void tick(float deltaTime); //behavior per frame
    virtual Vector2 getScreenPos() = 0; //get position on the screen
    bool getAlive() { return alive; }; //see if alive or dead
    void setAlive(bool isAlive) { alive = isAlive; }; //set alive status

protected:
    Texture2D texture{LoadTexture("textures/characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("textures/characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("textures/characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 means facing right, -1 means facing left
    float rightLeft{1.f};
    // Animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.f};
    Vector2 velocity{};

private:
    bool alive{true};
};

#endif