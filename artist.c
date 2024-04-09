#include <stdio.h>
#include <stdlib.h>
#include "artist.h"
#include "string.h"
#include "General.h"
#include "fileHelper.h"
#include "macros.h"


int creatArtist(Artist* artist)
{
    artist->name = getStrExactName("Enter artist name\n");
    if(!artist->name)
        return ERROR;
    artist->aboutMe = getStrExactName("Write about the artist\n");
    if(!artist->aboutMe)
    {
        free(artist->name);
        return ERROR;
    }
    artist->amountOfPlay = 0;

    printf("Enter artist's number of Songs\n");
    scanf("%d", &artist->amountOfSongs);


    return 1;

}


void showArtist(const void *pArtist)
{
    Artist *temp = (Artist*)pArtist;
    printf(ANSI_COLOR_BLUE"Artist Name: %s\n"ANSI_COLOR_RESET,temp->name);
    printf("About him: %s\n",temp->aboutMe);
}




int	saveArtistToTextFile(const Artist * artist, FILE* fp)
{
    if (!artist)
        return 0;
    fprintf(fp, "%s\n", artist->name);
    fprintf(fp, "%s\n", artist->aboutMe);
    fprintf(fp, "%d\n", artist->amountOfPlay);
    fprintf(fp, "%d\n", artist->amountOfSongs);
    return 1;
}

int	loadArtistFromTextFile(Artist * artist, FILE* fp)
{
    char temp[MAX_STR_LEN];
    CHECK_RETURN_0(artist)

    myGets(temp, MAX_STR_LEN, fp);
    artist->name = getDynStr(temp);
    CHECK_RETURN_0_PRINT(artist->name,"Error reading artist name\n")

    myGets(temp, MAX_STR_LEN, fp);
    artist->aboutMe = getDynStr(temp);
    CHECK_RETURN_0_PRINT(artist->aboutMe,"Error reading artist CV\n")
    if(fscanf(fp, "%d", &artist->amountOfPlay) != 1)
    {
        printf("Error reading artist's amount of played\n");
        free(artist->name);
        free(artist->aboutMe);
        return 0;
    }
    if(fscanf(fp, "%d", &artist->amountOfSongs) != 1)
    {
        printf("Error reading artist's amount of songs\n");
        free(artist->name);
        free(artist->aboutMe);
        return 0;
    }

    return 1;
}


int writeArtistToBFile(Artist * pArtist,FILE* fp)
{
    if(!writeStringToFile(pArtist->name,fp,"Error Writing Artist Name"))
        return 0;
    if(!writeStringToFile(pArtist->aboutMe,fp,"Error Writing \"About me\""))
        return 0;
    if(!writeIntToFile(pArtist->amountOfPlay,fp,"Error Writing amount of played songs"))
        return 0;
    if(!writeIntToFile(pArtist->amountOfSongs,fp,"Error Writing amount of songs"))
        return 0;
    return 1;
}
int saveArtistToCompressFile(Artist* pArtist, FILE* fp)
{
    if(pArtist->amountOfPlay > MAX_NUM_PLAY) //more than we can compress 
        PRINT_RETURN_0("Cant compress num of artist to File")
    if (pArtist->amountOfSongs > MAX_NUM_SONGS)
        PRINT_RETURN_0("Cant compress num of songs to File")
    if (strlen(pArtist->name) > MAX_NAME_LEN)
        PRINT_RETURN_0("Cant compress name len of artist to File")
    if (strlen(pArtist->aboutMe) > MAX_CV_LEN)
         PRINT_RETURN_0("Cant compress CV len of artist to File")

    BYTE dataArtist[4];
    int len1  = strlen(pArtist->name);
    int len2 = strlen(pArtist->aboutMe);
    dataArtist[0] = len1 << 3 | len2 >> 5;
    dataArtist[1] = (len2 & 0x1F) << 3 | pArtist->amountOfSongs >> 4 ;
    dataArtist[2] = (pArtist->amountOfSongs & 0xF) << 4 | pArtist->amountOfPlay >> 8;
    dataArtist[3] = pArtist->amountOfPlay & 0xFF;
    if(fwrite(dataArtist, sizeof(BYTE), 4, fp) != 4)
    {
        printf("Error write artist data to compress file\n");
        return 0;
    }

    if(!writeStringToComprassFile(pArtist->name,fp,"Error write artist name to compress file\n"))
        return 0;
    if (!writeStringToComprassFile(pArtist->aboutMe,fp,"Error write artist VC to compress file\n"))
        return 0;

    return 1;
}

int readArtistFromBFile(Artist * pArtist,FILE* fp)
{
    pArtist->name = readStringFromFile(fp,"Error Reading Artist Name");
    if(pArtist->name == NULL)
        return 0;

    pArtist->aboutMe = readStringFromFile(fp,"Error Reading \"About me\"");
    if(pArtist->aboutMe == NULL)
        return 0;

    if(!readIntFromFile(&pArtist->amountOfPlay,fp,"Error Reading of played songs"))
        return 0;
    if(!readIntFromFile(&pArtist->amountOfSongs,fp,"Error Reading amount of songs"))
        return 0;

    return 1;
}

int readArtistFromCompressFile(Artist* pArtist,FILE* fp)
{
    BYTE dataArtist[4];
    if (fread(&dataArtist, sizeof(BYTE), 4, fp) != 4)
    {
        printf("Error reading artist's data from compress file\n");
        return 0;
    }
    int len1 = dataArtist[0] >> 3;
    int len2 = (dataArtist[0] & 0x7) << 5 | (dataArtist[1] >>3);
    pArtist->amountOfSongs = (dataArtist[1] & 0x7) << 4 | dataArtist[2] >> 4;
    pArtist->amountOfPlay = (dataArtist[2] & 0xF) << 8 | dataArtist[3];
    pArtist->name = (char*)calloc(len1 + 1, sizeof(char));
    if (!pArtist->name || fread(pArtist->name,sizeof(char),len1,fp) != len1)
        return 0;

    pArtist->aboutMe = (char*)calloc(len2 + 1, sizeof(char));
    if (!pArtist->aboutMe || fread(pArtist->aboutMe,sizeof(char),len2,fp) != len2)
        return 0;

    return 1;

}


void showArtistName(const void* pArtist)
{
    Artist *temp = (Artist*)pArtist;
    printf(ANSI_COLOR_BLUE"%s\n"ANSI_COLOR_RESET,temp->name);
}

void freeArtist(Artist *artist)
{
    free(artist->name);
    free(artist->aboutMe);
}
