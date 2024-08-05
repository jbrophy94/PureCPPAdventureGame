#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {

};

Vector2 BaseCharacter::getWorldPos() { return worldPos; }

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale};
}

void BaseCharacter::tick(float deltaTime)
{
    // Store previous world pos before updating
    worldPosLastFrame = worldPos;
    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    // update movement
    if (Vector2Length(velocity) != 0.0)
    {
        // Vector needs to be normalized or we will move faster when
        // going diagnal.
        // Then we use the normalized vector to move the mapPos.
        // We are also applying our movement speed in Vector2Scale (just multiplies)
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        // use running sheet
        texture = run;

        // Change direction of sprite
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
    }
    else
    {
        texture = idle;
    }

    velocity = {};

    // Draw Knight--this explanation was used before we created the base character class
    // Basically you need the source rectangle, which defines the dimensons
    // and location we will use to cut out the knight from the spritesheet
    // Then you need the dest rectangle which defines the location and size on the screen
    // Then when you actually draw, you use the knight texture, apply the source rectangle to it,
    // and then draw it on the screen using hte dest rectangle.
    // origin is just an empty vector
    Rectangle source{frame * width, 0.f, rightLeft * height, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    Vector2 origin{};
    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}
