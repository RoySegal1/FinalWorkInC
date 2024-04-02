#pragma once
#include "stdio.h"
#include "artist.h"
#define CODE_LENGTH 5

typedef enum{eRock,ePop,eHipHop,eRB,eEDM,eReggae,eMizrahit,eNumOfOptions} eGenreOptions;


static char* typeOfGenre[eNumOfOptions]= {"Rock","Pop","Hip Hop","R&B","EDM","Reggae","Mizrahit"};
static int codeHelper = 0;
typedef struct {
    char songCode[CODE_LENGTH];
    char* songName;
    eGenreOptions typeOfSong;
    Artist artist;
    int minutes;
    int seconds;
    int amountPlayedSong;
} Song;

void initSong(Song* pSong ,Artist* pArtist);
void getLength(Song* pSong);
void getCode(char code[5],int num);
eGenreOptions genreMenu();
int isSongType(const Song* pSong,eGenreOptions genre);
void printSong(const void* pSong);
void printSongForAlbum(const void* pSong);
void printSongForPlayList(const void* pSong);
void playSong(Song* pSong,const char* fileName);
void freeSong(void* pSong);
int compareByArtistName(const void* pSong1,const void* pSong2);
int compareByName(const void* pSong1,const void* pSong2);
int compareByAmountPlayed(const void* pSong1,const void* pSong2);
int compareByGenre(const void* pSong1,const void* pSong2);
int readSongFromBFile(Song* pSong,FILE* fp, Artist* artists, int size);
int writeSongToBFile(Song* pSong,FILE* fp);
int readSongFromTextFile(Song* pSong, FILE* fp, Artist* artists, int size);
int writeSongToTextFile(Song* pSong, FILE* fp);
Artist* findArtistInArr(const Artist* pArr,int size,const char* name);
