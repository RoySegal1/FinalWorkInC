//
// Created by User on 02/04/2024.
//
#include <stdlib.h>
#include "user.h"
#include "macros.h"
#include "General.h"


void initUser(User* pUser)
{
    pUser->numOfAlbums=0;
    pUser->numOfPlaylists = 0;
    pUser->userName = getStrExactName("Enter User Name");
    pUser->userAlbums = NULL;
    pUser->userPlayLists = NULL;
}

int createPlayListToUser(User* pUser, SongRepository* pSongs)
{
    pUser->userPlayLists = (PlayList*)realloc(pUser->userPlayLists,(pUser->numOfPlaylists+1)*sizeof(PlayList));
    CHECK_RETURN_0(pUser->userPlayLists)
    initPlayListForUser(&pUser->userPlayLists[pUser->numOfPlaylists]);
    printAllSongs(pSongs);
    int choice,cont = 1,addFlag;
    while(cont) {
        do {
            printf("Enter Number Of Song To Add From 1-%d\n", pSongs->numSongs);
            scanf("%d", &choice);
        } while (choice < 1 || choice > pSongs->numSongs);
     addFlag = addSongToPlayList(&pUser->userPlayLists[pUser->numOfPlaylists],&pSongs->songsArr[choice-1]);
     if(addFlag == 0)
     {
         printf("error\n");
         return 0;
     }
     if(addFlag == 1)
         printf("Song added\n");
     printf("Do you want to add more songs to playlist? 1 for yes any other number of no\n");
     scanf("%d",&cont);
    }
    pUser->numOfPlaylists++;
    return 1;
}

int deleteSongFromUserPlayList(User* pUser,int index)
{
    if (index<0 || index>pUser->numOfPlaylists)
        return 0;
    if (pUser->userPlayLists[index].numOfSongs < 1) // empty PlayList
        return 0;
    if (!removeSongFromPlayList(&pUser->userPlayLists[index]))
        return 0;
}

int addPlayListToUser(User* pUser, PlayList* pPlay)
{
    pUser->userPlayLists = (PlayList*)realloc(pUser->userPlayLists,(pUser->numOfPlaylists+1)*sizeof(PlayList));
    CHECK_RETURN_0(pUser->userPlayLists)
    pUser->userPlayLists[pUser->numOfPlaylists] = *pPlay; // maybe not shallow
    pUser->numOfPlaylists++;
    return 1;
}

int addAlbumToUser(User* pUser, Album* pAlbums)
{
    pUser->userAlbums = (Album *)realloc(pUser->userAlbums,(pUser->numOfAlbums+1)*sizeof(Album));
    CHECK_RETURN_0(pUser->userAlbums)
    pUser->userAlbums[pUser->numOfAlbums] = *pAlbums; // maybe not shallow
    pUser->numOfAlbums++;
    return 1;
}



void printUser(const User* pUser)
{
    printf(ANSI_COLOR_GREEN"User Name: %s Has %d PlayLists, %d Albums\n", pUser->userName, pUser->numOfPlaylists, pUser->numOfAlbums);
    printf(ANSI_COLOR_RESET);
    printPlayListForUser(pUser);
    printAlbumsForUser(pUser);
}


void printPlayListForUser(const User* pUser)
{
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        printPlayList(&pUser->userPlayLists[i]);
    }
}

void printAlbumsForUser(const User* pUser)
{
    for (int i = 0; i < pUser->numOfAlbums; i++)
    {
        printAlbum(&pUser->userAlbums[i]);
    }
}

void freeUser(User* pUser)
{
    for (int i = 0; i < pUser->numOfAlbums; i++)
    {
        freeAlbum(&pUser->userAlbums[i]);
    }
    free(pUser->userAlbums);
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        freePlayList(&pUser->userPlayLists[i]);
    }
    free(pUser->userPlayLists);
    free(pUser->userName);
}
