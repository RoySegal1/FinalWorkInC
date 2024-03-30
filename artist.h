#pragma once



typedef struct{
    char* name;
    int amountOfPlay;
    int amountOfSongs;

}Artist;

void showArtist(Artist* artist);
void initArtist(Artist* artist);
void getArtistName(Artist* artist);