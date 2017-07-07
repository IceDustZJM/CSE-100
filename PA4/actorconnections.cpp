/*
 * actorconnection.cpp
 * Author: Hwa Chien Hong
 * Date:   5/27/17
 *
 * actorconnection program that will find the first year in which these two 
 * actors become connected.
 */

#include "ActorGraph.h"
#include "ActorTree.h"
#include "Actor.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    char* file = argv[1];
    char* pairs = (argv[2]);
    char* outfile(argv[3]);
    // if we want to do bfs or ufind
    bool bfs = false;
    if(argc == 5) { 
	std::string c(argv[4]);
	bfs = (c.compare("bfs") == 0) ? true : false;
    } 

    ofstream output;
    output.open(outfile);
    long long time;
    ActorGraph graph1;
    // Step 1: Construct the Graph
    // the true makes sure that a empty graph is constructed from bfs traversal
    // the middle true does nothing
    // also makes the list of pairs to load 
    vector<std::pair<std::string, std::string> > vec = graph1.loadPairs(pairs);
     
    output << "Actor1" << '\t' << "Actor2" << '\t' << "Year" << endl; 
    // Step 3: find the shortest distance and print the results 
    int year = 0;
    for(int i = 0; i < vec.size(); i++) { 
	Actor* actor1 = new Actor(vec.at(i).first);
        Actor* actor2 = new Actor(vec.at(i).second);
        Timer t;
        t.begin_timer();
        // run bfs on graph structure
	if(bfs) { 
	    ActorGraph graph;
	    graph.loadFromFile(file, true , true);
	    // Step 4: find all the relative edges/paths to the starting actor
	    year = graph.findConnectionBFS(actor1, actor2); 
	} else { 
        // run disjoint set to findConnection
	    ActorTree tree;
            tree.loadFromFile(file, true, true);
	    year = tree.findConnectionTree(actor1, actor2);
        }
        long long  temp = t.end_timer();
        time += temp;
        //cout << temp << endl;
	// format and all the result
	output << actor1->getName() << '\t';
	output << actor2->getName() << '\t' << year << endl;
    }
    //cout << "Calculated time is " << time/vec.size();

    return 0;
}
