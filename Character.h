#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int windWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() const { return weaponCollisionRec; };
    float getHealth() const { return health; };
    void takeDamage(float damage);
    void playAttackScream();

private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("textures/characters/weapon_sword.png")};
    Sound attackScream = LoadSound("Audio/attack_scream.wav");
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif
