// ITP 365 Spring 2019
// HW7 - IMDB Graph
// Name: Kirubel Seyoum
// Email: kseyoum@usc.edu
// Platform: Mac
//
// IDMBData.cpp - Implements IMDBData interface

#include "IMDBData.h"
#include <fstream>
#include <iostream>
#include <queue>


// Do for Part 1
// Function: Default Constructor
// Purpose: Loads in the actor/movie file specified,
// and populates the data into the appropriate hash maps.
// Also constructs the graph with actor relationships.
// Input: Name of file to load (by reference)
// Returns: Nothing
IMDBData::IMDBData(const std::string& fileName)
{
	// TODO for Part 1
	// TODO: Generate the actor to movies map
    std::ifstream file(fileName);
    if (file.is_open())
    {
        //create string to store the lines into
        std::string line="";
        //create strings to store the actors and movies in
        std::string actor="";
        std::vector<std::string> movies;
        
        //loop until the file is over
        while (!file.eof())
        {
            //first line in the file is an actor
            actor=line;
            //use getline to store the file into the line and move to the next line
            std::getline(file,line);
            //make sure the line isn't empty
            if (line.empty())
            {
                //continue if the line contains anything
                continue;
            }
            //check if line starts with '|' because those are the movie lines
            while (line[0]== '|')
            {
                //estbalish substream
                std::string movieSS;
                //make substream not include | and make sure it doesn't go past the last index
                movieSS = line.substr(1,line.length()-1);
                //place movie in vector once it is found
                movies.push_back(movieSS);
                //move on to the next line
                std::getline(file, line);
            }
            //establish them in to map
            mActorsToMoviesMap[actor]=movies;
            //reverse the map so that the movies correspond to the actor
            reverseMap(actor, movies);
            //clear the actor string
            actor="";
            //clear the movies vector
            movies.clear();
        }
    }
    else
    {
        std::cout<< "Failed to load file.";
    }
    
    // TODO: Generate the movie to actors map
    
}

// Do for Part 1
// Function: reverseMap
// Purpose: This is a helper function that is used to generate
// the reverse map (movies to actors)
// Input: Name of actor (by reference), vector of their movies (by reference)
// Returns: Nothing
void IMDBData::reverseMap(const std::string& actorName, const std::vector<std::string>& movies)
{
    //loop through all of the movies in the vector
    for(int i=0; i<movies.size(); i++)
    {
        //check if the key is at the end of the map
        if (mMoviesToActorsMap.find(movies[i]) != mMoviesToActorsMap.end())
        {
            //push back the vector
            mMoviesToActorsMap[movies[i]].push_back(actorName);
            
        }
        else
        {
            //vector to store all the actors
            std::vector<std::string> actorVec;
            //push back the actor vector
            actorVec.push_back(actorName);
            //fill in the map
            mMoviesToActorsMap[movies[i]]=actorVec;
        }
        
    }
}

// Do for Part 1
// Function: getMoviesFromActor
// Purpose: Given an actor's name, returns a vector containing their movies
// Input: Name of actor (by reference)
// Returns: Vector of movies (by reference)
std::vector<std::string>& IMDBData::getMoviesFromActor(const std::string& actorName)
{
	// TODO for Part 1
	// TODO: Implement
    //return a vector containing their movies based on name
    //if statement checks if user input is in the file
    if(mActorsToMoviesMap.find(actorName)!= mActorsToMoviesMap.end())
    {
        //returens proper map for actors to movies
        return mActorsToMoviesMap[actorName];
    }
	return sEmptyVector;
}

// Do for Part 1
// Function: getActorsFromMovie
// Purpose: Given a movie's name, returns the name of its actors
// Input: Name of movie (by reference)
// Returns: Vector of actors (by reference)
std::vector<std::string>& IMDBData::getActorsFromMovie(const std::string& movieName)
{
	// TODO for Part 1
	// TODO: Implement
    //return a vector containing their name based on movies
    //if statement checks if user input is in the file
    if(mMoviesToActorsMap.find(movieName)!= mMoviesToActorsMap.end())
    {
        //returns proper map for movies to actors
        return mMoviesToActorsMap[movieName];
    }
	return sEmptyVector;
}

// Do for Part 2
// Function: findRelationship
// Purpose: Tries to find a relationship between two actors, using a BFS
// and outputs (to cout) the result of the search.
// Input: Name of two actors to check for a relationship
// Returns: Nothing
void IMDBData::findRelationship(const std::string& fromActor, const std::string& toActor)
{
	// TODO for Part 1
	// TODO: Implement
    //if statement to check if both actors are in the graph
    if (mGraph.containsActor(toActor)&&mGraph.containsActor(fromActor))
    {
        //create pointer nodes for the two actors
        ActorNode* oneActor= mGraph.getActorNode(fromActor);
        ActorNode* twoActor= mGraph.getActorNode(toActor);
        bool isThere=false;
        ActorNode* currentNode = nullptr;
        //create a queue for the graph
        std::queue<ActorNode*> queueGraph;
        //enqueue the node we are starting from
        queueGraph.push(oneActor);
        //loop while the BFS queue is not empty
        while (queueGraph.size()!=0)
        {
            //establish a targetNode
            ActorNode* targetNode = nullptr;
            //set currentNode equal to value in front of queue
            currentNode=queueGraph.front();
            //pop the queue graph
            queueGraph.pop();
            //set the target node equal to the second actor
            targetNode=twoActor;
            //conditional for if the currentNode equals the targetNode
            if(currentNode==targetNode)
            {
                //Indicate that a path was found in however many hops
                std::cout<< "A Path was found!" << " (" <<currentNode->mPath.size() << " hops" << ") \n";
                //set boolean to true to indicate that its been found
                isThere = true;
                break;
            }
            //conditional for if the currentNode is not visited
            if (!currentNode->mIsVisited)
            {
                //set currentNode visited to true
                currentNode->mIsVisited=true;
                //loop through current nodes adjacency list
                for (Edge curr: currentNode->mEdges)
                {
                    //conditional for if the visited flag is false
                    if (curr.mOtherActor->mIsVisited==false)
                    {
                        // enqueue the adjacent node
                        queueGraph.push(curr.mOtherActor);
                        //conditional for if the path has a size of zero
                        if (curr.mOtherActor->mPath.size()==0)
                        {
                            //set the adjacent node's path equal to currentNode's path
                            curr.mOtherActor->mPath=currentNode->mPath;
                            //push back adjacent nodes name to adjacent nodes path
                            curr.mOtherActor->mPath.push_back(PathPair(curr.mMovieName, curr.mOtherActor->mName));
                        }
                    }
                }
            }
            
        }
        //conditional for if we found a path
        if(isThere==true)
        {
            //indicate that what the actor entered was in
            std::cout<< fromActor << " was in... \n";
            //loop through the currentNodes path
            for(PathPair mypair : currentNode->mPath)
            {
                //conditional for if the name of the pair doesnt equal the actor
                if (mypair.getActorName()!=toActor)
                {
                    //output a connection hop between the two
                    std::cout<<mypair.getMovieName() << " with "<< mypair.getActorName()<< " who was in... \n";
                }
                //otherwise
                else
                {
                    //output the movie connection between the two
                    std::cout << mypair.getMovieName() <<  " with " << mypair.getActorName() << "\n";
                }
            }
        }
        //otherwise indicate that no path was found
        else
        {
            std::cout << "No path was found \n";
        }
    }
    


	// LEAVE THIS AT THE END OF THE FUNCTION
	mGraph.clearVisited();
}

// For Part 2
// Function: createGraph
// Purpose: This helper function constructs the IMDBGraph from the movie to actors map
// Input: None
// Returns: Nothing
void IMDBData::createGraph()
{
	// DO NOT EDIT THIS FUNCTION
	// For every movie in the actors map...
	for (auto& p : mMoviesToActorsMap)
	{
		const std::string& movieName = p.first;
		// Get the actors for this movie
		const std::vector<std::string>& actors = mMoviesToActorsMap[movieName];

		// Make n^2 edges between these actors
		for (size_t i = 0; i < actors.size(); i++)
		{
			ActorNode* firstActor = mGraph.getActorNode(actors[i]);
			for (size_t j = i + 1; j < actors.size(); j++)
			{
				ActorNode* secondActor = mGraph.getActorNode(actors[j]);
				mGraph.createActorEdge(firstActor, secondActor, movieName);
			}
		}
	}
}

// Leave here! Do not edit!!! Use in part 1
// DO NOT REMOVE THIS LINE
std::vector<std::string> IMDBData::sEmptyVector;
