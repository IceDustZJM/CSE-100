/*
 * ActorGraph.h
 * Author: Hwa Chien Hong
 * Date:   5/20/2017
 * File: ActorGraph.h
 * Description: the file containing the member variables of thie graph
 * and all the methods needed to traverse and modify the graph structure
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <utility>
#include <string>
#include <queue>
#include <vector>
#include <set>
#include "Actor.h"
#include "Movie.h"
#include "Edge.h"

// Maybe include some data structures here

using namespace std;

struct actorCompare {
    bool operator() (Actor* const & act1, Actor* const & act2){
	return act1->getName().compare(act2->getName())<0;
    }
};
struct movieCompare{
    bool operator() (Movie* const & mov1, Movie* const & mov2) { 
	if(!(mov1->getTitle().compare(mov2->getTitle()))) {
	    return mov1->getYear() < mov2->getYear();
	}
	return (mov1->getTitle().compare(mov2->getTitle())) < 0;
    }
};
struct distCompare {
    bool operator()(pair<int, Actor*> n1, pair<int, Actor*> n2) { 
	return n1.first > n2.first;
    }
};
struct connectionCompare { 
    bool operator()(Movie* const & mov1, Movie* const & mov2) { 
 	return mov1->getYear() > mov2->getYear();
    }
};

class ActorGraph { 
    protected:
	std::set<Movie*, movieCompare> movies;
	std::set<Actor*, actorCompare> actors;

	/* FINAL SUBMISSION */ 

        priority_queue<Movie*, vector<Movie*>, connectionCompare> qp;

    public:
	ActorGraph() { } 

	/* CHECKPOINT */      

	// To create the sets of movies and actors
	bool loadFromFile(char const* in_filename, bool use_weighted_edges, bool actorConnection);

	// To create the actualt graph representations 
	void graphify();

	// Traverse through the graph to get the shortest path
	std::string bfs(Actor* from, Actor* to);

	// to parse the inputs to then used to create the shortest paths 
	vector<std::pair<std::string, std::string> > loadPairs(char const* pairs);  

	/* FINAL SUBMISSION */

	// Traverse through a weighted graph to get the shortest path
	std::string dijkstra(Actor* from, Actor* to); 
  
        int findConnectionBFS(Actor* from, Actor* to);
	
	void graphifyFS(Movie* mov);
};

#endif // ACTORGRAPH_H
