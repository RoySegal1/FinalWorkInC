#pragma once
#include "song.h"
#include "artist.h"
#include "GeneralList.h"
#include "songRepository.h"

typedef struct {
	LIST songs;
	int numOfSongs;
	Artist* artist;
	char* albumName;
}Album;


int initAlbum(Album* pAlbum, Artist* pArtist);
int addSongToAlbum(Album* pAlbum, Song* pSong,int fromFile);


Song* findSongByName(const Album* pAlbum, const char* songName);


void printAlbum(const Album* pAlbum);
void freeAlbum(Album* pAlbum);



int readAlbumFromBFileWithOpenFile(Album* pAlbum,FILE* fp,  Artist* artists, int size,const SongRepository* pSongs);
int writeAlbumToBFileWithOpenFile(const Album* pAlbum, FILE* fp);
int readAlbumFromTextFileWithOpenFile(Album* pAlbum, FILE* fp,  Artist* artists, int size, const SongRepository* pSongs);
int writeAlbumToTextFileWithOpenFile(const Album* pAlbum,FILE* fp);