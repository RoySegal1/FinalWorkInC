#pragma once

#define MAX_NUM_PLAY 4096
#define MAX_NUM_SONGS 128
#define MAX_NAME_LEN 31
#define MAX_CV_LEN 255

typedef unsigned char BYTE;
typedef struct{
    char* name;
    int amountOfPlay;
    int amountOfSongs;
    char* aboutMe;
}Artist;

void showArtist(const void* pArtist);
void showArtistName(const void* pArtist);
//void getArtistName(Artist* artist);
int	loadArtistFromTextFile(Artist * artist, FILE* fp);
int	saveArtistToTextFile(const Artist * artist, FILE* fp);
int saveArtistToCompressFile(const Artist* pArtist, FILE* fp);
//int saveArtistArrToCompressFile();
int creatArtist(Artist* artist);
int writeArtistToBFile(const Artist* pArtist,FILE* fp);
int readArtistFromBFile(Artist* pArtist,FILE* fp);
int readArtistFromCompressFile(Artist* pArtist,FILE* fp);
void freeArtist(Artist *artist);
