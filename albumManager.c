#include <stdlib.h>
#include "albumManager.h"
#include "fileHelper.h"
#include "macros.h"



int addAlbumToManager(AlbumManager* pAblumManager,const ArtistRepository* pArtistRepo)
{
    if (pArtistRepo->numOfArtist < 1)
    {
        printf(ANSI_COLOR_RED"Not Enough Artists.\n"ANSI_COLOR_RESET);
        return 0;
    }

    int artistChoice;
    do {
        printf("Enter Artist For Album 1 - %d\n",pArtistRepo->numOfArtist);
        showArtistRepository(pArtistRepo);
        printf(ANSI_COLOR_RED"To return menu Press 0\n"ANSI_COLOR_RESET);
        scanf("%d",&artistChoice);
    }while(artistChoice < 0 || artistChoice>pArtistRepo->numOfArtist);
    if (artistChoice == 0)
        return RETURN_MENU;
    pAblumManager->allAlbums = (Album*) realloc(pAblumManager->allAlbums,sizeof(Album)*(pAblumManager->numOfAlbums+ 1));
    CHECK_RETURN_0(pAblumManager->allAlbums)
    if(!initAlbum(&pAblumManager->allAlbums[pAblumManager->numOfAlbums++],&pArtistRepo->allArtists[artistChoice-1]))
        return ERROR;
    else
        printf(ANSI_COLOR_GREEN"Album Added\n"ANSI_COLOR_RESET);
    return 1;
 }
int addSongToAlbumManager(AlbumManager* pAlbumManager,const SongRepository* pSongs)
{
    if (pAlbumManager->numOfAlbums < 1)
    {
        printf(ANSI_COLOR_RED"Not Enough Albums.\n"ANSI_COLOR_RESET);
        return NOT_ENOUGH;
    }
    if (pSongs->numSongs < 1)
    {
        printf(ANSI_COLOR_RED"Not Enough Songs\n"ANSI_COLOR_RESET);
        return NOT_ENOUGH;
    }
    printf("Enter Album Index To Add a Song to\n");
    for (int i = 0; i < pAlbumManager->numOfAlbums; ++i) {
        printf("%d."ANSI_COLOR_BLUE"%s\n"ANSI_COLOR_RESET,i+1,pAlbumManager->allAlbums[i].albumName);
    }
    int albumChoice,songChoice;
    do {
        scanf("%d",&albumChoice);
    }while(albumChoice<0 || albumChoice>pAlbumManager->numOfAlbums);
    albumChoice--;
    printf("Enter Song Index To Be Added To Album\n");
    printAllSongs(pSongs);
    do {
        scanf("%d",&songChoice);
    }while(songChoice<0 || songChoice>pSongs->numSongs);
    songChoice--;
    int flag = addSongToAlbum(&pAlbumManager->allAlbums[albumChoice], &pSongs->songsArr[songChoice], 0);
    if (flag != 4 && flag != DUPLICATE)
        printf(ANSI_COLOR_GREEN"Song Added\n"ANSI_COLOR_RESET);
    return 1;
}










int writeAlbumManagerToTextFile(const AlbumManager* pAlbum, FILE* fp)
{
	CHECK_RETURN_0(pAlbum)
    fprintf(fp,"%d\n",pAlbum->numOfAlbums);
    for (int i = 0; i < pAlbum->numOfAlbums; i++) {
        if(!writeAlbumToTextFileWithOpenFile(&pAlbum->allAlbums[i],fp))
            return 0;
    }
    return 1;
}
int writeAlbumManagerToBFile(const AlbumManager* pAlbum, FILE* fp)
{
    CHECK_RETURN_0(pAlbum)
    if(!writeIntToFile(pAlbum->numOfAlbums,fp,"Error Writing Number Of Albums"))
        return 0;
    for (int i = 0; i < pAlbum->numOfAlbums; i++) {
        if(!writeAlbumToBFileWithOpenFile(&pAlbum->allAlbums[i],fp))
            return 0;
    }
    return 1;
}
int readAlbumManagerFromTextFIle(AlbumManager* pAlbum, FILE* fp, Artist* artists, int size, const SongRepository* pSongs)
{
    CHECK_RETURN_0(pAlbum)
    if(fscanf(fp,"%d",&pAlbum->numOfAlbums) != 1)
        return 0;
    pAlbum->allAlbums = (Album*) malloc(sizeof(Album)*pAlbum->numOfAlbums);
    CHECK_RETURN_0(pAlbum->allAlbums)
    for (int i = 0; i < pAlbum->numOfAlbums; i++)
        {
            L_init(&pAlbum->allAlbums[i].songs);
        }
    for (int i = 0; i < pAlbum->numOfAlbums; ++i) {
        if(!readAlbumFromTextFileWithOpenFile(&pAlbum->allAlbums[i],fp,artists,size,pSongs)) {
            for (int j = 0; j < i; j++) {
                freeAlbum(&pAlbum->allAlbums[j]);
            }
            free(pAlbum->allAlbums);
            return 0;
        }
    }
    return 1;
}
int readAlbumManagerFromBFIle(AlbumManager* pAlbum, FILE* fp, Artist* artists, int size, const SongRepository* pSongs)
{
    if(!readIntFromFile(&pAlbum->numOfAlbums,fp,"Error Reading NumberOfAlbums"))
         return 0;
    pAlbum->allAlbums = (Album*) malloc(sizeof(Album)*pAlbum->numOfAlbums);
    CHECK_RETURN_0(pAlbum->allAlbums)
        for (int i = 0; i < pAlbum->numOfAlbums; i++)
        {
            L_init(&pAlbum->allAlbums[i].songs);
        }
    for (int i = 0; i < pAlbum->numOfAlbums; ++i) {
        if(!readAlbumFromBFileWithOpenFile(&pAlbum->allAlbums[i],fp,artists,size,pSongs)) {
            for (int j = 0; j < i; j++) {
                freeAlbum(&pAlbum->allAlbums[j]);
            }
            free(pAlbum->allAlbums);
            return 0;
        }
    }
    return 1;
}


int writeAlbumManagerToFile(const AlbumManager* pAlbum, const char* fileName, int typeFile)
{
    if (typeFile == FROM_BINARY_FILE)
    {
        FILE* fp;
        fp = fopen(fileName, "wb");
        CHECK_RETURN_0(fp)
            if (!writeAlbumManagerToBFile(pAlbum, fp))
            {
                fclose(fp);
                return 0;
            }
        fclose(fp);
        return 1;
    }
    else
    {
        FILE* fp;
        fp = fopen(fileName, "w");
        CHECK_RETURN_0(fp)
            if (!writeAlbumManagerToTextFile(pAlbum, fp))
            {
                fclose(fp);
                return 0;
            }
        fclose(fp);
        return 1;
    }
    return 0;
}
int readAlbumManagerFromFile(AlbumManager* pAlbum, const char* fileName, Artist* artists, int size, const SongRepository* pSongs, int typeFile) {
    if (typeFile == FROM_BINARY_FILE)
    {
        FILE* fp;
        fp = fopen(fileName, "rb");
        CHECK_RETURN_0(fp)
        if (!readAlbumManagerFromBFIle(pAlbum, fp,artists,size,pSongs))
        {
            fclose(fp);
            return 0;
        }
        fclose(fp);
        return 1;
    }
    else
    {
        FILE* fp;
        fp = fopen(fileName, "r");
        CHECK_RETURN_0(fp)
        if (!readAlbumManagerFromTextFIle(pAlbum, fp,artists,size,pSongs))
        {
            fclose(fp);
            return 0;
        }
        fclose(fp);
        return 1;
    }
    return 0;
}


void printAlbumManager(const AlbumManager* pAlbumManager){
    if (pAlbumManager->numOfAlbums < 1)
    {
        printf("Album Manager , Has no songs.\n");
        return;
    }
    for (int i = 0; i < pAlbumManager->numOfAlbums; i++) {
        printAlbum(&pAlbumManager->allAlbums[i]);
    }
}
void freeAlbumManager(AlbumManager* pAlbumManager)
{
    CHECK_RETURN(pAlbumManager->allAlbums); // if not initialize don't free
    for (int i = 0; i < pAlbumManager->numOfAlbums; i++) {
        freeAlbum(&pAlbumManager->allAlbums[i]);
    }
    free(pAlbumManager->allAlbums);
}