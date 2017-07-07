/**
 * Movie.h
 * Author: Hwa Chien Hong
 * Date:   5/20/2017
 * 
 * THis file specifies the methods and fields of a Movie object
 */
#include "Movie.h" 
#include "Actor.h"
#include <fstream>
#include <iostream>


void Movie::addActor(Actor* actor) { 
    actors.push_back(actor);
}

const std::vector<Actor*> Movie::getActors() { 
    return actors;
}

std::string Movie::getTitle() const { 
    return title;
}

int Movie::getYear() const{
    return year; 
}

Movie::~Movie() {};
