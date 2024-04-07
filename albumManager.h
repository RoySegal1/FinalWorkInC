#pragma once
#include "album.h"
#include "artistRepository.h"
#include "songRepository.h"



typedef struct {
	Album* allAlbums;
	int numOfAlbums;
}AlbumManager;


void printAlbumManager(const AlbumManager* pAlbumManager);
void freeAlbumManager(AlbumManager* pAlbumManager);

int addAlbumToManager(AlbumManager* pAblumManager,const ArtistRepository* pArtistRepo);
int addSongToAlbumManager(AlbumManager* pAlbumManager,const SongRepository* pSongs);





int writeAlbumManagerToTextFile(const AlbumManager* pAlbum, FILE* fp);
int writeAlbumManagerToBFile(const AlbumManager* pAlbum, FILE* fp);
int readAlbumManagerFromTextFIle(AlbumManager* pAlbum, FILE* fp,  Artist* artists, int size, const SongRepository* pSongs);
int readAlbumManagerFromBFIle(AlbumManager* pAlbum, FILE* fp,  Artist* artists, int size, const SongRepository* pSongs);


int writeAlbumManagerToFile(const AlbumManager* pAlbum, const char* fileName, int typeFile);
int readAlbumManagerFromFile(AlbumManager* pAlbum, const char* fileName, Artist* artists, int size, const SongRepository* pSongs, int typeFile);


