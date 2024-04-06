#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <time.h>
#include <Windows.h>
#include "artist.h"
#include "song.h"
#include "album.h"
#include "songRepository.h"
#include "playList.h"
#include "user.h"
#include "macros.h"
#include "playlistRepository.h"
#include "artistRepository.h"
#include "main.h"


int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    int fileChoice;
    printf("Welcome To Our System\n");
    Sleep(1500);
    printf("Enter 1 For Text Files 2 For Binary File\n");
    do {
        scanf("%d", &fileChoice);
    } while (fileChoice < 1 || fileChoice>2);
    ArtistRepository A;
    PlayListRepository pR;
    initPlayListRepo(&pR);
    SongRepository sR;
    User user;
    if (!initSystemFromFile(&sR, &pR, &A, fileChoice))
        return 0;
    Album album;
    L_init(&album.songs);
    readAlbumFromTextFile(&album, "Album.txt", A.allArtists, A.numOfArtist, &sR);
    int choice;
    do {
        printf(ANSI_COLOR_GREEN"\nSystem Menu\n");
        printf("1. Add song to song repository\n");
        printf("2. Show all songs in song repository\n");
        printf("3. Create System Playlists\n");
        printf("4. Show All System Playlists\n");
        printf("5. Show all artists\n");
        printf("6. Add An artist\n");
        printf("7. Create a new user\n");
        printf("8. Use user from file\n");
        printf("9. Quit\n");
        printf("Enter your choice: "ANSI_COLOR_RESET);
        scanf("%d", &choice);

        // Implement functionality based on user choice
        switch (choice) {
        case 1:
            addSongToRepository(&sR, A.allArtists, A.numOfArtist);
            break;
        case 2:
            printAllSongs(&sR);
            break;
        case 3:
            createNewSystemPlayList(&pR, &sR);
            break;
        case 4:
            printPlayLists(&pR);
            break;
        case 5:
            showArtistRepository(&A);
            break;
        case 6:
        //    addArtistToRepostiory(&A);
            break;
        case 7:
            initUser(&user);
            userSubMenu(&user,&sR,&pR);
            choice = 9;
            break;
        case 8:
            printf("Enter User Name (with .txt/.bin) To Open File With\n");
        case 9:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    saveArtistRepositoryToFile(&A, "ComperssArtistRepo.bin", FROM_BINARY_FILE);
    writeUserToFile(&user, "dosent matter right now", FROM_BINARY_FILE);
    savePlayListRepositoryToFile(&pR, "PlayList.bin", FROM_BINARY_FILE);
    saveSongRepositoryToTextFile(&sR, "Songs.txt");
    saveSongRepositoryToBFile(&sR, "Songs.bin");
    freeAlbum(&album);
    freeSongRepository(&sR);
    freePlayListsRepo(&pR);
    freeArtistRepository(&A);
    freeUser(&user);
	return 0;
}






void userSubMenu(User* pUser, const SongRepository* pSongs, const PlayListRepository* pPlayLists) {
    int choice, playListChoice;
    do {
        printf("\nUser Submenu\n");
        printf("Hello %s\n", pUser->userName);
        printf("1. Add a System Playlist to user\n"); // need work
        printf("2. Delete a playlist from user\n");
        printf("3. Create a new playlist\n");
        printf("4. Delete a song from a user playlist\n");
        printf("5. Play a Playlist by order\n");
        printf("6. Shuffle a Playlist\n");
        printf("7. Add Album to User\n");
        printf("8. Delete an Album from User\n");
        printf("9. Print All Playlists\n");
        printf("10. Print All Albums\n");
        printf("11. Print All Data About User\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Implement functionality based on user choice
        switch (choice) {
        case 1:
            printf("Enter Index Of PlayList To Be Added 1 - %d\n", pPlayLists->numOfPlayList);
            printPlayLists(pPlayLists);
            do {
                scanf("%d", &playListChoice);
            } while (playListChoice<0 || playListChoice>pPlayLists->numOfPlayList);
            addPlayListToUser(pUser, &pPlayLists->systemPlaylists[playListChoice - 1]);
            break;
        case 2:
            deletePlayListFromUser(pUser);
            break;
        case 3:
            createPlayListToUser(pUser, pSongs);
            break;
        case 4:
            deleteSongFromUserPlayList(pUser);
            break;
        case 5:
            playByOrderPlayList(pUser);
            break;
        case 6:
            printf("Shuffling a Playlist...\n");
            break;
        case 7:
            printf("Adding Album to User...\n");
            break;
        case 8:
            deleteAlbumFromUser(pUser);
            break;
        case 9:
            printPlayListForUser(pUser);
            break;
        case 10:
            printAlbumsForUser(pUser);
            break;
        case 11:
            printUser(pUser);
            break;
        case 12:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 12);
}



int initSystemFromFile(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists, int typeFile)
{
    if (typeFile == FROM_BINARY_FILE)
    {
        if (!initArtistRepositoryFromFile(pArtists, ARTIST_REPO_FROM_BIN, FROM_BINARY_FILE))
            return 0;
        if (!loadSongsRepositoryFromBFile(pSong, SONGS_REPO_FROM_BIN, pArtists->allArtists, pArtists->numOfArtist))
            return 0;
        if (!loadPlayListRepositoryFromFile(pPlayList, PLAYLIST_REPO_FROM_BIN, pSong, FROM_BINARY_FILE))
            return 0;
    }
    else
    {
        if (!initArtistRepositoryFromFile(pArtists, ARTIST_REPO_FROM_TEXT, FROM_TEXT_FILE))
            return 0;
        if (!loadSongsRepositoryFromTextFile(pSong, SONGS_REPO_FROM_TEXT, pArtists->allArtists, pArtists->numOfArtist))
            return 0;
        if (!loadPlayListRepositoryFromFile(pPlayList, PLAYLIST_REPO_FROM_TEXT, pSong, FROM_TEXT_FILE))
            return 0;
    }
    return 1;
}


int saveSystemFiles(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists, int typeFile);
