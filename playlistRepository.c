//
// Created by User on 05/04/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "playlistRepository.h"
#include "macros.h"
#include "fileHelper.h"
#include "General.h"

void initPlayListRepo(PlayListRepository* repository)
{
    repository->numOfPlayList = 0;
    repository->systemPlaylists = NULL;
}


int savePlayListRepositoryToFile(PlayListRepository* pPlay, const char* fileName, int fileType)
{
    if (fileType == FROM_BINARY_FILE)
    {
        if (!(savePlayListArrToBfile(pPlay, fileName)))
            return 0;
        return 1;
    }
    else
    {
        if (!(savePlayListArrToTextFile(pPlay, fileName)))
            return 0;
        return 1;
    }
    return 0;
}


int loadPlayListRepositoryFromFile(PlayListRepository* pPlay, const char* fileName, SongRepository* pSongRepository, int fileType)
{
    if (fileType == FROM_BINARY_FILE)
    {
        if (!(loadPlayListArrFromBfile(pPlay, fileName,pSongRepository)))
            return 0;
        return 1;
    }
    else
    {
        if (!(loadPlayListArrFromTextFile(pPlay, fileName, pSongRepository)))
            return 0;
        return 1;
    }
    return 0;
}


int savePlayListArrToBfile(PlayListRepository* pPlay, const char* fileName)
{
    CHECK_RETURN_0(pPlay)
        FILE* fp = fopen(fileName, "wb");
    CHECK_RETURN_0_PRINT(fp,"Couldnt find File")

        if (!writeIntToFile(pPlay->numOfPlayList, fp, "Error Writing number of PlayLists"))
            RETURN_0_CLOSE_FILE(fp)
    for (int i = 0; i < pPlay->numOfPlayList; i++) {
        if(!writePlayListToBFile(&pPlay->systemPlaylists[i],fp))
            RETURN_0_CLOSE_FILE(fp)
    }
    fclose(fp);
    return 1;
}


int savePlayListArrToTextFile(PlayListRepository* pPlay, const char* fileName)
{
    CHECK_RETURN_0(pPlay)
        FILE* fp = fopen(fileName, "w");
    fprintf(fp,"%d\n", pPlay->numOfPlayList);
    for (int i = 0; i < pPlay->numOfPlayList; i++) {
        if(!writePlayListToTextFile(&pPlay->systemPlaylists[i], fp))
            RETURN_0_CLOSE_FILE(fp)
    }
    fclose(fp);
    return 1;
}



int loadPlayListArrFromBfile(PlayListRepository* repository, const char* fileName,SongRepository* pSongRepository)
{
    FILE* fp;
    fp = fopen(fileName, "rb");
    if(!readIntFromFile(&repository->numOfPlayList,fp,"Error Reading number Play lists"))
        RETURN_0_CLOSE_FILE(fp)
    repository->systemPlaylists = (PlayList*) malloc(sizeof(PlayList)* repository->numOfPlayList);
    CHECK_RETURN_0(repository->systemPlaylists)
    for (int i = 0; i < repository->numOfPlayList; i++) {
        if(!readPlayListFromBFile(&repository->systemPlaylists[i],fp,pSongRepository))
        {
            for (int j = 0; j < i; j++) {
                freePlayList(&repository->systemPlaylists[i]);
            }
            free(repository->systemPlaylists);
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}





int loadPlayListArrFromTextFile(PlayListRepository* repository, const char* fileName, SongRepository* pSongRepository)
{
    FILE* fp;
    fp = fopen(fileName, "r");
    CHECK_RETURN_0(fp)
    if(fscanf(fp,"%d",&repository->numOfPlayList)!= 1)
        RETURN_0_CLOSE_FILE(fp)
    repository->systemPlaylists = (PlayList*) malloc(sizeof(PlayList)* repository->numOfPlayList);
    CHECK_RETURN_0(repository->systemPlaylists)
    for (int i = 0; i < repository->numOfPlayList; i++) {
        if(!readPlayListFromTextFile(&repository->systemPlaylists[i],fp,pSongRepository))
        {
            for (int j = 0; j < i; j++) {
                freePlayList(&repository->systemPlaylists[i]);
            }
            free(repository->systemPlaylists);
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}




int createNewSystemPlayList(PlayListRepository* pPlayRepository,SongRepository* pSongRepository)
{
    int maxSongs;
    do{
        printf("Enter Number Of Max Songs in PlayList 1 - %d\n",pSongRepository->numSongs);
        scanf("%d",&maxSongs);
    }
    while(maxSongs<0 || maxSongs>pSongRepository->numSongs);

    pPlayRepository->systemPlaylists = (PlayList*) realloc(pPlayRepository->systemPlaylists,(pPlayRepository->numOfPlayList+1)*(sizeof(PlayList)));
    CHECK_RETURN_0(pPlayRepository->systemPlaylists)
    initPlayListForSystem(&pPlayRepository->systemPlaylists[pPlayRepository->numOfPlayList]);
    eGenreOptions option = genreMenu();
    for (int i = 0; i < pSongRepository->numSongs && maxSongs; i++) {
        if (pSongRepository->songsArr[i].typeOfSong == option)
        {
            addSongToPlayList(&pPlayRepository->systemPlaylists[pPlayRepository->numOfPlayList], &pSongRepository->songsArr[i]);
            maxSongs--;
        }
    }
    printf("PlayList Created\n");
    printPlayList(&pPlayRepository->systemPlaylists[pPlayRepository->numOfPlayList]);
    pPlayRepository->numOfPlayList++;
    return 1;
}




void printPlayLists(const PlayListRepository* pPlayRepository)
{
    if (pPlayRepository->numOfPlayList < 1)
    {
        printf("No playlist to be printted\n");
        return;
    }
    for (int i = 0; i < pPlayRepository->numOfPlayList; i++)
    {
        printPlayList(&pPlayRepository->systemPlaylists[i]);
    }
}




void freePlayListsRepo(PlayListRepository* pPlayRepository)
{
    for (int i = 0; i < pPlayRepository->numOfPlayList; i++)
    {
        freePlayList(&pPlayRepository->systemPlaylists[i]);
    }
    free(pPlayRepository->systemPlaylists);
}


