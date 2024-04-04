//
// Created by אילון אהרוני on 01/04/2024.
//

#ifndef FINALWORKINC_SONGREPOSITORY_H
#define FINALWORKINC_SONGREPOSITORY_H
#include "song.h"


typedef struct {
    Song *songsArr;
    int numSongs;
    int maxSongs;
} SongRepository;

int creatSongsArr(SongRepository* songRepository);
int loadSongArrFromBFile(SongRepository* repository, FILE* fp, Artist* artists, int numOfArtists);
int loadSongsRepositoryFromBFile(SongRepository* songRepository, const char* fileName, Artist* artist, int numOfArtists);
int saveSongRepositoryToBFile(const SongRepository* songRepository, const char* fileName);
int saveSongRepositoryToTextFile(const SongRepository* songRepository, const char* fileName);
int loadSongsRepositoryFromTextFile(SongRepository* songRepository, const char* fileName, Artist* artist, int numOfArtists);
int loadSongArrFromTextFile(SongRepository *repository, FILE *fp, Artist *artists, int numOfArtists);
Song* getSongFromRepositoryByCode(const SongRepository* pSongs,const char Code[CODE_LENGTH]);
int addSongToRepository(SongRepository* pRepository, Song* pSong);
void printAllSongs(const SongRepository* pSongRepository);
void freeSongRepository(SongRepository* songRepository);


#endif //FINALWORKINC_SONGREPOSITORY_H
