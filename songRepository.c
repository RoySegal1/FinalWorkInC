//
// Created by אילון אהרוני on 01/04/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"
#include "songRepository.h"
#include "fileHelper.h"




int creatSongsArr(SongRepository* songRepository)
{
    if (songRepository->numSongs > 0)
    {

        songRepository->songsArr = (Song *) malloc(songRepository->numSongs * sizeof(Song));
        if (!songRepository->songsArr)
        {
            printf("Alocation error\n");
            return 0;
        }
        return 1;

    }
    else
        songRepository->songsArr = NULL;

    return 0;

}

int loadSongsRepositoryFromBFile(SongRepository* songRepository, const char* fileName, Artist* artist, int numOfArtists)
{
    FILE* fp;
    fp = fopen(fileName, "rb");
    if (!fp)
    {
        printf("Error open Song repository file\n");
        return 0;
    }

    if (!readIntFromFile(&songRepository->numSongs, fp, "Error reading song count\n"))
    {
        fclose(fp);
        return 0;
    }

    if(!creatSongsArr(songRepository))
    {
        printf("Alocation error\n");
        fclose(fp);
        return 0;
    }

    if (!loadSongArrFromBFile(songRepository, fp, artist,numOfArtists))
    {
        free(songRepository->songsArr);
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;



}
// assuming repository is init and num of songs > 0
int loadSongArrFromBFile(SongRepository* repository, FILE* fp, Artist* artists, int numOfArtists)
{

    for (int i = 0; i < repository->numSongs; i++)
    {
        if (!readSongFromBFile(&repository->songsArr[i], fp,artists,numOfArtists ))
        {
            for (int j =0; j < i; ++j)
            {
                freeSong(&repository->songsArr[j]);
//                free(&repository->songsArr[j]);
            }
          //  free(repository->songsArr);
            return 0;
        }
    }
    return 1;
}

int saveSongRepositoryToBFile(const SongRepository* songRepository, const char* fileName)
{
    FILE* fp;
    fp = fopen(fileName, "wb");
    if (!fp) {
        printf("Error open Song repository file to write\n");
        return 0;
    }
    if (!writeIntToFile(songRepository->numSongs, fp, "Error write songs count\n"))
    {
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < songRepository->numSongs; ++i)
    {
        if(!writeSongToBFile(&songRepository->songsArr[i],fp))
        {
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;

}

int saveSongRepositoryToTextFile(const SongRepository* songRepository, const char* fileName)
{
    FILE* fp;

    fp = fopen(fileName, "w");
    if (!fp) {
        printf("Error open song repository file to write\n");
        return 0;
    }

    fprintf(fp, "%d\n", songRepository->numSongs);

    for (int i = 0; i < songRepository->numSongs; ++i)
    {
        if (!writeSongToTextFile(&songRepository->songsArr[i], fp))
        {
            printf("Error write songs\n");
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

int loadSongsRepositoryFromTextFile(SongRepository* songRepository, const char* fileName, Artist* artist, int numOfArtists)
{
    FILE* fp;

    fp = fopen(fileName, "r");
    if (!fp)
    {
        printf("Error open song repository file\n");
        return 0;
    }

    fscanf(fp, "%d", &songRepository->numSongs);
//    //clean the buffer
//    fgetc(fp);

    if(!creatSongsArr(songRepository))
    {
        printf("Alocation error\n");
        fclose(fp);
        return 0;
    }

    if (!loadSongArrFromTextFile(songRepository, fp, artist,numOfArtists))
    {
        free(songRepository->songsArr);
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;
}

int loadSongArrFromTextFile(SongRepository *repository, FILE *fp, Artist *artists, int numOfArtists)
{
    for (int i = 0; i < repository->numSongs; i++)
    {
        if (!readSongFromTextFile(&repository->songsArr[i], fp,artists,numOfArtists ))
        {
            for (int j =0; j < i; ++j)
            {
                freeSong(&repository->songsArr[j]);
//                free(&repository->songsArr[j]);
            }
            return 0;
        }
    }
    return 1;
}


Song* getSongFromRepositoryByCode(SongRepository* pSongs,const char Code[CODE_LENGTH])
{
    for (int i = 0; i < pSongs->numSongs; i++) {
        if(!strcmp(pSongs->songsArr[i].songCode,Code))
            return &pSongs->songsArr[i];
    }
    return NULL;
}

//get a pointer to song and if not Null or already exist adding to repository
int addSongToRepository(SongRepository* pRepository, Song* pSong)
{
    if(pSong == NULL)
        return 0;
    Song* temp = getSongFromRepositoryByCode(pRepository,pSong->songCode) ;
    if(temp)// if temp != null
    {
        printf("Song already exist in repository\n");
        return 0;
    }
    pRepository->songsArr = (Song*)realloc(pRepository->songsArr,(pRepository->numSongs + 1)*sizeof(Song));
    if(!pRepository->songsArr)
        return 0;
    pRepository->songsArr[pRepository->numSongs++] = *pSong;
    return 1;

}
void printAllSongs(SongRepository* pSongRepository)
{
    if (!pSongRepository || pSongRepository->numSongs<1)
    {
        printf("Empty repository\n");
        return;
    }
    for (int i = 0; i < pSongRepository->numSongs; ++i)
    {
        printSong(&pSongRepository->songsArr[i]);

    }
}

void freeSongRepository(SongRepository* songRepository)
{
    if (songRepository == NULL)
        return;

    for (int i = 0; i < songRepository->numSongs; ++i)
    {
        freeSong(&songRepository->songsArr[i]);

    }
    free(songRepository->songsArr);
}

