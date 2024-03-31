#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "artist.h"
#include "song.h"

int main() {
	/*Artist A;
	initArtist(&A);
	Song s;
	initSong(&s,&A);
	FILE* fp;
	fp = fopen("Song.txt", "w");
	if (!fp)
		return 0;
	writeSongToTextFile(&s, fp);
	fclose(fp);*/
	FILE* fp;
	fp = fopen("Song.bin", "rb");
	//Artist A;
	//initArtist(&A);
	Song s;
	//initSong(&s, &A);
	readSongFromBFile(&s, fp);
	printSong(&s);
	fclose(fp);
	return 0;
}
