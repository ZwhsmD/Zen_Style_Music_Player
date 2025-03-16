README:                                     Implementation Details and Design Decisions for Assignement 1 

Introduction
  >This document provides details on the implementation and design choices made for assignement1 which is a programme that sorts and shuffles a list of songs received as input. The sorting algorithm used is         Selection Sort, while the shuffling is implemented using the Fisher-Yates algorithm.

Function Used to Read Input from the Command Line--fgets()

  >fgets() is used to read input from the user because it allows handling input as a string, making it suitable for handling song and artist names that may contain spaces.
  Unlike scanf(), which stops reading at spaces, fgets() captures the entire line, ensuring proper input handling.

Sorting Algorithm Used for sorting Artists and Songs -- Selection Sort

  >Selection Sort is chosen because of its simple implementation and ease of use for sorting fixed-size arrays.
  The playlist contains a relatively small number of elements, so the inefficiencies of Selection Sort (O(n²) complexity) do not significantly impact performance.
  The algorithm is implemented in the sortSongs() and SortArtists() functions and works by iterating through the list, finding the smallest element, and swapping it with the current index.
  An alternative could be Insertion Sort, but since arrays do not allow easy expansion and shifting of elements, Selection Sort is preferred for simplicity.

Shuffling Algorithm Used--Fisher-Yates Shuffle

  >The Fisher-Yates algorithm is an efficient way to shuffle an array of elements that ensures that each permutation of the array is equally likely, making it ideal for generating random playlists.
  The implementation works by iterating backward through the array, swapping each element with a randomly selected preceding element.
  First the length of the random playlist is chosen randomly from the interval (number of songs, number of songs*2). Then using rand()%(number of songs) and an iteration i of the whole song array a random  song is chosen to be swapped with the current song[i]
  The program ensures that in a randomly generated playlist, no song is repeated within a sequence of five songs.
  This is managed using a sequence[5] array that tracks the last five played songs.If a song is about to be repeated within the last five songs, it is skipped, and a new random selection is made.
