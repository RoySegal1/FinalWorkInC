#include <stdlib.h>
#include "albumManager.h"
#include "fileHelper.h"
#include "macros.h"



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
        return 1;
    }
    return 0;
}


void printAlbumManager(AlbumManager* pAlbumManager){
    for (int i = 0; i < pAlbumManager->numOfAlbums; i++) {
        printAlbum(&pAlbumManager->allAlbums[i]);
    }
}
void freeAlbumManager(AlbumManager* pAlbumManager)
{
    for (int i = 0; i < pAlbumManager->numOfAlbums; i++) {
        freeAlbum(&pAlbumManager->allAlbums[i]);
    }
    free(pAlbumManager->allAlbums);
}