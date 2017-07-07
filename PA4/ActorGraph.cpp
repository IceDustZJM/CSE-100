/*
 * ActorGraph.cpp
 * Author: Hwa Chien Hong
 * Date:   5/20/2017
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
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
#include "ActorGraph.h"
#include "Actor.h"
#include "Edge.h"
#include "Movie.h"

using namespace std;

//ActorGraph::ActorGraph() {}

/**
 * the method that will parse the input file and then organize them in such a way
 * the we are able then create the graph then traverse through it
 * @param: the file to be read, bool to determine whether we are making a 
 * weighted graph or not
 * @return: boolean to see whether the file is succesffully read
 */ 
bool ActorGraph::loadFromFile(char const* in_filename, bool use_weighted_edges, bool actorConnection) {
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
    // THIS IS A MODIFICATION
    // Just doing regular searches in the graph
    if(!actorConnection) graphify();

    if (!infile.eof()) {
	cerr << "Failed to read " << in_filename << "!\n";
	return false;
    }
    infile.close();

    return true;
}

/** 
 * Construct the actual adjacency list graph structure by adding edges to 
 * all the actors.
 * @param: void
 * @return: void
 */ 

void ActorGraph::graphify() {

    for(std::set<Movie*>::iterator m = movies.begin(); m!=movies.end(); ++m) {
	vector<Actor*> movie_actors = (*m)->getActors();
	for(std::vector<Actor*>::iterator a1 = movie_actors.begin(); a1!=movie_actors.end(); ++a1) { 
	    for(std::vector<Actor*>::iterator a2 = movie_actors.begin(); a2!=movie_actors.end(); ++a2) { 
		if(*a1 != *a2) { 
		    Edge* edge = new Edge(*m, *a2);
		    (*a1)->addEdge(edge);
		}
	    }
	}
    } 
}

/**
 * BFS traversal to find the shortest path given two actors.
 * @param: the two actors who we will find the unweighted path between
 * @return: the string representation of the path 
 */ 

std::string ActorGraph::bfs(Actor* fromCopy, Actor* toCopy) {
    // get the actual actors
    std::set<Actor*>::iterator a = actors.find(toCopy);
    Actor * to = *a;
    std::set<Actor*>::iterator b = actors.find(fromCopy);
    Actor * from = *b;  
    // to first make all verticies unvisited 
    for(std::set<Actor*>::iterator a = actors.begin(); a!=actors.end(); ++a){ 
	(*a)->visited = false;
 	// change made here
        (*a)->prev_act = NULL;
    }
    std::queue<Actor*> q;
    q.push(from);
    from->visited = true;

    while(!q.empty()) { 
	Actor* curr = q.front();
	q.pop();

	// if we've reached the actor that we are looking for
	if(curr == to) break;

	vector<Edge*> edges = curr->getEdges(); 
	for(std::vector<Edge*>::iterator e = edges.begin(); e!=edges.end(); ++e) {
	    Edge* edge = *e;
	    // if not visited yet 
	    if(!(edge->actor->visited)) { 
		q.push(edge->actor);
		edge->actor->visited = true;
		edge->actor->prev_mov = edge->movie;
		edge->actor->prev_act = curr;
	    }
	} 
    }
    std::string s = "";
    // Added line here for Final Submission findConnection
    // If path is not found
    if((*actors.find(to))->prev_act == NULL) return s; 

    // Print Graph
    Actor* curr = to; 
    s.append("(" + to->getName()+ ")");
    while(curr != from) { 
	stringstream stream;
	stream << curr->prev_mov->getYear();
	s.insert(0, "--[" + curr->prev_mov->getTitle() + 
		"#@" + stream.str() + "]-->");
	s.insert(0, "(" + curr->prev_act->getName() + ")");      
	curr = curr->prev_act;
    }   
    return s;
}

/* ---------- FINAL SUBMISSION ---------- */

/**
 * Dijkstra's algorithm to traverse through the weighted graph.
 * @param: the two actors which we wil find the shortest path for
 * @return: the string representation of the path between these 
 * actors 
 */ 

std::string ActorGraph::dijkstra(Actor* fromCopy, Actor* toCopy) { 
    // get the actual actors
    std::set<Actor*>::iterator a = actors.find(toCopy);
    Actor * to = *a;
    std::set<Actor*>::iterator b = actors.find(fromCopy);
    Actor * from = *b;  
    // to first make all verticies unvisited 
    for(std::set<Actor*>::iterator a = actors.begin(); a!=actors.end(); ++a) { 
	(*a)->visited = false;
	(*a)->dist = INT_MAX;
    }

    priority_queue<pair<int, Actor*>, vector<pair<int, Actor*>>, distCompare> pq;

    from->dist = 0; 
    pq.push(std::make_pair(0, from));

    while(!pq.empty()) { 
	std::pair<int, Actor*> curr = pq.top();
	pq.pop();

	if(curr.second->visited == false) { 
	    // if we've reached the actor that we are looking for
	    curr.second->visited = true;

	    vector<Edge*> edges = curr.second->getEdges(); 
	    for(std::vector<Edge*>::iterator e = edges.begin(); e!=edges.end(); ++e) {
		Edge* edge = *e;
		int c = curr.second->dist + (1 + (2015 - edge->movie->getYear()));
		// if not visited yet 
		if(c < edge->actor->dist) { 
		    edge->actor->prev_act = curr.second;
		    edge->actor->prev_mov = edge->movie;
		    edge->actor->dist = c;
		    pq.push(make_pair(c, edge->actor));
		}
	    } 
	}
    }

    // Print Result
    std::string s = "";
    Actor* curr = to; 
    s.append("(" + to->getName()+ ")");
    while(curr != from) { 
	stringstream stream;
	stream << curr->prev_mov->getYear();
	s.insert(0, "--[" + curr->prev_mov->getTitle() + 
		"#@" + stream.str() + "]-->");
	s.insert(0, "(" + curr->prev_act->getName() + ")");      
	curr = curr->prev_act;
    }   
    return s;
}

/**
 * Method that find whether there is a connection between two actors after 
 * all the movies in one year was added.
 * @param: the two actors where we will find if there exists a path between
 * @return: year of which these two actors are connected  
 */

int ActorGraph::findConnectionBFS(Actor* from, Actor* to) { 
    // made a copy here so the global one does not get poped 
    priority_queue<Movie*, vector<Movie*>, connectionCompare> p = qp;

    // iterate each movie in a sorted queue 
    while(!p.empty()) {

	// defaults to the first movie of that same year  
	int year = p.top()->getYear();
	Movie * mov = p.top();
	p.pop();
	int nextYear = year;

	// Graphyify for each movie that is in the same year. i.e add more edges to each actor
	while(!p.empty()) { 
	    graphifyFS(mov);
	    mov = p.top();
	    nextYear = mov->getYear(); 
	    // different year 
	    if(nextYear != year) break;
	    p.pop();      
	}

	// run BFS to find whether this year gives us a valid path 
	// if the returned result is not an empty string
	// means a connection is established in this year
	if(bfs(from, to)!="") return year;
    }
    return 9999;
}

/**
 * A graphify method made specifically for the actorconnection portion of the assignment.
 * Only adds the edges that was passed in by the movie.
 * @param: the movie whose actors in it are connected through this edge
 * @return: void 
 */

void ActorGraph::graphifyFS(Movie* movie) { 
    vector<Actor*> movie_actors = movie->getActors();
    for(std::vector<Actor*>::iterator a1 = movie_actors.begin(); a1!=movie_actors.end(); ++a1) { 
	for(std::vector<Actor*>::iterator a2 = movie_actors.begin(); a2!=movie_actors.end(); ++a2) { 
	    if(*a1 != *a2) { 
		Edge* edge = new Edge(movie, *a2);
		(*a1)->addEdge(edge);
	    }
	}
    }
}

/**
 * Method that parses the pairs from the input and return the result as a vector of
 * string pairs.
 * @param: the pairs where each actor will be parsed
 * @return: the parsed result is returned as vector of pairs containing the two 
 * actors
 */

std::vector<std::pair<std::string, std::string> > ActorGraph::loadPairs(char const* pairs) { 
    std::vector<std::pair<std::string, std::string> > pairs_vec; 

    ifstream infile(pairs);
    //skips header
    string s;
    getline(infile, s);

    while(getline(infile, s)) { 
	vector<string> record;
	int tab = s.find('\t');
	pairs_vec.push_back(std::make_pair(s.substr(0, tab), 
		    s.substr(tab+1, s.length())));
    }
    infile.close();
    return pairs_vec;
}
