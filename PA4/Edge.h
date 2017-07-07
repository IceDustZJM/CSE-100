/*
 * Author: Hwa Chien Hong
 * Date: 5/20/17
 * Assignment Number: PA4
 * File: Edge.h
 * Overview: The .h file that specifies what the needed implementations of 
 * each method as well as the member variables  
 */
#ifndef EDGE_H
#define EDGE_H
#include <string>
#include <vector>

using namespace std;

/** A class, instances of which are Actors in the graph.*/

class Movie;
class Actor;

class Edge {

    public:
	Movie* movie;			// Movie (edge) that defines this edge
	
	Actor* actor; 			// the connecting node to this edge
	
	int weight;

	Edge(Movie* movie, Actor* actor):movie(movie), actor(actor){}
 
	//Movie& getMovie();		// Gets Movie of this edge
	
	//Actor& getActor(); 		// Gets Actor of this edge
 
        ~Edge();
};

#endif
