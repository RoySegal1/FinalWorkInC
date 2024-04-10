#include "string.h"
#include <stdlib.h>
#include "album.h"
#include "macros.h"
#include "General.h"
#include "fileHelper.h"


int initAlbum(Album* pAlbum, Artist* pArtist)
{
	if (!L_init(&pAlbum->songs))
		return ERROR;
	pAlbum->albumName = getStrExactName("Enter Album Name");
	pAlbum->artist = pArtist;
	pAlbum->numOfSongs = 0;
    return 1;
}

int addSongToAlbum(Album* pAlbum, Song* pSong,int fromFile)
{
    if(strcmp(pAlbum->artist->name,pSong->artist.name))
    {
        printf(ANSI_COLOR_RED"Song Artist Is Not The Album Artist. Cant Add Song! \n"ANSI_COLOR_RESET);
        return 4; // 4 for Not Same
    }
    if (findSongByName(pAlbum, pSong->songName) != NULL)
    {
        printf(ANSI_COLOR_RED"Cant Add Same Song Twice\n"ANSI_COLOR_RESET);
        return DUPLICATE;
    }
    else {

        NODE *tmp;
        tmp = pAlbum->songs.head.next;
        if (tmp == NULL) // if empty
            L_insert(&pAlbum->songs.head, pSong);
        else {
            while (tmp->next != NULL) // get to the last node
            {
                tmp = tmp->next;
            }
            L_insert(tmp, pSong); // add at the last node to be in order.
        }
        if(fromFile == 0)
            pAlbum->numOfSongs++;
        return 1;
    }
}

Song* findSongByName(const Album* pAlbum, const char* songName)
{
	NODE* tmp;
	tmp = pAlbum->songs.head.next; // first node
	Song* pTemp;
	while (tmp != NULL) // run through the list
	{
		pTemp = (Song*)tmp->key;
		if (!strcmp(pTemp->songName, songName))
			return pTemp;
		tmp = tmp->next;
	}
	return NULL;
}

int writeAlbumToTextFileWithOpenFile(const Album* pAlbum,FILE* fp)
{
    if(!pAlbum)
        return ERROR;
    fprintf(fp,"%s\n",pAlbum->artist->name);
    fprintf(fp,"%s\n",pAlbum->albumName);
    fprintf(fp,"%d\n",pAlbum->numOfSongs);
    NODE* tmp;
    Song* tmpSong;
    tmp = pAlbum->songs.head.next;
    while(tmp != NULL) {
        tmpSong = (Song*)tmp->key;
        fprintf(fp, "%s\n", tmpSong->songCode);
        tmp = tmp->next;
    }
    return 1;
}
int writeAlbumToBFileWithOpenFile(const Album* pAlbum, FILE* fp)
{
    CHECK_RETURN_0(fp)
    if(!writeStringToFile(pAlbum->artist->name,fp,"Error Writing Artist Name"))
        return 0;
    if(!writeStringToFile(pAlbum->albumName,fp,"Error Writing Album Name"))
        return 0;
    if(!writeIntToFile(pAlbum->numOfSongs,fp,"Error Writing Number Of Songs"))
        return 0;
    NODE* tmp;
    Song* tmpSong;
    tmp = pAlbum->songs.head.next;
    while(tmp != NULL) {
        tmpSong = (Song*)tmp->key;
        if(!writeCharsToFile(tmpSong->songCode, CODE_LENGTH,fp,"Error Writing Song Code"))
            return 0;
        tmp = tmp->next;
    }
    return 1;
}

int readAlbumFromTextFileWithOpenFile(Album* pAlbum, FILE* fp, Artist* artists, int size, const SongRepository* pSongs)
{
    CHECK_RETURN_0(fp)
    char temp[MAX_STR_LEN];
    if(!pAlbum)
        return 0;
    myGets(temp,MAX_STR_LEN,fp);
    pAlbum->artist = findArtistInArr(artists,size,temp);
    myGets(temp,MAX_STR_LEN,fp);
    pAlbum->albumName = getDynStr(temp);
    if(fscanf(fp,"%d",&pAlbum->numOfSongs) != 1)
    {
        free(pAlbum->albumName);
        return 0;
    }
    Song* tempSong;
    for (int i = 0; i < pAlbum->numOfSongs; i++) {
        myGets(temp,CODE_LENGTH,fp);
        tempSong = getSongFromRepositoryByCode(pSongs,temp);
        if(!addSongToAlbum(pAlbum,tempSong,1))
        {
            freeAlbum(pAlbum);
            return 0;
        }
    }
    return 1;
}

int readAlbumFromBFileWithOpenFile(Album* pAlbum, FILE* fp, Artist* artists, int size, const SongRepository* pSongs)
{
    char* temp2 = readStringFromFile(fp, "Error Reading Artist Name");
    if (!temp2)
        return 0;
        pAlbum->artist = findArtistInArr(artists, size, temp2);
    free(temp2); 
    pAlbum->albumName = readStringFromFile(fp, "Error Reading Album Name");
    if (!pAlbum->albumName)
        return 0;
        if (!readIntFromFile(&pAlbum->numOfSongs, fp, "Error Reading Number Of Songs"))
        {
            free(pAlbum->albumName);
            return 0;
        }
    char tmp[CODE_LENGTH];
    Song* tempSong;
    for (int i = 0; i < pAlbum->numOfSongs; i++) {
        if (!readCharsFromFile(tmp, CODE_LENGTH, fp, "Error Reading Song Code"))
        {
            freeAlbum(pAlbum);
            return 0;
        }
        tempSong = getSongFromRepositoryByCode(pSongs, tmp);
        if (!addSongToAlbum(pAlbum, tempSong, 1))
        {
            freeAlbum(pAlbum);
            return 0;
        }
    }
    return 1;
}


void freeAlbum(Album* pAlbum)
{
    free(pAlbum->albumName);
    L_free(&pAlbum->songs, NULL); // frees only the NODES and not the songs
}


void printAlbum(const Album* pAlbum)
{
	printf("Album name: %s\n", pAlbum->albumName);
	showArtistName(pAlbum->artist);
	L_print(&pAlbum->songs, printSongForAlbum);
}