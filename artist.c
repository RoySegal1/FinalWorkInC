#include "artist.h"
#include "stdio.h"
#include "string.h"
#include "General.h"




void initArtist(Artist* artist)
{
    artist->name = NULL;
    artist->amountOfPlay = 0;
    artist->amountOfSongs = 0;
}


void showArtist(Artist* artist)
{
    printf("Artist Name: %s ",artist->name);
}

void getArtistName(Artist* artist)
{
    artist->name = getStrExactName("Enter artist name\n");
}

