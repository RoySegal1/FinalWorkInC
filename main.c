#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "artist.h"
#include "song.h"
#include "album.h"
#include "songRepository.h"
#include "playList.h"

int main() {
	FILE* fp,*fp1;
	fp1 = fopen("Artist.text", "r");
    int length;
    fscanf(fp1,"%d",&length);
    Artist *A = malloc(sizeof(Artist)*length);
    for (int i = 0; i < length; i++) {
        loadArtistFromTextFile(&A[i], fp1);
    }
    SongRepository sR;
    //creatSongsArr(&sR);
    loadSongsRepositoryFromTextFile(&sR,"Songs.text",A,length);
    printSong(&sR.songsArr[0]);
    Album album;
    L_init(&album.songs);
    readAlbumFromBFile(&album,"Album.bin",A,length,&sR);
    PlayList P;
    initPlayList(&P);
    addSongToPlayList(&P,&sR.songsArr[0]);
    addSongToPlayList(&P,&sR.songsArr[1]);
    addSongToPlayList(&P,&sR.songsArr[2]);
    printPlayList(&P);
    sortPlayList(&P);
    printPlayList(&P);
    Song ps;
    findSong(&P);
  /*  initAlbum(&album,&A[2]);
    addSongToAlbum(&album,&sR.songsArr[2]);
    addSongToAlbum(&album,&sR.songsArr[1]);
    printAlbum(&album);*/
    //writeAlbumToBFile(&album,"Album.bin");
    fclose(fp1);
	return 0;
}
