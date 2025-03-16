#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "sortAndShuffle.h"

#define MAX_SONGS 3
#define MAX_ARTISTS 4
#define MAX_LENGTH 80

/*
* This method sorts the artists alphabetically. It takes as input:
* - sortedArtists: the array of artists that that should be sorted
* - numOfArtists: the total number of artists
*
*/

//sorting Artists' Names using the Selection Sorting Algorithm
void sortArtists(char sortedArtists[][80] , int numOfArtists){
    int i,j;
    int minIndex=0;
    bool _IndexChanged=false;
    char swap[MAX_LENGTH];

    for(i=0;i<(numOfArtists-1);i++){
        minIndex=i;
        for(j=i+1;j<numOfArtists;j++){
            if(strcmp(sortedArtists[j], sortedArtists[minIndex])<0){
                minIndex=j;
                _IndexChanged=true;
            }
        }

        if(_IndexChanged)
        {
            //swap becomes #####...# (error handling)
            memset(swap, 23, MAX_LENGTH-2);
            swap[MAX_LENGTH-1]='\0';
            //Since we found a lower length we change songsOfAnArtist[i] to be at songsOfAnArtist[minIndex] and vice versa
            strcpy(swap, sortedArtists[i]);
            strcpy(sortedArtists[i], sortedArtists[minIndex]);
            strcpy(sortedArtists[minIndex], swap);

            _IndexChanged=false;
        }
    }
}

/*
* This method sorts the songs of a specific artist alphabetically. It takes as input:
* - songsOfAnArtist: the array of the songs of an artist that was provided from the standard input
* - numOfArtists: the number of artists provided from the standard input
*/

//below I have used Selection Sort, although Insertion Sort would be better it is harder to perform on Arrays as they are less flexible.
//They dont expand-would be possible on lists
void sortSongs(char songs[][MAX_LENGTH], int numOfSongs){
    int i,j;
    int minIndex=0;
    bool _IndexChanged=false;
    char temp[MAX_LENGTH];

    for(i=0;i<(numOfSongs-1);i++){
        minIndex=i;
        for(j=i+1;j<numOfSongs;j++){
            if(strcmp(songs[j], songs[minIndex])<0){
                minIndex=j;
                _IndexChanged=true;
            }
        }

        if(_IndexChanged)
        {
            //temp becomes #####...# (error handling)
            memset(temp, "#", MAX_LENGTH-2);
            temp[MAX_LENGTH-1]='\0';
            //Since we found a lower length we change songsOfAnArtist[i] to be at songsOfAnArtist[minIndex] and vice versa
            strcpy(temp, songs[i]);
            strcpy(songs[i], songs[minIndex]);
            strcpy(songs[minIndex], temp);

            _IndexChanged=false;
        }
    }

}

/*
* This method shuffles a set of songs. It takes as input:
* - songsToBeShuffled: the array of the songs that should be shuffled
* - numOfSongs: the number of songs to be shuffled
*/
//shuffling the songs using Fisher Yasher Algorithm
void shuffleSongs(char songsToBeShuffled[][MAX_LENGTH], int numOfSongs, int numOfArtists){
        int i, j;
        srand(time(NULL));

        for(i=0;i<numOfSongs;i++){
            //getting a random index with which the i index song will be swapped
            j=rand()%(i+1);
            if(j!=i){
                char swap[MAX_LENGTH];
                /*for(int k=0;k<MAX_LENGTH;k++){
                    if(songsToBeShuffled[j][k]=='\0'){
                        swap[k]='\0';
                        break;
                    }
                    else{
                        swap[k]=songsToBeShuffled[j][k];
                    }
                }

                //songsToBeShuffled[j] becomes #####...# (error handling)
                memset(songsToBeShuffled[j], "#", MAX_LENGTH-2);
                songsToBeShuffled[j][MAX_LENGTH-1]='\0';

                for(int k=0;k<80;k++){
                    if(songsToBeShuffled[i][k]=='\0'){
                        songsToBeShuffled[j][k]='\0';
                        break;
                    }
                    else{
                        songsToBeShuffled[j][k]=songsToBeShuffled[i][k];
                    }
                }
                //songsToBeShuffled[i] becomes #####...# (error handling)
                memset(songsToBeShuffled[i], "#", MAX_LENGTH-2);
                songsToBeShuffled[i][MAX_LENGTH-1]='\0';

                for(int k=0;k<MAX_LENGTH;k++){
                    if(swap[k]=='\0'){
                        songsToBeShuffled[i][k]='\0';
                        break;
                    }
                    else{
                        songsToBeShuffled[i][k]=swap[k];
                    }
                }*/

                strcpy(swap, songsToBeShuffled[i]);
                strcpy(songsToBeShuffled[i], songsToBeShuffled[j]);
                strcpy(songsToBeShuffled[j], swap);
            }
        }
}
