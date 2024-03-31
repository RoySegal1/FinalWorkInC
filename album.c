#include "album.h"
#include "macros.h"
#include "General.h"

int initAlbum(Album* pAlbum, Artist* pArtist)
{
	if (!L_init(&pAlbum->songs))
		return ERROR;
	pAlbum->albumName = getStrExactName("Enter Album Name");
	pAlbum->artist = *pArtist;
	pAlbum->numOfSongs = 0;
}

int addSong(Album* pAlbum, Song* pSong)
{
	NODE* tmp;
	tmp = pAlbum->songs.head.next;
	while (tmp->next != NULL) // get to the last node
	{
		tmp = tmp->next;
	}
	L_insert(tmp, pSong);
	pAlbum->numOfSongs++;
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

void printAlbum(Album* pAlbum)
{
	printf("Album name: %s\nThere are %d Songs in the Album\n", pAlbum->albumName, pAlbum->numOfSongs);
	showArtist(&pAlbum->artist);
	L_print(&pAlbum->songs, printSong);
}