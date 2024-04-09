//
// Created by User on 02/04/2024.
//

#ifndef FINALWORKINC_USER_H
#define FINALWORKINC_USER_H
#include "playList.h"
#include "album.h"
#include "songRepository.h"
#include "playlistRepository.h"
#include "albumManager.h"


typedef struct {
    char* userName;
    PlayList* userPlayLists;
    int numOfPlaylists;
    Album* userAlbums;
    int numOfAlbums;
}User;

void initUser(User* pUser);
void initUserZeros(User* pUser);

int addPlayListToUser(User* pUser, PlayList* pPlay);
int addPlayListToUserFromSystem(User* pUser,const PlayListRepository* pPlayLists);
int createPlayListToUser(User* pUser, const SongRepository* pSongs);
int addSongToUserPlayList(User* pUser,const SongRepository* pSongs);
int deleteSongFromUserPlayList(User* pUser);
int addAlbumToUser(User* pUser, Album* pAlbums);
int addAlbumFromAlbumManagertoUser(User* pUser,const AlbumManager* pAlbums);
int deleteAlbumFromUser(User* pUser);
int deletePlayListFromUser(User* pUser);


int hasPlayList(const User* pUser,const PlayList* pPlay);
int hasAlbum(const User* pUser,const Album* pAlbum);
int numberOfUserPlayList(const User* pUser);

int ShufflePlayList(const User* pUser);
int playByOrderPlayList(const User* pUser);
void sortPlayListForUser(const User* pUser);
void findSongInSortedPlayListForUser(const User* pUser);


void printUser(const User* pUser);
void printPlayListForUser(const User* pUser);
void printAlbumsForUser(const User* pUser);
void freeUser(User* pUser);
void freeUserAlbums(Album* albums,int size);
void freeUserPlayLists(PlayList* pPlay,int size);


int writeUserToTextFile(const User* pUser, const char* fileName);
int readUserFromTextFile(User* pUser, const char* fileName, Artist* artists, int size,const SongRepository* pSongs);
int writeUserToBFile(const User* pUser, const char* fileName);
int readUserFromBFile(User* pUser, const char* fileName, Artist* artists, int size, const SongRepository* pSongs);
int readUserFromFile(User* pUser, const char* fileName, Artist* artists, int size, const SongRepository* pSongs, int fileType);
int writeUserToFile(const User* pUser, const char* fileName, int fileType);



#endif //FINALWORKINC_USER_H
