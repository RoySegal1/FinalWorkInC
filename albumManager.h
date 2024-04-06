#pragma once
#include "album.h"



typedef struct {
	Album* allAlbums;
	int numOfAlbums;
}AlbumManager;


void printAlbumManager(AlbumManager pAlbumManager);
void freeAlbumManager(AlbumManager pAlbumManager);

int writeAlbumManagerToTextFile(const AlbumManager* pAlbum, FILE* fp);
int writeAlbumManagerToBFile(const AlbumManager* pAlbum, FILE* fp);
int readAlbumManagerFromTextFIle(AlbumManager* pAlbum, FILE* fp, const Artist* artists, int size, const SongRepository* pSongs);
int readAlbumManagerFromBFIle(AlbumManager* pAlbum, FILE* fp, const Artist* artists, int size, const SongRepository* pSongs);


int writeAlbumManagerToFile(const AlbumManager* pAlbum, const char* fileName, int typeFile);
int readAlbumManagerFromFile(AlbumManager* pAlbum, const char* fileName, const Artist* artists, int size, const SongRepository* pSongs, int typeFile);


