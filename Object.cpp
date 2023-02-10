#include "Object.h"
    
Object::Object(string name, string tag){
    this->name = name;   // the name of the character
    this->tag = tag;     // the tag is the type of the object
}

Object::Object(){
    // empty for purpose
}

void Object::setName(string Name){
    this->name = Name;
}

string Object::getName(){
    return this->name;
}

void Object::setTag(string Tag){
    this->tag = Tag;
}

string Object::getTag(){
    return this->tag;
}
