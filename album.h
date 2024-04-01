#pragma once
#include "song.h"
#include "artist.h"
#include "GeneralList.h"


typedef struct {
	LIST songs;
	int numOfSongs;
	Artist artist;
	char* albumName;
}Album;


int initAlbum(Album* pAlbum, Artist* pArtist);
int addSong(Album* pAlbum, Song* pSong);
Song* findSongByName(Album* pAlbum, const char* songName);
void printAlbum(Album* pAlbum);