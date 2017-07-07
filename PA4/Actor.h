/*
 * Author: Hwa Chien Hong
 * Date: 5/20/17
 * Assignment Number: PA4
 * File: Actor.h
 * Overview: The .h file that specifies what the needed implementations of 
 * each method as well as the member variables  
 */
#ifndef ACTOR_H
#define ACTOR_H
#include <string>
#include <vector>
#include "Edge.h"
#include "Movie.h"

using namespace std;

/** A class, instances of which are Actors in the graph.*/

class Movie;

class Actor {

    public:
	/* CHECKPOINT */
	std::string name;			// name of the actor

	std::vector<Edge*> edges; 		// list of movies he/she acted in

	bool visited;

	Actor* prev_act;

	Movie* prev_mov;

	/* FINAL SUBMISSION */
	int dist; 

	Actor* parent;				// for actorconnection (uptree)       

	Actor(std::string& name):name(name){}

	void addEdge(Edge* edge);

	const std::vector<Edge*> getEdges();

	string getName() const;			// Gets name of the actor 

	~Actor();
};

#endif
