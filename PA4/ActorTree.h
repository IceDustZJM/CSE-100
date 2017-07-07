/*
 * ActorGraph.h
 * Author: Hwa Chien Hong
 * Date:   5/20/2017
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORTREE_H
#define ACTORTREE_H

#include <iostream>
#include <utility>
#include <string>
#include <queue>
#include <vector>
#include <set>
#include "Actor.h"
#include "Movie.h"
#include "Edge.h"
#include "ActorGraph.h"

// Maybe include some data structures here

using namespace std;
class ActorTree { 
    protected:
	std::set<Movie*, movieCompare> movies;
	std::set<Actor*, actorCompare> actors;

	/* FINAL SUBMISSION */ 

        priority_queue<Movie*, vector<Movie*>, connectionCompare> qp;

    public:
	ActorTree() { } 

	// To create the sets of movies and actors
	bool loadFromFile(char const* in_filename, bool use_weighted_edges, bool actorConnection);

        // to add parent 
	void createSet(Movie* movie);  

	Actor* findSenti(Actor* actor);

	void connectSentinel(Actor* act1, Actor* act2);

        int findConnectionTree(Actor* fromCopy, Actor* toCopy);
};

#endif // ACTORGRAPH_H
