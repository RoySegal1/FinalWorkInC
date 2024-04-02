//
// Created by User on 01/04/2024.
//
#include <stdlib.h>
#include "playList.h"
#include "General.h"
#include "string.h"


void initPlayList(PlayList* pPlay)
{
    pPlay->numOfSongs=0;
    pPlay->playlistName = getStrExactName("Enter PlayList Name");
    pPlay->allSongs= NULL;
    pPlay->playListSortOp = eNotOrderd;
    pPlay->typeOfPlayList = playListTypeMenu();
}

int addSongToPlayList(PlayList* pPlay, Song* pSong)
{
    pPlay->allSongs = (Song**)realloc(pPlay->allSongs,(pPlay->numOfSongs + 1)*sizeof(Song*));
    if(!pPlay->allSongs)
        return 0;
    pPlay->allSongs[pPlay->numOfSongs] = pSong;
    pPlay->numOfSongs++;
    pPlay->playListSortOp = eNotOrderd; // when we add a song the arr becomes not sorted.
    return 1;
}

int removeSongFromPlayList(PlayList* pPlay)
{
    printf("Enter index of song to remove\n");
    printPlayList(pPlay);
    int index;
    do{
        printf("Enter index 1-%d\n",pPlay->numOfSongs);
        scanf("%d",&index);
    }
    while(index<0||index>pPlay->numOfSongs);
    index -=1; // index goes from 1..numOfSongs,  so now 0...numOfSongs-1.
    pPlay->allSongs[index] = pPlay->allSongs[pPlay->numOfSongs-1];
    pPlay->allSongs = (Song**)realloc(pPlay->allSongs,(pPlay->numOfSongs - 1)*sizeof(Song*));
    if(!pPlay->allSongs)
        return 0;
    pPlay->numOfSongs--;
    pPlay->playListSortOp = eNotOrderd; // when we remove a song the arr becomes not sorted.
    return 1;
}

ePlayListsType playListTypeMenu()
{
    int opt;
    printf("PlayList Options:\n");
    do {
        for (int i = 0; i < eNofPlayListType; i++)
            printf("Enter %d for %s\n", i, playListType[i]);
        scanf("%d", &opt);
    } while (opt < 0 || opt >=eNofPlayListType);

    return (ePlayListsType)opt;
}


void sortPlayList(PlayList* pPlay)
{
    pPlay->playListSortOp = showSortMenu();
    int(*compare) (const void* S1,const void* S2) = NULL;
    switch(pPlay->playListSortOp)
    {
        case eAmountPlayed:
            compare = compareByAmountPlayed;
            break;
        case eArtistName:
            compare = compareByArtistName;
            break;
        case eGenre:
            compare = compareByGenre;
            break;
        case eSongName:
            compare = compareByName;
            break;
    }
    if(compare!=NULL)
        qsort(pPlay->allSongs,pPlay->numOfSongs,sizeof(Song*),compare);
}

void findSong(const PlayList* pPlay) // need to be modified maby, finding not a particular song
{
    int(*compare) (const void* S1,const void* S2) = NULL;
    Song sTemp = {0};
    Artist temp1 = {0};
    Song* pTemp = &sTemp;
    char temp[MAX_STR_LEN];
    switch(pPlay->playListSortOp)
    {
        case eAmountPlayed:
            compare = compareByAmountPlayed;
            printf("Enter the amount to search for\n");
            scanf("%d",&sTemp.amountPlayedSong);
            break;
        case eArtistName:
            compare = compareByArtistName;
            printf("Enter Artist name to search for\n");
            myGets(temp,MAX_STR_LEN,stdin);
            sTemp.artist.name = temp;
            break;
        case eGenre:
            compare = compareByGenre;
            sTemp.typeOfSong = genreMenu();
            break;
        case eSongName:
            compare = compareByName;
            printf("Enter Song name to search for\n");
            myGets(temp,MAX_STR_LEN,stdin);
            sTemp.songName = temp;
            break;
        case eNofSortOpt:
            printf("Array not sorted, cant perform search.\n");
            break;
    }
    if(compare!=NULL) {
        Song **pS = bsearch(&pTemp, pPlay->allSongs, pPlay->numOfSongs, sizeof(Song *), compare);
        if (pS == NULL) {
            printf("didnt find\n");
        } else {
            printSong(*pS);
        }
    }
}


eSortOption showSortMenu()
{
    int opt;
    printf("Base on what field do you want to sort?\n");
    do {
        for (int i = 1; i < eNofSortOpt; i++)
            printf("Enter %d for %s\n", i, sortOptStr[i]);
        scanf("%d", &opt);
    } while (opt < 0 || opt >=eNofSortOpt);

    return (eSortOption)opt;
}


void printPlayList(const PlayList* pPlay) {
    printf("PlayList (%s) Name: %s, Has %d Songs\n",playListType[pPlay->typeOfPlayList],pPlay->playlistName,pPlay->numOfSongs);
    for (int i = 0; i < pPlay->numOfSongs; i++) {
        printf("%d.",i+1);
        printSongForPlayList(pPlay->allSongs[i]);
    }

}