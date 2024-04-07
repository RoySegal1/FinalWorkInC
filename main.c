#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
//#include <crtdbg.h>
#include <time.h>
//#include <unistd.h>
#include "string.h"
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
#include "General.h"



int main() {
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    int fileChoice;
    printf(ANSI_COLOR_GREEN"Welcome To Our System\n"ANSI_COLOR_RESET);
    Sleep(2);
    printf("Enter 1 For Text Files 2 For Binary File\n");
    do {
        scanf("%d", &fileChoice);
    } while (fileChoice < 1 || fileChoice>2);
    ArtistRepository A;
    PlayListRepository pR;
    initPlayListRepo(&pR);
    SongRepository sR;
    AlbumManager aManager;
    User user;
    initUserZeros(&user);
    if (!initSystemFromFile(&sR, &pR, &A,&aManager, fileChoice))
        return 0;
//    Album album;
//    L_init(&album.songs);

//    readAlbumManagerFromFile(&aManager, "Albums.txt", A.allArtists, A.numOfArtist, &sR, FROM_TEXT_FILE);
 //   readAlbumFromTextFile(&album, "Album.txt", A.allArtists, A.numOfArtist, &sR);
    int choice;
    char userFileName[MAX_STR_LEN];
    do {
        printf(ANSI_COLOR_GREEN"\nSystem Menu\n");
        printf("1. Add song to song repository\n");
        printf("2. Show all songs in song repository\n");
        printf("3. Create System Playlists\n");
        printf("4. Show All System Playlists\n");
        printf("5. Show all artists\n");
        printf("6. Add An artist\n");
        printf("7. Create a new album\n");
        printf("8. Add song to album\n");
        printf("9. Show all albums\n");
        printf("10. Create a new user\n");
        printf("11. Use user from file\n");
        printf("12. Quit\n");
        printf("Enter your choice: "ANSI_COLOR_RESET);
        scanf("%d", &choice);
        // Implement functionality based on user choice
        switch (choice) {
        case 1:
            if(addSongToRepository(&sR, A.allArtists, A.numOfArtist) == ERROR)
            {
                freeSystem(&sR, &pR, &A, &aManager, &user);
                return ERROR;
            }
            break;
        case 2:
            printAllSongs(&sR);
            break;
        case 3:
            if(createNewSystemPlayList(&pR, &sR) == ERROR)
            {
                freeSystem(&sR, &pR, &A, &aManager, &user);
                return ERROR;
            }
            break;
        case 4:
            printPlayLists(&pR);
            break;
        case 5:
            showArtistRepository(&A);
            break;
        case 6:
            if (addArtistToRepository(&A) == ERROR)
            {
                freeSystem(&sR, &pR, &A, &aManager, &user);
                return ERROR;
            }
            break;
        case 7:
                if(addAlbumToManager(&aManager,&A) == ERROR)
                {
                    freeSystem(&sR, &pR, &A, &aManager, &user);
                    return 0;
                }
                break;
        case 8:
                addSongToAlbumManager(&aManager,&sR);
                break;
        case 9:
                printAlbumManager(&aManager);
                break;
        case 10:
            initUser(&user);
            if (userSubMenu(&user, &sR, &pR, &aManager) == ERROR)
            {
                freeSystem(&sR,&pR,&A,&aManager,&user);
                return 0;
            }
            endProgram(&sR, &pR, &A, &aManager, &user);
            choice = 12;
            break;
        case 11:
            printf("Enter User Name To Open File With\n");
            scanf("%s", userFileName);
            if (fileChoice == FROM_BINARY_FILE)
                strcat(userFileName, ".bin");
            else
                strcat(userFileName, ".txt");
            printf("%s\n",userFileName);
            if (!readUserFromFile(&user, userFileName, A.allArtists, A.numOfArtist, &sR, fileChoice))
            {
                freeSystem(&sR,&pR,&A,&aManager,&user);

//                freeAlbumManager(&aManager);
//                freeSongRepository(&sR);
//                freePlayListsRepo(&pR);
//                freeArtistRepository(&A);
                return 0;
            }
            if (userSubMenu(&user, &sR, &pR, &aManager) == ERROR)
            {
                freeSystem(&sR,&pR,&A,&aManager,&user);
//                freeAlbumManager(&aManager);
//                freeSongRepository(&sR);
//                freePlayListsRepo(&pR);
//                freeArtistRepository(&A);
                return 0;
            }
            endProgram(&sR,&pR,&A,&aManager,&user);
            choice = 12;
            break;
        case 12:
            endProgram(&sR,&pR,&A,&aManager,&user);
            printf("Exiting program...\n");

            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 12);


//    writeAlbumManagerToFile(&aManager, "Albums.bin", FROM_BINARY_FILE);
//    saveArtistRepositoryToFile(&A, "ComperssArtistRepo.bin", FROM_BINARY_FILE);
//    writeUserToFile(&user, "dosent matter right now", FROM_BINARY_FILE);
//    savePlayListRepositoryToFile(&pR, "PlayList.bin", FROM_BINARY_FILE);
//    saveSongRepositoryToTextFile(&sR, "Songs.txt");
//    saveSongRepositoryToBFile(&sR, "Songs.bin");
//    freeAlbum(&album);
//    freeSongRepository(&sR);
//    freePlayListsRepo(&pR);
//    freeArtistRepository(&A);
//    freeUser(&user);
	return 0;
}






int userSubMenu(User* pUser, const SongRepository* pSongs, const PlayListRepository* pPlayLists,const AlbumManager* pAlbums) {
    int choice, playListChoice,albumChoice;
    do {
        printf(ANSI_COLOR_GREEN"\nUser Submenu\n"ANSI_COLOR_RESET);
        printf(ANSI_COLOR_YELLOW"Hello %s\n", pUser->userName);
        printf("1. Add a System Playlist to user\n"); // need work
        printf("2. Delete a playlist from user\n");
        printf("3. Create a new playlist\n");
        printf("4. Add a song to user playlist\n");
        printf("5. Delete a song from a user playlist\n");
        printf("6. Play a Playlist by order\n");
        printf("7. Shuffle a Playlist\n");
        printf("8. Add Album to User\n");
        printf("9. Delete an Album from User\n");
        printf("10. Print All Playlists\n");
        printf("11. Print All Albums\n");
        printf("12. Print All Data About User\n");
        printf("13. Sort A User PlayList\n");
        printf("14. Find A Song In A User PlayList\n");
        printf("15. Exit\n");
        printf("Enter your choice: "ANSI_COLOR_RESET);
        scanf("%d", &choice);

        // Implement functionality based on user choice
        switch (choice) {
        case 1:
            if(addPlayListToUserFromSystem(pUser, pPlayLists) == ERROR)
                return ERROR;
            break;
        case 2:
            if(deletePlayListFromUser(pUser) == ERROR)
                return ERROR;
            break;
        case 3:
            if(createPlayListToUser(pUser, pSongs) == ERROR)
                return ERROR;
            break;
        case 4:
            if(addSongToUserPlayList(pUser, pSongs) == ERROR)
                return ERROR;
            break;
        case 5:
            if(deleteSongFromUserPlayList(pUser) == ERROR)
                return ERROR;
            break;
        case 6:
            if(playByOrderPlayList(pUser) == ERROR)
                return ERROR;
            break;
        case 7:
            if(ShufflePlayList(pUser) == ERROR)
                return ERROR;
            break;
        case 8:
            if(addAlbumstoUser(pUser, pAlbums) == ERROR)
                return ERROR;
            break;
        case 9:
            if(deleteAlbumFromUser(pUser) == ERROR)
                return ERROR;
            break;
        case 10:
            printPlayListForUser(pUser);
            break;
        case 11:
            printAlbumsForUser(pUser);
            break;
        case 12:
            printUser(pUser);
            break;
        case 13:
            sortPlayListForUser(pUser);
            break;
        case 14:
            findSongInSortedPlayListForUser(pUser);
            break;
        case 15:
            printf("Exiting...\n");
            return 1;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 15);
    return 1;
}



int initSystemFromFile(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum, int typeFile)
{
    if (typeFile == FROM_BINARY_FILE)
    {/////// need to call to end program function
        if (!initArtistRepositoryFromFile(pArtists, ARTIST_REPO_FROM_BIN, FROM_BINARY_FILE))
            return 0;
        if (!loadSongsRepositoryFromBFile(pSong, SONGS_REPO_FROM_BIN, pArtists->allArtists, pArtists->numOfArtist))
            return 0;
        if (!loadPlayListRepositoryFromFile(pPlayList, PLAYLIST_REPO_FROM_BIN, pSong, FROM_BINARY_FILE))
            return 0;
        if(!readAlbumManagerFromFile(pAlbum,"Albums.bin",pArtists->allArtists,pArtists->numOfArtist,pSong,FROM_BINARY_FILE))
            return 0;
    }
    else
    {/////// need to call to end program function
        if (!initArtistRepositoryFromFile(pArtists, ARTIST_REPO_FROM_TEXT, FROM_TEXT_FILE))
            return 0;
        if (!loadSongsRepositoryFromTextFile(pSong, SONGS_REPO_FROM_TEXT, pArtists->allArtists, pArtists->numOfArtist))
            return 0;
        if (!loadPlayListRepositoryFromFile(pPlayList, PLAYLIST_REPO_FROM_TEXT, pSong, FROM_TEXT_FILE))
            return 0;
        if(!readAlbumManagerFromFile(pAlbum, "Albums.txt", pArtists->allArtists,  pArtists->numOfArtist, pSong, FROM_TEXT_FILE))
            return 0;
    }
    return 1;
}


int saveSystemFiles(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum,User* pUser)
{

    if(!saveArtistRepositoryToFile(pArtists, ARTIST_REPO_FROM_BIN, FROM_BINARY_FILE))
        return 0;
    if(! saveArtistRepositoryToFile(pArtists, ARTIST_REPO_FROM_TEXT, FROM_TEXT_FILE))
        return 0;

    if(!saveSongRepositoryToBFile(pSong,SONGS_REPO_FROM_BIN))
        return 0;
    if(!saveSongRepositoryToTextFile(pSong,SONGS_REPO_FROM_TEXT))
        return 0;

    if(!savePlayListRepositoryToFile(pPlayList,PLAYLIST_REPO_FROM_BIN,FROM_BINARY_FILE))
        return 0;
    if(!savePlayListRepositoryToFile(pPlayList,PLAYLIST_REPO_FROM_TEXT,FROM_TEXT_FILE))
        return 0;

    if(!writeAlbumManagerToFile(pAlbum,ALBUM_MANAGER_FROM_BIN,FROM_BINARY_FILE))
        return 0;
    if(!writeAlbumManagerToFile(pAlbum,ALBUM_MANAGER_FROM_TEXT,FROM_TEXT_FILE))
        return 0;

    if (pUser->userName && pUser->userAlbums)
    {
        if (!writeUserToFile(pUser,USER_MANAGER_FROM_BIN,FROM_BINARY_FILE))
            return 0;
        if(!writeUserToFile(pUser,USER_MANAGER_FROM_TEXT,FROM_TEXT_FILE))
            return 0;
    }




    return 1;
}

void endProgram(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum,User* pUser)
{

    printf("So you want to save before exit program?\n"ANSI_COLOR_GREEN "1) YES\n"ANSI_COLOR_RESET ANSI_COLOR_RED "2) NO\n"ANSI_COLOR_RESET);
        int saveOp;
        scanf("%d",&saveOp);
    if (saveOp == 1)
    {
      if(!saveSystemFiles( pSong,  pPlayList,  pArtists,pAlbum,pUser))
          printf("Failed to save the files\n");
        saveOp = 2;

    }
    freeSystem( pSong,  pPlayList,  pArtists,pAlbum,pUser);
//        freeAlbumManager(pAlbum);
//        freeSongRepository(pSong);
//        freePlayListsRepo(pPlayList);
//        freeArtistRepository(pArtists);
//        freeUser(pUser);
}


void freeSystem(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum,User* pUser)
{

    freeAlbumManager(pAlbum);
    freeSongRepository(pSong);
    freePlayListsRepo(pPlayList);
    freeArtistRepository(pArtists);
    freeUser(pUser);

}