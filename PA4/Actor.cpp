/**
 * Actor.cpp
 * Author: Hwa Chien Hong
 * Date:   5/20/2017
 * 
 * This file specifies the implementations of the methods from Actor.h
 */

#include "Actor.h"
#include "Movie.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>


void Actor::addEdge(Edge* edge) {
    edges.push_back(edge);
}

std::string Actor::getName() const {
    return name;
}

const std::vector<Edge*> Actor::getEdges() {
    return edges;
} 

Actor::~Actor() {};
