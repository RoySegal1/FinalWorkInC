#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "song.h"
#include "General.h"




void initSong(Song* pSong /*,Artist* pArtist*/)
{
    pSong->songName = getStrExactName("Enter Song Name");
    getCode(pSong->songCode,codeHelper);
    codeHelper++;
    getLength(pSong);
    pSong->typeOfSong = genreMenu();
    pSong->amountPlayedSong = 0;
    //pSong->artist = *pArtist;
}

void getCode(char code[5],int num)
{
    for (int i = 3; i >= 0; i--) {
        code[i]= num%10 + '0';
        num/=10;
    }
    code[4] = '\0';
}

void getLength(Song* pSong)
{
    int minutes,seconds;
    do{
        printf("Enter minutes\n");
        scanf("%d",&minutes);
    }
    while(minutes<0||minutes>60);
    pSong->minutes = minutes;
    do{
        printf("Enter seconds\n");
        scanf("%d",&seconds);
    }
    while(seconds<0||seconds>60);
    pSong->seconds = seconds;
}


void printSong(const void* pSong)
{
    Song* tempSong = (Song*) pSong;
    printf("Song Name: %s\nSong Length: %d.%d minutes\n",tempSong->songName,tempSong->minutes,tempSong->seconds);
    printf("Song Genre: %s\n",typeOfGenre[tempSong->typeOfSong]);
    printf("Song Code: %s\n",tempSong->songCode);
}


eGenreOptions genreMenu()
{
    int opt;
    printf("Genre Options:\n");
    do {
        for (int i = 1; i < eNumOfOptions; i++)
            printf("Enter %d for %s\n", i, typeOfGenre[i]);
        scanf("%d", &opt);
    } while (opt < 0 || opt >=eNumOfOptions);

    return (eGenreOptions)opt;
}


int isSongType(const Song* pSong,eGenreOptions genre)
{
    return pSong->typeOfSong == genre;
}
void freeSong(void* pSong)
{
    Song* temp = (Song*) pSong;
    free(temp->songName);
}

//int compareByArtistName(const void* pSong1,const void* pSong2);
int compareByName(const void* pSong1,const void* pSong2)
{
    Song* temp1 = (Song*) pSong1;
    Song* temp2 = (Song*) pSong2;
    return strcmp(temp1->songName,temp2->songName);
}
int compareByAmountPlayed(const void* pSong1,const void* pSong2)
{
    Song* temp1 = (Song*) pSong1;
    Song* temp2 = (Song*) pSong2;
    return temp1->amountPlayedSong-temp2->amountPlayedSong;
}