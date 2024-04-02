#pragma once



typedef struct{
    char* name;
    int amountOfPlay;
    int amountOfSongs;
    char* aboutMe;

}Artist;

void showArtist(const Artist* artist);
void initArtist(Artist* artist);
//void getArtistName(Artist* artist);
int	loadArtistFromTextFile(Artist * artist, FILE* fp);
int	saveArtistToTextFile(const Artist * artist, FILE* fp);
int creatArtist(Artist* artist);
int writeArtistToBFile(Artist * pArtist,FILE* fp);
int readArtistFromBFile(Artist * pArtist,FILE* fp);
void freeArtist(Artist *artist);