/*
 * PathFinder.cpp
 * Author: Hwa Chien Hong
 * Date:   5/20/17
 *
 * Pathfinder program that will find the shortest path from one actor to another
 * actor through shared movies.
 */
#include "ActorGraph.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    if(argc != 5) { 
	cout << "Incorrect number of argumets" << endl;
	return -1;
    }

    char* file = argv[1];
    bool weighted_edges = (*argv[2] == 'w') ? true : false;
    char* pairs = (argv[3]);
    char* outfile(argv[4]);

    ofstream output;
    output.open(outfile);

    ActorGraph graph;
    // Step 1: Construct the Graph
    graph.loadFromFile(file, weighted_edges, false);  

    // Step 2: Construct a vector of pairs to find the shortest path between 
    // the input actors

    vector<std::pair<std::string, std::string> > vec = graph.loadPairs(pairs);
    output << "(actor)--[movie#@year]-->(actor)--..." << endl; 
    // Step 3: find the shortest distance and print the results 
    for(int i = 0; i < vec.size(); i++) { 
	Actor* actor1 = new Actor(vec.at(i).first);
	Actor* actor2 = new Actor(vec.at(i).second);
        
	std::string s;

	// Step 4: find all the relative edges/paths to the starting actor
	if(!weighted_edges) s = graph.bfs(actor1, actor2);
        else s = graph.dijkstra(actor1, actor2);

        output << s << endl;
    }

    return 0;
}
