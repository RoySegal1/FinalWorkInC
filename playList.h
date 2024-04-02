//
// Created by User on 01/04/2024.
//

#ifndef FINALWORKINC_PLAYLIST_H
#define FINALWORKINC_PLAYLIST_H
#include "song.h"
#include "songRepository.h"


typedef enum {ePrivate,ePublic,eNofPlayListType} ePlayListsType;
static const char* playListType[eNofPlayListType] = {"Private","Public"};
typedef enum { eNotOrdered, eAmountPlayed, eArtistName, eGenre,eSongName, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt] = {"Default","Amount Played","Artist Name","Genre","Song Name"};

typedef struct {
    Song** allSongs;
    char* playlistName;
    int numOfSongs;
    ePlayListsType typeOfPlayList;
    eSortOption playListSortOp;
}PlayList;

void initPlayList(PlayList* pPlay);


int addSongToPlayList(PlayList* pPlay, Song* pSong);
int removeSongFromPlayList(PlayList* pPlay);

void sortPlayList(PlayList* pPlay);
void findSong(const PlayList* pPlay);

int createSongArr(PlayList* pPlay);

eSortOption showSortMenu();
ePlayListsType playListTypeMenu();

void printPlayList(const PlayList* pPlay);

int writePlayListToBFile(PlayList* pPlay,FILE* fp);
int writePlayListToTextFile(PlayList* pPlay,FILE* fp);
int readPlayListFromBFile(PlayList* pPlay,FILE* fp,SongRepository* sR);
int readPlayListFromTextFile(PlayList* pPlay,FILE* fp,SongRepository* sR);

#endif //FINALWORKINC_PLAYLIST_H
