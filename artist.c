#include <stdio.h>
#include <stdlib.h>
#include "artist.h"
#include "string.h"
#include "General.h"
#include "fileHelper.h"
#include "macros.h"


void initArtist(Artist* artist)
{
    artist->name = NULL;
    artist->aboutMe = NULL;
    artist->amountOfPlay = 0;
    artist->amountOfSongs = 0;
}


void showArtist(const Artist* artist)
{
    printf("Artist Name: %s\n ",artist->name);
    printf("About him: %s\n ",artist->aboutMe);
}


int creatArtist(Artist* artist)
{
    artist->name = getStrExactName("Enter artist name\n");
    if(!artist->name)
        return 0;
    artist->aboutMe = getStrExactName("Write about the artist\n");
    if(!artist->aboutMe)
    {
        free(artist->name);
        return 0;
    }
    return 1;

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

void freeArtist(Artist *artist)
{
    free(artist->name);
    free(artist->aboutMe);

}
