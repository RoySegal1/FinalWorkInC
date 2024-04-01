//
// Created by User on 01/04/2024.
//
#include <stdlib.h>
#include "playList.h"
#include "General.h"


void initPlayList(PlayList* pPlay)
{
    pPlay->numOfSongs=0;
    pPlay->playlistName = getDynStr("Enter PlayList Name");
    pPlay->allSongs= NULL;
    pPlay->playListSortOp = 0;
    pPlay->typeOfPlayList = playListTypeMenu();
}

int addSongToPlayList(PlayList* pPlay, Song* pSong)
{
    pPlay->allSongs = (Song**)realloc(pPlay->allSongs,(pPlay->numOfSongs + 1)*sizeof(Song*));
    if(!pPlay->allSongs)
        return 0;
    pPlay->allSongs[pPlay->numOfSongs] = pSong;
    pPlay->numOfSongs++;
    pPlay->playListSortOp = eNone;
    return 1;
}

ePlayListsType playListTypeMenu()
{
    int opt;
    printf("PlayList Options:\n");
    do {
        for (int i = 1; i < eNofPlayListType; i++)
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

Song findSong(const PlayList* pPlay) // need to be modified maby, finding not a particular song
{
    int(*compare) (const void* S1,const void* S2) = NULL;
    Song sTemp ={0};
    Song* pTemp = &sTemp;
    switch(pPlay->playListSortOp)
    {
        case eAmountPlayed:
            compare = compareByAmountPlayed;
            printf("Enter the amount to search for\n");
            scanf("%d",&pTemp->amountPlayedSong);
            break;
        case eArtistName:
            compare = compareByArtistName;
            printf("Enter Artist name to search for\n");
            scanf("%s",pTemp->artist.name);
            break;
        case eGenre:
            compare = compareByGenre;
            pTemp->typeOfSong = genreMenu();
            break;
        case eSongName:
            compare = compareByName;
            printf("Enter Song name to search for\n");
            scanf("%s",pTemp->songName);
            break;
    }
    Song** pS = NULL;
    if(compare!=NULL)
    {
        Song** pS = bsearch(&pTemp,pPlay->allSongs,pPlay->numOfSongs,sizeof(Song*),compare);
    }
    return **pS;
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