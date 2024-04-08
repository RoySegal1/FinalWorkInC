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


Song* findSongByName(const Album* pAlbum, const char* songName);


void printAlbum(const Album* pAlbum);
void freeAlbum(Album* pAlbum);


//int readAlbumFromBFile(Album* pAlbum, const char* fileName,  Artist* artists, int size,const SongRepository* pSongs);
int readAlbumFromBFileWithOpenFile(Album* pAlbum,FILE* fp,  Artist* artists, int size,const SongRepository* pSongs);
//int writeAlbumToBFile(const Album* pAlbum, const char* fileName);
int writeAlbumToBFileWithOpenFile(const Album* pAlbum, FILE* fp);
//int readAlbumFromTextFile(Album* pAlbum, const char* fileName,  Artist* artists, int size,const SongRepository* pSongs);
int readAlbumFromTextFileWithOpenFile(Album* pAlbum, FILE* fp,  Artist* artists, int size, const SongRepository* pSongs);
//int writeAlbumToTextFile(const Album* pAlbum, const char* fileName);
int writeAlbumToTextFileWithOpenFile(const Album* pAlbum,FILE* fp); // for user