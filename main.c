#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "artist.h"
#include "song.h"
#include "album.h"

int main() {
	FILE* fp,*fp1,*fp2,*fp3;
	fp = fopen("Song.text", "r");
	fp1 = fopen("Artist.text", "r");
    fp2 = fopen("Album.txt","w");
    fp3 = fopen("Album.bin","wb");
	Artist A;
	//initArtist(&A);
	//creatArtist(&A);
    loadArtistFromTextFile(&A, fp1);
	Song s;
	//initSong(&s, &A);
    readSongFromTextFile(&s, fp,&A,1);
	printSong(&s);
    Album aB;
    initAlbum(&aB,&A);
    addSong(&aB,&s);
    printAlbum(&aB);
    Song s2;
    initSong(&s2,&A);
    printSong(&s2);
    addSong(&aB,&s2);
    printAlbum(&aB);
    writeAlbumToBFile(&aB,fp3);
    writeAlbumToTextFile(&aB,fp2);
	fclose(fp);
	fclose(fp1);
    fclose(fp2);
    fclose(fp3);
	return 0;
}
