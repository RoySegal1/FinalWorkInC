//
// Created by User on 05/04/2024.
//

#ifndef FINALWORKINC_PLAYLISTREPOSITORY_H
#define FINALWORKINC_PLAYLISTREPOSITORY_H
#include "playList.h"
#include "songRepository.h"

typedef struct{
    PlayList *systemPlaylists;
    int numOfPlayList;
}PlayListRepository;


void initPlayListRepo(PlayListRepository* repository);

int savePlayListArrToBfile(const PlayListRepository* pPlay, const char* fileName);
int savePlayListArrToTextFile(const PlayListRepository* pPlay, const char* fileName);
int loadPlayListArrFromBfile(PlayListRepository* repository, const char* fileName, SongRepository* pSongRepository);
int loadPlayListArrFromTextFile(PlayListRepository* repository, const char* fileName, SongRepository* pSongRepository);
int savePlayListRepositoryToFile(const PlayListRepository* pPlay, const char* fileName, int fileType);
int loadPlayListRepositoryFromFile(PlayListRepository* repository, const char* fileName, SongRepository* pSongRepository,int fileType);


int createNewSystemPlayList(PlayListRepository* pPlayRepository, SongRepository* pSongRepository);

void printPlayLists(const PlayListRepository* pPlayRepository);
void freePlayListsRepo(PlayListRepository* pPlayRepository);



#endif //FINALWORKINC_PLAYLISTREPOSITORY_H
