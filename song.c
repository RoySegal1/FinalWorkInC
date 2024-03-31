#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "song.h"
#include "General.h"
#include "macros.h"
#include "fileHelper.h"




void initSong(Song* pSong ,Artist* pArtist)
{
    pSong->songName = getStrExactName("Enter Song Name");
    getCode(pSong->songCode,codeHelper);
    codeHelper++;
    getLength(pSong);
    pSong->typeOfSong = genreMenu();
    pSong->amountPlayedSong = 0;
    pSong->artist = *pArtist;
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

int compareByArtistName(const void* pSong1,const void* pSong2)
{
    Song* temp1 = (Song*) pSong1;
    Song* temp2 = (Song*) pSong2;
    return strcmp(temp1->artist.name,temp2->artist.name);
}
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



int readSongFromBFile(Song* pSong,FILE* fp)
{
    //READ ARTIST
    pSong->songName = readStringFromFile(fp,"Error Reading Song Name");
    if(pSong->songName == NULL)
        return 0;
    if(readCharsFromFile(pSong->songCode,5,fp,"Error Reading Song Code"))
        return 0;
    if(readIntFromFile(&pSong->minutes,fp,"Error Reading Minutes"))
        return 0;
    if(readIntFromFile(&pSong->seconds,fp,"Error Reading Seconds"))
        return 0;
    if(readIntFromFile(&pSong->amountPlayedSong,fp,"Error Reading Amount Played"))
        return 0;
    int temp;
    if(readIntFromFile(&temp,fp,"Error Reading Type Of Song"))
        return 0;
    pSong->typeOfSong = temp;
    return 1;
}
int writeSongToBFile(Song* pSong,FILE* fp)
{
    //WriteArtist
    if(writeStringToFile(pSong->songName,fp,"Error Writing Song Name"))
        return 0;
    if(writeCharsToFile(pSong->songCode,5,fp,"Error Writing Song Code"))
        return 0;
    if(writeIntToFile(pSong->minutes,fp,"Error Writing Minutes"))
        return 0;
    if(writeIntToFile(pSong->seconds,fp,"Error Writing Seconds"))
        return 0;
    if(writeIntToFile(pSong->amountPlayedSong,fp,"Error Writing Amount Played"))
        return 0;
    if(writeIntToFile(pSong->typeOfSong,fp,"Error Writing Type of song"))
        return 0;
    return 1;


}