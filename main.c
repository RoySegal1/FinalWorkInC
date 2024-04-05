#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <time.h>
#include "artist.h"
#include "song.h"
#include "album.h"
#include "songRepository.h"
#include "playList.h"
#include "user.h"
#include "macros.h"
#include "playlistRepository.h"


int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); 
    FILE* fp;
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
    PlayListRepository pR;
    initPlayListRepo(&pR);
    SongRepository sR;
    if (!loadSongsRepositoryFromBFile(&sR, "Songs.bin", A, length))
        return 0;
    loadPlayListArrFromTextfile(&pR, "PlayList.txt", &sR);
    User user;
    readUserFromTextFile(&user, "user.txt", A, length, &sR);
    Album album;
    L_init(&album.songs);
    readAlbumFromTextFile(&album, "Album.txt", A, length, &sR);
    Song pTemp;
    int choice;
    do {
        printf("\nMain Menu\n");
        printf("1. Add song to song repository\n");
        printf("2. Show all songs in song repository\n");
        printf("3. Create System Playlists\n");
        printf("4. Show All System Playlists\n");
        printf("5. Show all artists\n");
        printf("6. Add artist\n");
        printf("7. Create a new user\n");
        printf("8. Use user from file\n");
        printf("9. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Implement functionality based on user choice
        switch (choice) {
        case 1:
                addSongToRepository(&sR,A,length);
            break;
        case 2:
            //Song pTemp;
            printAllSongs(&sR);
            break;
        case 3:
            createNewSystemPlayList(&pR, &sR);
            break;
        case 4:
            printPlayLists(&pR);
            break;
        case 5:
         //   addArtist();
            break;
        case 6:
        //    createUser();
            break;
        case 7:

        case 9:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);




    fclose(fp);
    writeUserToTextFile(&user, "user.txt");
    savePlayListArrToTextfile(&pR, "PlayList.txt");
    saveSongRepositoryToTextFile(&sR, "Songs.txt");
    saveSongRepositoryToBFile(&sR, "Songs.bin");
    freeAlbum(&album);
    freeSongRepository(&sR);
    freeArtist(&A[0]);
    freeArtist(&A[1]);
    freeArtist(&A[2]);
    free(A);
    freeUser(&user);
    freePlayLists(&pR);
	return 0;
}
