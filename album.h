#pragma once
#include "song.h"
#include "artist.h"
#include "GeneralList.h"
#include "songRepository.h"

typedef struct {
	LIST songs;
	int numOfSongs;
	Artist artist;
	char* albumName;
}Album;


int initAlbum(Album* pAlbum, Artist* pArtist);
int addSongToAlbum(Album* pAlbum, Song* pSong,int fromFile);
Song* findSongByName(Album* pAlbum, const char* songName);
void printAlbum(const Album* pAlbum);
void freeAlbum(Album* pAlbum);
int readAlbumFromBFile(Album* pAlbum, const char* fileName, Artist* artists, int size,SongRepository* pSongs);
int writeAlbumToBFile(Album* pAlbum, const char* fileName);
int readAlbumFromTextFile(Album* pAlbum, const char* fileName, Artist* artists, int size,SongRepository* pSongs);
int writeAlbumToTextFile(Album* pAlbum, const char* fileName);