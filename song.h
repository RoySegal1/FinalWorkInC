#pragma once
#include "stdio.h"
#include "artist.h"

typedef enum{eRock,ePop,eHipHop,eRB,eEDM,eReggae,eNumOfOptions} eGenreOptions;


static char* typeOfGenre[eNumOfOptions]= {"Rock","Pop","Hip Hop","R&B","EDM","Reggae"};
static int codeHelper = 0;
typedef struct {
    char songCode[5];
    char* songName;
    eGenreOptions typeOfSong;
    Artist artist;
    int minutes;
    int seconds;
    int amountPlayedSong;
} Song;

void initSong(Song* pSong ,Artist* pArtist);
void getLength(Song* pSong);
void getCode(char code[4],int num);
eGenreOptions genreMenu();
int isSongType(const Song* pSong,eGenreOptions genre);
void printSong(const void* pSong);
void freeSong(void* pSong);
int compareByArtistName(const void* pSong1,const void* pSong2);
int compareByName(const void* pSong1,const void* pSong2);
int compareByAmountPlayed(const void* pSong1,const void* pSong2);
int readSongFromBFile(Song* pSong,FILE* fp);
int writeSongToBFile(Song* pSong,FILE* fp);
