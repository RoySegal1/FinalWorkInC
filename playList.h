//
// Created by User on 01/04/2024.
//

#ifndef FINALWORKINC_PLAYLIST_H
#define FINALWORKINC_PLAYLIST_H
#include "song.h"
typedef enum {ePrivate,ePublic,eNofPlayListType} ePlayListsType;
static const char* playListType[eNofPlayListType] = {"Private","Public"};
typedef enum { eNone, eAmountPlayed, eArtistName, eGenre,eSongName, eNofSortOpt } eSortOption;
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

void sortPlayList(PlayList* pPlay);
Song findSong(const PlayList* pPlay);
eSortOption showSortMenu();
ePlayListsType playListTypeMenu();

void printPlayList(const PlayList* pPlay);
void printSongs(const Song** pSongs,int size);




#endif //FINALWORKINC_PLAYLIST_H
