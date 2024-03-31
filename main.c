#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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
	FILE* fp,*fp1;
	fp = fopen("Song.bin", "rb");
	fp1 = fopen("Artist.bin", "rb");
	Artist A;
	//initArtist(&A);
	//creatArtist(&A);
	readArtistFromBFile(&A, fp1);
	Song s;
	//initSong(&s, &A);
	readSongFromBFile(&s, fp, &A, 1);
	printSong(&s);
	//system("start Song.mp4");
	fclose(fp);
	fclose(fp1);
	return 0;
}
