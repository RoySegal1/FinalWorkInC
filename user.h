//
// Created by User on 02/04/2024.
//

#ifndef FINALWORKINC_USER_H
#define FINALWORKINC_USER_H
#include "playList.h"
#include "album.h"
#include "songRepository.h"


typedef struct {
    char* userName;
    PlayList* userPlayLists;
    int numOfPlaylists;
    Album* userAlbums;
    int numOfAlbums;
}User;

void initUser(User* pUser);

int addPlayListToUser(User* pUser, PlayList* pPlay);
int createPlayListToUser(User* pUser, const SongRepository* pSongs);
int addSongToUserPlayList(User* pUser,const SongRepository* pSongs);
int deleteSongFromUserPlayList(User* pUser);
int addAlbumToUser(User* pUser, Album* pAlbums);
int deleteAlbumFromUser(User* pUser);
int deletePlayListFromUser(User* pUser);


int hasPlayList(User* pUser, PlayList* pPlay);
int hasAlbum(User* pUser, Album* pAlbum);
int numberOfUserPlayList(User* pUser);

void ShufflePlayList(const User* pUser); // maby receives only user and asks him which one to play
void playByOrderPlayList(const User* pUser); // same comments to all play functions


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
