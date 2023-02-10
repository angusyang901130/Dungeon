#include "GameCharacter.h"

GameCharacter::GameCharacter(){
    // empty for now
}

GameCharacter::GameCharacter(string name, string tag, int health, int attack, int defense):Object(name, tag){
    this->maxHealth = health;
    this->currentHealth = health;
    this->attack = attack;
    this->defense = defense;
}

// show the currenthealth first then decide whether the player is dead
bool GameCharacter::checkIsDead(){
    if(this->currentHealth <= 0){
        return true;
    }else return false;
}

// get damage and then show the currentHealth - damage, but the currentHealth hasn't been updated
void GameCharacter::takeDamage(int damage){
    if(this->getCurrentHealth() <= damage){
        this->setCurrentHealth(0);
    }else this->setCurrentHealth(this->getCurrentHealth() - damage);
}

void GameCharacter::setAttack(int Attack){
    this->attack = Attack;
}

void GameCharacter::setCurrentHealth(int CurrentHealth){
    this->currentHealth = CurrentHealth;
}

void GameCharacter::setMaxHealth(int MaxHealth){
    this->maxHealth = MaxHealth;
}

void GameCharacter::setDefense(int Defense){
    this->defense = Defense;
}

int GameCharacter::getAttack(){
    return this->attack;
}

int GameCharacter::getCurrentHealth(){
    return this->currentHealth;
}

int GameCharacter::getMaxHealth(){
    return this->maxHealth;
}

int GameCharacter::getDefense(){
    return this->defense;
}

bool GameCharacter::triggerEvent(Object* object){
    return true;
}
