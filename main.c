#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "artist.h"
#include "song.h"
#include "album.h"
#include "songRepository.h"
#include "playList.h"

int main() {
	FILE* fp,*fp1,*fp2;
	fp1 = fopen("Artist.text", "r");
    fp = fopen("PlayList1.txt","r");
    fp2 = fopen("PlayList1.bin","rb");
    if(!fp)
        return 0;
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
    readPlayListFromBFile(&P,fp2,&sR);
   // writePlayListToBFile(&P,fp2);
   // initPlayList(&P);
   // addSongToPlayList(&P,&sR.songsArr[0]);
   // addSongToPlayList(&P,&sR.songsArr[1]);
   // addSongToPlayList(&P,&sR.songsArr[2]);
    printPlayList(&P);
   // writePlayListToTextFile(&P,fp);
   // sortPlayList(&P);
   // printPlayList(&P);
    Song ps;
    findSong(&P);
    Song new ;
    initSong(&new,&A[0]);// creat new song
    addSongToRepository(&sR,&new);
    printAllSongs(&sR);
  /*  initAlbum(&album,&A[2]);
    addSongToAlbum(&album,&sR.songsArr[2]);
    addSongToAlbum(&album,&sR.songsArr[1]);
    printAlbum(&album);*/
    //writeAlbumToBFile(&album,"Album.bin");
    fclose(fp1);
    fclose(fp);
    fclose(fp2);
	return 0;
}
