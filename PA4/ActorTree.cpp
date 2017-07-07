/*
 * ActorTree.cpp
 * Author: Hwa Chien Hong
 * Date:   5/20/2017
 * File: ActorTree.cpp
 * Description: File that contains all the neccesary methods to modify, 
 * traverse through the tree data structure.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include "ActorTree.h"
#include "Actor.h"
#include "Edge.h"
#include "Movie.h"

using namespace std;

/** 
 * method that creates the two data structure of movie and actor sets so that the
 * tree can later be constructed using those data.
 * @param: the name of the file to be read, whether we should perform bfs
 * or dijkstra
 * @return: bool value to say if file is properly read
 */ 

bool ActorTree::loadFromFile(char const* in_filename, bool use_weighted_edges, bool actorConnection) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
	string s;

	// get the next line
	if (!getline( infile, s )) break;

	if (!have_header) {
	    // skip the header
	    have_header = true;
	    continue;
	}

	istringstream ss( s );
	vector <string> record;

	while (ss) {
	    string next;

	    // get the next string before hitting a tab character and put it in 'next'
	    if (!getline( ss, next, '\t' )) break;

	    record.push_back( next );
	}

	if (record.size() != 3) {
	    // we should have exactly 3 columns
	    continue;
	}

	string actor_name(record[0]);
	string movie_title(record[1]);
	int movie_year = atoi(record[2].c_str());
	// Creating the objects first, added with all its needed information
	Actor* actor = new Actor(actor_name); 
	Movie* movie = new Movie(movie_title, movie_year);

	// if the actor does not already exist
	if((actors.find(actor)==actors.end())){
	    actors.insert(actor);
	} else { 
	    std::set<Actor*>::iterator ita = actors.find(actor);
	    delete(actor);
	    actor = *ita;

	}

	if((movies.find(movie)==movies.end())){ 
	    movies.insert(movie);
	    qp.push(movie);
	} else {
	    std::set<Movie*>::iterator itm = movies.find(movie);
	    delete(movie);
	    movie = *itm;
	}

	// add the actor to the movie
	movie->addActor(actor);
    }

    for(std::set<Actor*>::iterator it = actors.begin(); it != actors.end(); ++it){
	(*it)->parent = NULL;   
    }
    if (!infile.eof()) {
	cerr << "Failed to read " << in_filename << "!\n";
	return false;
    }
    infile.close();

    return true;
}

/*
 * Method that creates the set structure that defines the tree.
 * @param: the movie which the actors in this movie will traverse through
 * @return: void
 */ 

void ActorTree::createSet(Movie* movie) { 
    vector<Actor*> movie_actors = movie->getActors();
    Actor * actor = *(movie_actors.begin());

    std::vector<Actor*>::iterator it = movie_actors.begin();
    it++;
    // connect each pair of actors in this movie
    while(it != movie_actors.end()){
	connectSentinel((actor), (*it++));
    }
}

/**
 * Connect two node's sentinel nodes.
 * @param: two actors where the sentinel nodes of these two actors are connected
 * @return: void 
 */ 

void ActorTree::connectSentinel(Actor* act1, Actor* act2) { 
    Actor* sent1 = findSenti(act1);
    Actor* sent2 = findSenti(act2);
    if(sent1 != sent2) sent1->parent = sent2;
}

/** 
 * A recursive method that finds the sentinel node of an actor.
 * @param: the actor whose sentinel node is to be found
 * @return: the sentinel node 
 */ 

Actor* ActorTree::findSenti(Actor* actor) {
    // the actor itself is the sentinel node 
    if (actor->parent == NULL) return actor;
    // path compression
    actor->parent = findSenti(actor->parent);   
    return actor->parent;
}

/**
 * method that finds the year when two actors become connected. Returns 
 * the year after that year is dicovered.
 * @param: the two actors which we will find if there exist a connection
 * @return: the year of which these two actors are connected 
 */ 

int ActorTree::findConnectionTree(Actor* fromCopy, Actor* toCopy) { 
    std::set<Actor*>::iterator a = actors.find(toCopy);
    Actor * to = *a;
    std::set<Actor*>::iterator b = actors.find(fromCopy);
    Actor * from = *b; 
    // made a copy here so the global one does not get poped 
    priority_queue<Movie*, vector<Movie*>, connectionCompare> p = qp;

    // iterate each movie in a sorted queue 
    while(!p.empty()) { 	
	// defaults to the first movie of that same year  
	int year = p.top()->getYear();
	Movie * mov = p.top();
	p.pop();
	int nextYear = year;

	// Create set for each movie that is in the same year. i.e add more edges to each actor
	while(!p.empty()) { 
	    createSet(mov);
	    mov = p.top();
	    nextYear = mov->getYear(); 
	    // different year 
	    if(nextYear != year) break;
	    p.pop();      
	}
	// means a connection is established in this year
	if(findSenti(from) == findSenti(to)) return year;
    }
    return 9999;
}
