/*
 * Author: Hwa Chien Hong
 * Date: 5/20/17
 * Assignment Number: PA4
 * File: Movie.h
 * Overview: The .h file that specifies what the needed implementations of 
 * each method as well as the member variables  
 */
#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <vector>

using namespace std;

class Actor;

/** A class, instances of which are the movie (edges) in the graph.
*/
class Movie {

    public: 
	std::string title;			// Name of the movie
	
	int year;				// Year it came out
	
	std::vector<Actor*> actors;		// Vector containing all actors in it
 
	Movie(std::string title, int year):title(title), year(year){}

	void addActor(Actor* actor);		// adds actor to this movie object

	const std::vector<Actor*> getActors();

	std::string getTitle() const;

	int getYear() const;				// Getter to retrieve year        

	~Movie();
};

#endif
