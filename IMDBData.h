// ITP 365 Spring 2019
// HW7 - IMDB Search
// Name: Tommy Trojan
// Email: ttrojan@usc.edu
// Platform: Windows
//
// IDMBData.h - Defines IMDBData interface
//

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "IMDBGraph.h"

class IMDBData
{
public:
	// Do for Part 1
	// Function: Default Constructor
	// Purpose: Loads in the actor/movie file specified,
	// and populates the data into the appropriate hash maps.
	// Also constructs the graph with actor relationships.
	// Input: Name of file to load (by reference)
	// Returns: Nothing
	IMDBData(const std::string& fileName);

	// Do for Part 1
	// Function: getMoviesFromActor
	// Purpose: Given an actor's name, returns a vector containing their movies
	// Input: Name of actor (by reference)
	// Returns: Vector of movies (by reference)
	void reverseMap(const std::string& actorName, const std::vector<std::string>& movies);

	// Do for Part 1
	// Function: getMoviesFromActor
	// Purpose: Given an actor's name, returns a vector containing their movies
	// Input: Name of actor (by reference)
	// Returns: Vector of movies (by reference)
	std::vector<std::string>& getMoviesFromActor(const std::string& actorName);

	// Do for Part 1
	// Function: getActorsFromMovie
	// Purpose: Given a movie's name, returns the name of its actors
	// Input: Name of movie (by reference)
	// Returns: Vector of actors (by reference)
	std::vector<std::string>& getActorsFromMovie(const std::string& movieName);

	// Do for Part 2
	// Function: findRelationship
	// Purpose: Tries to find a relationship between two actors, using a BFS
	// and outputs (to cout) the result of the search.
	// Input: Name of two actors to check for a relationship
	// Returns: Nothing
	void findRelationship(const std::string& fromActor, const std::string& toActor);

	// For Part 2
	// Function: createGraph
	// Purpose: This helper function constructs the IMDBGraph from the movie to actors map
	// Input: None
	// Returns: Nothing
	void createGraph();
private:
	// Hash map which associates an actor with a vector of movies (use for part 1)
	std::unordered_map<std::string, std::vector<std::string>> mActorsToMoviesMap;

	// Hash map which associates a movie with a vector of actors (use for part 1)
	std::unordered_map<std::string, std::vector<std::string>> mMoviesToActorsMap;
	
	// Graph that shows relationships between actors (use for part 2)
	IMDBGraph mGraph;

	// Static helper variable used to have an empty vector (use for part 1)
	static std::vector<std::string> sEmptyVector;

};
