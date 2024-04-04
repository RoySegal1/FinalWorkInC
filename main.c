#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
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


int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); 
	FILE* fp, * fp1, * fp2;
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
    saveSongRepositoryToBFile(&sR,"Songs.bin");
    printAllSongs(&sR);
    //playSong(&sR.songsArr[0],5);
    Album album;
    L_init(&album.songs);
    readAlbumFromTextFile(&album,"Album.txt",A,length,&sR);
    User user;
    readUserFromTextFile(&user, "user.txt", &A, length, &sR);
    //initUser(&user);
    //createPlayListToUser(&user,&sR);
    //if (!deleteSongFromUserPlayList(&user, 0))
      //  return 0;
    printUser(&user);
   // printPlayListForUser(&user);
   // playByOrderPlayList(&user);
   // writeUserToTextFile(&user, "user.txt");
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
    freeUser(&user);
    
	return 0;
}
