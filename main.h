#pragma once
#include <stdio.h>
#include <stdlib.h>
//#include <crtdbg.h>
#include <time.h>
#include "artist.h"
#include "song.h"
#include "album.h"
#include "songRepository.h"
#include "playlistRepository.h"
#include "artistRepository.h"
#include "playList.h"
#include "user.h"
#include "macros.h"
#include "albumManager.h"

void mainMenu();
int userSubMenu(User* pUser, const SongRepository* pSongs, const PlayListRepository* pPlayLists,const AlbumManager* pAlbums);
int initSystemFromFile(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum, int typeFile);
int saveSystemFiles(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum,User* pUser);//need to check that user isn't null
void endProgram(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum,User* pUser);//need to check that user isn't null
void freeSystem(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum,User* pUser);


void freeSystem(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum,User* pUser);