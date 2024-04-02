#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "artist.h"
#include "song.h"
#include "album.h"
#include "songRepository.h"
#include "playList.h"

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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
        if (!loadArtistFromTextFile(&A[i], fp1))
            return 0;
    }
    SongRepository sR;
    //creatSongsArr(&sR);
    if (!loadSongsRepositoryFromTextFile(&sR, "Songs.text", A, length))
        return 0;
    //saveSongRepositoryToBFile(&sR,"Songs.bin");
    printAllSongs(&sR);
    Album album;
    L_init(&album.songs);
    readAlbumFromTextFile(&album,"Album.txt",A,length,&sR);
    printAlbum(&album);
   // PlayList P;
   // readPlayListFromBFile(&P,fp2,&sR);
   // writePlayListToBFile(&P,fp2);
   // initPlayList(&P);
   // addSongToPlayList(&P,&sR.songsArr[0]);
   // addSongToPlayList(&P,&sR.songsArr[1]);
   // addSongToPlayList(&P,&sR.songsArr[2]);
   // printSong(&sR.songsArr[0]);
   // printPlayList(&P);
   // writePlayListToTextFile(&P,fp);
    //sortPlayList(&P);
   // printPlayList(&P);
   // Song ps;
    //findSong(&P);
  /*  initAlbum(&album,&A[2]);
    addSongToAlbum(&album,&sR.songsArr[2]);
    addSongToAlbum(&album,&sR.songsArr[1]);
    printAlbum(&album);*/
    //writeAlbumToBFile(&album,"Album.bin");
    fclose(fp1);
    fclose(fp);
    fclose(fp2);
    freeAlbum(&album);
    //freePlayList(&P);
    freeSongRepository(&sR);
    freeArtist(&A[0]);
    freeArtist(&A[1]);
    freeArtist(&A[2]);
    free(A);
	return 0;
}
