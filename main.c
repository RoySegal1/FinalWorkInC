#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <time.h>
//#include <SDL3/SDL.h>
//#include <SDL3_mixer/SDL_mixer.h>
//#include <SDL3/SDL_audio.h>
//#include <SDL3/main.h>
#include "artist.h"
#include "song.h"
#include "album.h"
#include "songRepository.h"
#include "playList.h"
#include "user.h"
#include "macros.h"


int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); 
	FILE* fp, * fp1, * fp2;
	fp1 = fopen("Artist.text", "r");
    fp = fopen("CompressArtist.bin", "rb");
    if(!fp)
        return 0;
    int length = 3;
    //fscanf(fp1, "%d", &length);
    Artist* A = (Artist*)malloc(sizeof(Artist)*length);
    for (int i = 0; i < length; i++) {
        if (!readArtistFromCompressFile(&A[i], fp))
        {
            fclose(fp);
            return 0;
        }
    }
   /* for (int i = 0; i < length; i++) {
        if (!saveArtistToCompressFile(&A[i], fp))
        {
            fclose(fp);
            return 0;
        }
    }*/
    SongRepository sR;
    //creatSongsArr(&sR);
    if (!loadSongsRepositoryFromBFile(&sR, "Songs.bin", A, length))
        return 0;
    //saveSongRepositoryToBFile(&sR,"Songs.bin");
    printAllSongs(&sR);
    Song p;
    initSong(&p, &A[2]);
    addSongToRepository(&sR, &p);
    printAllSongs(&sR);
    //playSong(&sR.songsArr[0],5);
    Album album;
    L_init(&album.songs);
    readAlbumFromTextFile(&album,"Album.txt",A,length,&sR);
    //writeAlbumToBFile(&album, "Album.bin");
    //printAlbum(&album);
    User user;
    readUserFromTextFile(&user, "user.txt", A, length, &sR);
    //initUser(&user);
   // createPlayListToUser(&user, &sR);
    //addAlbumToUser(&user, &album);
    printUser(&user);
    fclose(fp1);
    fclose(fp);
    writeUserToTextFile(&user, "user.txt");
    saveSongRepositoryToTextFile(&sR, "Songs.txt");
    saveSongRepositoryToBFile(&sR, "Songs.bin");
  //  fclose(fp2);
    freeAlbum(&album);
    //freePlayList(&P);
    freeSongRepository(&sR);
    freeArtist(&A[0]);
    freeArtist(&A[1]);
    freeArtist(&A[2]);
    free(A);
    freeUser(&user);
	return 0;
}
