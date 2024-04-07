//
// Created by User on 01/04/2024.
//

#ifndef FINALWORKINC_PLAYLIST_H
#define FINALWORKINC_PLAYLIST_H
#include "song.h"
#include "songRepository.h"
#define MIN_SONGS 0

typedef enum {eUser,eSystem,eNofPlayListType} ePlayListsType;
static const char* playListType[eNofPlayListType] = {"User","System"};
typedef enum { eNotOrdered, eAmountPlayed, eArtistName, eGenre,eSongName, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt] = {"Default","Amount Played","Artist Name","Genre","Song Name"};

typedef struct {
    Song** allSongs;
    char* playlistName;
    int numOfSongs;
    ePlayListsType typeOfPlayList;
    eSortOption playListSortOp;
}PlayList;


int initPlayListForSystem(PlayList* pPlay);
int initPlayListForUser(PlayList* pPlay);


int addSongToPlayList(PlayList* pPlay, Song* pSong);
int removeSongFromPlayList(PlayList* pPlay);
Song* getSongFromPlayList(const PlayList* pPlay,const char code[5]);

void sortPlayList(PlayList* pPlay);
void findSong(const PlayList* pPlay);

int createSongArr(PlayList* pPlay);

eSortOption showSortMenu();
ePlayListsType playListTypeMenu();

void printPlayList(const PlayList* pPlay);
void freePlayList(PlayList* pPlay);
void freeSongsArr(Song** pSongs, int size);

int writePlayListToBFile(PlayList* pPlay,FILE* fp);
int writePlayListToTextFile(PlayList* pPlay,FILE* fp);
int readPlayListFromBFile(PlayList* pPlay,FILE* fp,const SongRepository* sR);
int readPlayListFromTextFile(PlayList* pPlay,FILE* fp,const SongRepository* sR);

#endif //FINALWORKINC_PLAYLIST_H
