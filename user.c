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


void playByOrderPlayList(const User* pUser)
{
    printf("Enter Number Of PlayList To Be Played. From 1 - %d\n",pUser->numOfPlaylists);
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        printf("%d."ANSI_COLOR_BLUE"%s"ANSI_COLOR_RESET"\n",i+1,pUser->userPlayLists[i].playlistName);
    }
    int choice;
    do{
        scanf("%d",&choice);
    }
    while(choice<0 | choice>pUser->numOfPlaylists);
    for (int i = 0; i < pUser->userPlayLists[choice-1].numOfSongs; ++i) {
        playSong(pUser->userPlayLists[choice - 1].allSongs[i]);
    }
}

int createPlayListToUser(User* pUser, SongRepository* pSongs)
{
    pUser->userPlayLists = (PlayList*)realloc(pUser->userPlayLists,(pUser->numOfPlaylists+1)*sizeof(PlayList));
    CHECK_RETURN_0(pUser->userPlayLists)
    initPlayListForUser(&pUser->userPlayLists[pUser->numOfPlaylists]);
    printAllSongs(pSongs);
    int choice,cont = 0,addFlag;
    while(!cont) {
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
     printf("Do you want to add more songs to playlist? 0 for yes any other number of no\n");
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
    return 1;
}

int addPlayListToUser(User* pUser, PlayList* pPlay)
{
    CHECK_RETURN_0(pPlay)
    pUser->userPlayLists = (PlayList*)realloc(pUser->userPlayLists,(pUser->numOfPlaylists+1)*sizeof(PlayList));
    CHECK_RETURN_0(pUser->userPlayLists)
    pUser->userPlayLists[pUser->numOfPlaylists] = *pPlay; // maybe not shallow
    pUser->numOfPlaylists++;
    return 1;
}

int deletePlayListFromUser(User* pUser)
{
    printf("Enter Number Of PlayList To Be Deleted. From 1 - %d\n",pUser->numOfPlaylists);
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        printf("%d."ANSI_COLOR_BLUE"%s"ANSI_COLOR_RESET"\n",i+1,pUser->userPlayLists[i].playlistName);
    }
    int choice;
    do{
        scanf("%d",&choice);
    }
    while(choice<0 | choice>pUser->numOfPlaylists);
    pUser->userPlayLists[choice-1] = pUser->userPlayLists[pUser->numOfPlaylists-1];
    pUser->userPlayLists = (PlayList*)realloc(pUser->userPlayLists,(pUser->numOfPlaylists-1)*sizeof(PlayList));
    CHECK_RETURN_0_PRINT_ALOC(pUser->userPlayLists)
    pUser->numOfPlaylists--;
    return 1;
}
int deleteAlbumFromUser(User* pUser)
{
    printf("Enter Number Of Album To Be Deleted. From 1 - %d\n",pUser->numOfAlbums);
    for (int i = 0; i < pUser->numOfAlbums; i++)
    {
        printf("%d."ANSI_COLOR_BLUE"%s"ANSI_COLOR_RESET"\n",i+1,pUser->userAlbums[i].albumName);
    }
    int choice;
    do{
        scanf("%d",&choice);
    }
    while(choice<0 | choice>pUser->numOfAlbums);
    pUser->userAlbums[choice-1] = pUser->userAlbums[pUser->numOfAlbums-1];
    pUser->userAlbums = (Album*) realloc(pUser->userAlbums,(pUser->numOfAlbums-1)*sizeof(Album));
    CHECK_RETURN_0_PRINT_ALOC(pUser->userAlbums)
    pUser->numOfAlbums--;
    return 1;
}

int addAlbumToUser(User* pUser, Album* pAlbums)
{
    CHECK_RETURN_0(pAlbums)
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
