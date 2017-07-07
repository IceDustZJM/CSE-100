/*
 * extension.cpp
 * Author: Hwa Chien Hong
 * Date:   5/27/17
 *
 * extension graph problem that finds the next n friends to add
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
#include <algorithm>

using namespace std;

class CompareCount { 
    public:
	bool operator()(pair<int, int> n1, pair<int, int> n2) { 
	    return n1.first > n2.first;
	}
};

/**
 * the method that will parse the input file and then organize them in such a way
 * the we are able then create the graph then traverse through it
 * @param: the file to be read, bool to determine whether we are making a 
 * weighted graph or not
 * @return: boolean to see whether the file is succesffully read
 */ 
vector<set<int> > loadFromFile(char const* in_filename) {
    // Initialize the file stream
    ifstream infile(in_filename);
    std::vector<set<int> > info(1000);

    // keep reading lines until the end of file is reached
    while (infile) {
	string s;

	// get the next line
	if (!getline( infile, s )) break;

	istringstream ss( s );
	vector <string> record;

	while (ss) {
	    string next; 

	    // get the next string before hitting a tab character and put it in 'next'
	    if (!getline( ss, next, ' ' )) break;

	    record.push_back( next );
	}

	if (record.size() != 2) {
	    // we should have exactly 3 columns
	    continue;
	}

	int me = atoi(record[0].c_str());
	int you = atoi(record[1].c_str());
	// Creating the objects first, added with all its needed information
	//cout << me << " and " << you << endl;
	// populate adjanceny list of friend connections
	if(info[me].find(you) == info[me].end()) info[me].insert(you);
	//cout << info[me].size() << endl;
    } 

    return info;
}

/**
 * This is the method that will go through each edge of the graph, and search 
 * for the duplicate friends of friends that would possible be added as the 
 * next friend of startNode
 * @param: info from loadFromFile, the id of this current friend, number of 
 * friends to look for
 * @return: vector containing all the id of the next possible friends to add
 */ 

vector<int> queryNextFriends(vector<set<int> > info, int startNode, int numOfNextFriends) { 
    int numFriend = 1000;
    set<int> myFriends = info[startNode];
    vector<int> returnFriends; 
    vector<int> counter(numFriend);

    // for every edge of this friend
    for(std::set<int>::iterator i = myFriends.begin(); i != myFriends.end(); ++i) { 

	// search for the friends of all this person's friend
	set<int> friendsfriend = info[*i];
	for(std::set<int>:: iterator o = friendsfriend.begin(); o != friendsfriend.end(); o++) {     
	    counter[*o]++;
	}
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareCount> pq;
    for(int i = 0; i < counter.size(); i++) { 
	if(counter[i] != 0) { 
	    pq.push(std::make_pair(counter[i], i));
	} 
    }
    int count = 0;
    // after the search we will be able to see the mutual friends of this person's friend
    // the people in the vector called counter are the next likely set of people who
    // are most likely to be added as friends 
    while(!pq.empty() && count < numOfNextFriends) { 
	returnFriends.push_back(pq.top().second);
	pq.pop();
	count++;
    }

    return returnFriends;
}

int main(int argc, char* argv[]) {

    char* file = argv[1];
    char * pEnd;
    int startFriend = strtol(argv[2], &pEnd, 10);
    int numFriends = strtol(argv[3], &pEnd, 10);
    char* outfile(argv[4]);

    if(startFriend >= 1000) { 
	cout << "Chosen Friend does not exist"; 
	cout << "Please pick friend with ID between 0 ~ 999" << endl;
	return -1;
    }

    ofstream output;
    output.open(outfile);

    // Step 1: Construct the Graph --> represented as an adjacency list
    vector<set<int> > info = loadFromFile(file);

    // Step 2: find the edge connections of the friends possible to be added
    vector<int> sug = queryNextFriends(info, startFriend, numFriends); 
    for(int i = 0; i < sug.size(); i++) {
	output << "Suggestion " << i + 1<< " is friend with ID " << sug[i] << endl;
    }

    return 0;
}
