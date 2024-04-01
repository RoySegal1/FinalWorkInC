#include "string.h"

#include "album.h"
#include "macros.h"
#include "General.h"
#include "fileHelper.h"


int initAlbum(Album* pAlbum, Artist* pArtist)
{
	if (!L_init(&pAlbum->songs))
		return ERROR;
	pAlbum->albumName = getStrExactName("Enter Album Name");
	pAlbum->artist = *pArtist;
	pAlbum->numOfSongs = 0;
    return 1;
}

int addSong(Album* pAlbum, Song* pSong)
{
	NODE* tmp;
	tmp = pAlbum->songs.head.next;
	if (tmp == NULL) // if empty
		L_insert(&pAlbum->songs.head, pSong);
	else
	{
		while (tmp->next != NULL) // get to the last node
		{
			tmp = tmp->next;
		}
		L_insert(tmp, pSong);
	}
	pAlbum->numOfSongs++;
    return 1;
}

Song* findSongByName(Album* pAlbum, const char* songName)
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

int writeAlbumToTextFile(Album* pAlbum, FILE* fp)
{
    if(!pAlbum)
        return ERROR;
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
    fprintf(fp,"%s\n",pAlbum->artist.name);
    return 1;
}

int writeAlbumToBFile(Album* pAlbum, FILE* fp)
{
    if(!writeStringToFile(pAlbum->albumName,fp,"Error Writing Album Name"))
        return 0;
    if(!writeIntToFile(pAlbum->numOfSongs,fp,"Error Writing Number Of Songs"))
        return 0;
    NODE* tmp;
    Song* tmpSong;
    tmp = pAlbum->songs.head.next;
    while(tmp != NULL) {
        tmpSong = (Song*)tmp->key;
        if(!writeCharsToFile(tmpSong->songCode,5,fp,"Error Writing Song Code"))
            return 0;
        tmp = tmp->next;
    }
    if(!writeStringToFile(pAlbum->artist.name,fp,"Error Writing Artist Name"))
        return 0;
    return 1;
}

int readAlbumFromTextFile(Album* pAlbum, FILE* fp, Artist* artists, int size/*,songRepostory pSongs*/)
{
    char temp[MAX_STR_LEN];
    if(!pAlbum)
        return 0;
    myGets(temp,MAX_STR_LEN,fp);
    pAlbum->albumName = getDynStr(temp);
    if(fscanf(fp,"%d",&pAlbum->numOfSongs) != 1)
        return 0;
    Song* tempSong;
    for (int i = 0; i < pAlbum->numOfSongs; i++) {
        myGets(temp,MAX_STR_LEN,fp);
        //tempSong == getSongFromRepositoryByCode(temp,pSongs);
        addSong(pAlbum,tempSong);
    }
    myGets(temp,MAX_STR_LEN,fp);
    pAlbum->artist = *findArtistInArr(artists,size,temp);
    return 1;
}

int readAlbumFromBFile(Album* pAlbum, FILE* fp, Artist* artists, int size/*,songRepostory pSongs*/)
{
    pAlbum->albumName = readStringFromFile(fp,"Error Reading Album Name");
    if(!pAlbum->albumName)
        return 0;
    if(!readIntFromFile(&pAlbum->numOfSongs,fp,"Error Reading Number Of Songs"))
        return 0;
    char tmp[5];
    Song* tempSong;
    for (int i = 0; i < pAlbum->numOfSongs; i++) {
        if(!readCharsFromFile(tmp,5,fp,"Error Reading Song Code"))
            return 0;
        //tempSong == getSongFromRepositoryByCode(tmp,pSongs);
        addSong(pAlbum,tempSong);
    }
    char *temp2 = readStringFromFile(fp,"Error Reading Artist Name");
    if(!temp2)
        return 0;
    pAlbum->artist = *findArtistInArr(artists,size,temp2);
    return 1;
}



void printAlbum(const Album* pAlbum)
{
	printf("Album name: %s\nThere are %d Songs in the Album\n", pAlbum->albumName, pAlbum->numOfSongs);
	showArtist(&pAlbum->artist);
	L_print(&pAlbum->songs, printSongForAlbum);
}