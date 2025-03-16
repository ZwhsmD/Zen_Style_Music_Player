#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "sortAndShuffle.h"

#define MAX_SONGS 3
#define MAX_ARTISTS 4
#define MAX_LENGTH 80


int InsertSongs(char songs[MAX_SONGS][MAX_LENGTH], char ArtistName[MAX_LENGTH], char allSongs[MAX_SONGS][MAX_LENGTH], char artistNumber);

void printSongs(char songs[MAX_SONGS][MAX_LENGTH], int numOfSongs);

void printArtistsWithSongs(char artist[MAX_LENGTH], char songs[MAX_SONGS][MAX_LENGTH], int numOfSongs);

int findAuthor(char artist1[3][MAX_LENGTH], char artist2[2][MAX_LENGTH], char artist3[2][MAX_LENGTH],char artist4[2][MAX_LENGTH], int numOfArtists, char song[MAX_LENGTH]);


int main(void)
{
  int artist_counter=0;
  //The array containing artists names
  char artists[4][80];
  //Songs for Artist 1
  char songsArtist1[3][80];
  //Songs for Artist 2
  char songsArtist2[3][80];
  //Songs for Artist 3
  char songsArtist3[3][80];
  //Songs for Artist 4
  char songsArtist4[3][80];
  //The total number of artists (Note it can be less than 4)
  int numOfArtists =0;
  //The total number of songs for each artist (Note that less than 3 songs can be provided for each artist)
  int numSongsPerArtist[4];

  srand(time(NULL));



    //inserting artists and keeping track of how many were inputed in var numOfArtists
    for(int i=0;i<4;i++){
        printf("Insert artist/group name\n");
        fgets(artists[numOfArtists],MAX_LENGTH, stdin);
        artists[i][strcspn(artists[i], "\n")] = '\0';  // Removes newline added automatically by fgets in the previous line
            //if input is an enter or a single character of the user's choice then end getting input
        if(strlen(artists[numOfArtists])<=2) break;
        else numOfArtists++;

    }
    //array with all songs in order of songsArtist1, songsArtist2, songsArtist3, songsArtist4;
    char allSongs[MAX_SONGS*numOfArtists][MAX_LENGTH];


    //sorting artists alphabetically. Done in sortAndShuffle.c
    sortArtists(artists, numOfArtists);


    //Inserting songs for each artists based on the number of artists. Keeping track of how many songs
    //were entered for each artist in array numSongsPerArtist
    if(numOfArtists>=1) numSongsPerArtist[0] = InsertSongs(songsArtist1, artists[0], allSongs, '0');
    if(numOfArtists>=2) numSongsPerArtist[1] = InsertSongs(songsArtist2, artists[1], allSongs, '1');
    if(numOfArtists>=3) numSongsPerArtist[2] = InsertSongs(songsArtist3, artists[2], allSongs, '2');
    if(numOfArtists==4) numSongsPerArtist[3] = InsertSongs(songsArtist4, artists[3], allSongs, '3');

    //printing sorted songs with their artist
    printf("Sorted list of songs: \n");
    printArtistsWithSongs(artists[0], songsArtist1, numSongsPerArtist[0]);

    if(numOfArtists>1)
    {
        printArtistsWithSongs(artists[1], songsArtist2, numSongsPerArtist[1]);

        if(numOfArtists>2) printArtistsWithSongs(artists[2], songsArtist3, numSongsPerArtist[2]);
        if(numOfArtists>3) printArtistsWithSongs(artists[3], songsArtist4, numSongsPerArtist[3]);
    }


    int songCounter=0;
    //inserting songs of each artists into one array called allSongs to allow shuffling
    for(int i=0;i<numOfArtists;i++)
    {
        for(int j=0;j<numSongsPerArtist[i];j++)
        {
            if(i==0) strcpy(allSongs[songCounter+j], songsArtist1[j]);
            if(i==1) strcpy(allSongs[songCounter+j], songsArtist2[j]);
            if(i==2) strcpy(allSongs[songCounter+j], songsArtist3[j]);
            if(i==3) strcpy(allSongs[songCounter+j], songsArtist4[j]);
        }
        songCounter+=numSongsPerArtist[i];
    }

    //shuffling songs using shuffle function from sortAndShuffle.c
    shuffleSongs(allSongs, songCounter, numOfArtists);
    //choosing a random length of a playlist from interval(number of Songs, 2*number of songs)
    int n = songCounter + rand()%(songCounter*2);

    printf("\n Random Playlist of %d songs:\n",n);
    //array for storing last 5 songs to make sure each 5 songs are unique, not repeated
    int sequence[5]={0};
    int q=0;
    int randSong;
    bool _repeated;
    for(int i=0;i<n;i++){
            if(q==5) q=0;
            //choosing a random song from array allSongs. RandSong hold the random index of allSongs
            randSong = rand()%(songCounter);

            char ArtistName[MAX_LENGTH];
            memset(ArtistName, "#", MAX_LENGTH-2);
            ArtistName[MAX_LENGTH-1]='\0';
            //getting the song from allSongs using the random index stored in randSong
            char song[MAX_LENGTH];
            strcpy(song, allSongs[randSong]);
            //finding the artist's index in artists array using the function findAuthor. Then using the index we get the name from artists array
            strcpy(ArtistName, artists[findAuthor(songsArtist1,songsArtist2, songsArtist3, songsArtist4, numOfArtists, song)]);

            //if song index repeats, ignore it and choose another song. if it doesn't repeat, store it in sequence
            _repeated = false;
            for(int j=0;j<5;j++){
                if(sequence[j]==randSong){
                    _repeated=true;
                    break;
                }

            }
            if(!_repeated){
                printf("%s \"%s\"\n", ArtistName, song);
                sequence[q]=randSong;
                q++;
            }
            else i--;
            _repeated=false;

    }
    printf("\n");

    //ASCII ART. a heart with my initials
    printf("   XXX   XXX  .\n");
    printf("  X   X X   X .\n");
    printf(" X     X     X.\n");
    printf("  X         X .\n");
    printf("   X       X  .\n");
    printf("    X     X   .\n");
    printf("     X   X    .\n");
    printf("      X X     .\n");
    printf("       X    zd.\n");



  return 0;
}

//function that inserts songs for a certain artist using fgets and returning the number of songs inputted
int InsertSongs(char songs[MAX_SONGS][MAX_LENGTH], char ArtistName[MAX_LENGTH], char allSongs[MAX_SONGS][MAX_LENGTH], char artistNumber)
{
    int i, length;
    for(i=0;i<MAX_SONGS;i++)
    {
        printf("Insert song %d for %s\n", i+1, ArtistName);
        fgets(songs[i], MAX_LENGTH, stdin);
        //songs[i][strcspn(songs[i], "\n")] = '\0';  // Removes newline added automatically by fgets in the previous line

        if(strlen(songs[i])<=2) break;

        length = strlen(songs[i]);
        songs[i][length-1]='\0';
    }
    if(i>0) return i;
    else return 0;
}

//printing songs for a certain artist using printf
void printSongs(char songs[MAX_SONGS][MAX_LENGTH], int numOfSongs)
{
    int i;
    for(i=0;i<numOfSongs;i++)
    {
        printf("    -- %s\n", songs[i]);
    }
}

//printing using printf an Artist name followed by a sorted list of songs inputed
void printArtistsWithSongs(char artist[MAX_LENGTH], char songs[MAX_SONGS][MAX_LENGTH], int numOfSongs)
{
    printf("%s\n", artist);

    sortSongs(songs, numOfSongs);
    printSongs(songs, numOfSongs);

}

//function checking each array with songs for each artists to find the artist's name for a given song
int findAuthor(char artist1[3][MAX_LENGTH], char artist2[3][MAX_LENGTH], char artist3[3][MAX_LENGTH], char artist4[3][MAX_LENGTH], int numOfArtists, char song[MAX_LENGTH])
{
    for(int j=0;j<3;j++) if(strcmp(song, artist1[j])==0) return 0;
    for(int j=0;j<3;j++) if(strcmp(song, artist2[j])==0) return 1;
    for(int j=0;j<3;j++) if(strcmp(song, artist3[j])==0) return 2;
    for(int j=0;j<3;j++) if(strcmp(song, artist4[j])==0) return 3;
    return -1;

}
