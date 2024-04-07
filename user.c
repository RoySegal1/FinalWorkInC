//
// Created by User on 02/04/2024.
//
#include <stdlib.h>
#include "user.h"
#include "macros.h"
#include "General.h"
#include "fileHelper.h"
#include "string.h"


void initUser(User* pUser)
{
    pUser->numOfAlbums=0;
    pUser->numOfPlaylists = 0;
    pUser->userName = getStrExactName("Enter User Name");
    pUser->userAlbums = NULL;
    pUser->userPlayLists = NULL;
}

int ShufflePlayList(const User* pUser)
{
    if (pUser->numOfPlaylists < 1)
    {
        printf("No Enough PlayLists\n");
        return NOT_ENOUGH;
    }
    printf("Enter Number Of PlayList To Be Played. From 1 - %d\n", pUser->numOfPlaylists);
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        printf("%d."ANSI_COLOR_BLUE"%s"ANSI_COLOR_RESET"\n", i + 1, pUser->userPlayLists[i].playlistName);
    }
    int choice,songChoice,songsRemaning;
    do {
        scanf("%d", &choice);
    } while (choice<0 || choice>pUser->numOfPlaylists);
    int allSongs = pUser->userPlayLists[choice - 1].numOfSongs;
    songsRemaning = allSongs;
    int* arrayHelper = (int*)calloc(allSongs, sizeof(int));
    CHECK_RETURN_0(arrayHelper)
    while(songsRemaning >0) {
        songChoice = MIN_SONGS + (rand() % (allSongs - MIN_SONGS + 1));
        if (arrayHelper[songChoice] == 0)
        {
            if (!playSong(pUser->userPlayLists[choice - 1].allSongs[songChoice]))
                return ERROR;
            printf("Press Enter To Play Next Song\n");
            getchar();
            arrayHelper[songChoice] = 1;
            songsRemaning--;
        }
    }
    free(arrayHelper);
    return 1;
}




int hasPlayList(User* pUser, PlayList* pPlay)
{
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        if(!strcmp(pUser->userPlayLists[i].playlistName,pPlay->playlistName))
        {
            if(pUser->userPlayLists[i].typeOfPlayList == eSystem)
                return 1;
        }
    }
    return 0;
}

int hasAlbum(User* pUser, Album* pAlbum)
{
    for (int i = 0; i < pUser->numOfAlbums; i++)
    {
        if (!strcmp(pUser->userAlbums[i].albumName, pAlbum->albumName))
        {
            if (!strcmp(pUser->userAlbums[i].artist.name, pAlbum->artist.name))
                return 1;
        }
    }
    return 0;
}




int playByOrderPlayList(const User* pUser)
{
    if (pUser->numOfPlaylists < 1)
    {
        printf("No Enough PlayLists\n");
        return NOT_ENOUGH;
    }
    printf("Enter Number Of PlayList To Be Played. From 1 - %d\n",pUser->numOfPlaylists);
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        printf("%d."ANSI_COLOR_BLUE"%s"ANSI_COLOR_RESET"\n",i+1,pUser->userPlayLists[i].playlistName);
    }
    int choice;
    do{
        scanf("%d",&choice);
    }
    while(choice<0 || choice>pUser->numOfPlaylists);
    for (int i = 0; i < pUser->userPlayLists[choice-1].numOfSongs; ++i) {
        if (!playSong(pUser->userPlayLists[choice - 1].allSongs[i]))
            return ERROR;
        printf("Press Enter To Play Next Song\n");
        getchar();
    }
    return 1;
}

int addSongToUserPlayList(User* pUser,const SongRepository* pSongs)
{
    if (pUser->numOfPlaylists < 1)
    {
        printf(ANSI_COLOR_RED"No Enough PlayLists\n"ANSI_COLOR_RESET);
        return NOT_ENOUGH;
    }
    if (pSongs->numSongs < 1)
    {
        printf(ANSI_COLOR_RED"Not Enough Songs.\n"ANSI_COLOR_RESET);
        return NOT_ENOUGH;
    }
    printf("Enter Index Of Playlist To add a Song to from 1 - %d\n",pUser->numOfPlaylists);
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        printf("%d."ANSI_COLOR_BLUE"%s"ANSI_COLOR_RESET"\n",i+1,pUser->userPlayLists[i].playlistName);
    }
    int choicePlayList,choiceSong;
    do{
        scanf("%d",&choicePlayList);
    }
    while(choicePlayList<0 || choicePlayList>pUser->numOfPlaylists);
    choicePlayList--;
    if(pUser->userPlayLists[choicePlayList].typeOfPlayList == eSystem)
    {
        printf("Cant add songs to a system Playlist.\n");
        return 1;
    }
    else
    {
        printf("Enter number of song to be added , 1-%d\n",pSongs->numSongs);
        printAllSongs(pSongs);
        do{
            scanf("%d",&choiceSong);
        }
        while(choiceSong<0 || choiceSong>pSongs->numSongs);
        choiceSong--;
        if(!addSongToPlayList(&pUser->userPlayLists[choicePlayList],&pSongs->songsArr[choiceSong]))
            return ERROR;
        return 1;
    }
}

int createPlayListToUser(User* pUser, const SongRepository* pSongs)
{
    if (pSongs->numSongs < 1)
    {
        printf(ANSI_COLOR_RED"Not Enough Songs.\n"ANSI_COLOR_RESET);
        return NOT_ENOUGH;
    }
    pUser->userPlayLists = (PlayList*)realloc(pUser->userPlayLists,(pUser->numOfPlaylists+1)*sizeof(PlayList));
    CHECK_RETURN_0(pUser->userPlayLists)
    initPlayListForUser(&pUser->userPlayLists[pUser->numOfPlaylists]);
    printAllSongs(pSongs);
    int choice,cont = 0,addFlag;
    while(!cont) {
        do {
            printf("Enter Number Of Song To Add From 1-%d\n", pSongs->numSongs);
            scanf("%d", &choice);
        } while (choice < 1 || choice > pSongs->numSongs);
     addFlag = addSongToPlayList(&pUser->userPlayLists[pUser->numOfPlaylists],&pSongs->songsArr[choice-1]);
     if(addFlag == 0)
     {
         printf("error\n");
         return ERROR;
     }
     if(addFlag == 1)
         printf("Song added\n");
     printf("Do you want to add more songs to playlist? 0 for yes any other number of no\n");
     scanf("%d",&cont);
    }
    pUser->numOfPlaylists++;
    return 1;
}

int deleteSongFromUserPlayList(User* pUser)
{
    if (pUser->numOfPlaylists < 1)
    {
        printf("No Enough PlayLists\n");
        return NOT_ENOUGH;
    }
    printf("Enter Index Of Playlist To Remove a Song to from 1 - %d\n", pUser->numOfPlaylists);
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        printf("%d."ANSI_COLOR_BLUE"%s"ANSI_COLOR_RESET"\n", i + 1, pUser->userPlayLists[i].playlistName);
    }
    int choicePlayList;
    do {
        scanf("%d", &choicePlayList);
    } while (choicePlayList<0 || choicePlayList>pUser->numOfPlaylists);
    choicePlayList--;
    if (pUser->userPlayLists[choicePlayList].typeOfPlayList == eUser)
    {
        if (!removeSongFromPlayList(&pUser->userPlayLists[choicePlayList]))
            return ERROR;
    }
    else
        {
            printf("Cant Delete Songs From System PlayList\n");
            return 1;
        }
    //return 1;
}

int addPlayListToUserFromSystem(User* pUser, PlayListRepository* pPlayLists)
{
    int playListChoice;
    if (pPlayLists->numOfPlayList < 1)
    {
        printf("Not Enough PlayList in System\n");
        return NOT_ENOUGH;
    }
    printf("Enter Index Of PlayList To Be Added 1 - %d\n", pPlayLists->numOfPlayList);
    printPlayLists(pPlayLists);
    do {
        scanf("%d", &playListChoice);
    } while (playListChoice<0 || playListChoice>pPlayLists->numOfPlayList);
    if (addPlayListToUser(pUser, &pPlayLists->systemPlaylists[playListChoice - 1]) == ERROR)
        return ERROR;
    return 1;
}
int addAlbumstoUser(User* pUser, AlbumManager* pAlbums)
{
    int albumChoice;
    if (pAlbums->numOfAlbums < 1)
    {
        printf("Not Enough albums.\n");
        return NOT_ENOUGH;
    }
    printf("Enter Index Of Album To Add 1 - %d\n", pAlbums->numOfAlbums);
    printAlbumManager(pAlbums);
    do {
        scanf("%d", &albumChoice);
    } while (albumChoice < 0 || albumChoice < pAlbums->numOfAlbums);
    if (addAlbumToUser(pUser, &pAlbums->allAlbums[albumChoice - 1]) == ERROR)
        return ERROR;
}

int addPlayListToUser(User* pUser, PlayList* pPlay)
{
    if(hasPlayList(pUser,pPlay))
    {
        printf(ANSI_COLOR_RED"Cant Add Same PlayList.\n"ANSI_COLOR_RESET);
        return DUPLICATE;
    }
    CHECK_RETURN_0(pPlay) // maby change
    pUser->userPlayLists = (PlayList*)realloc(pUser->userPlayLists,(pUser->numOfPlaylists+1)*sizeof(PlayList));
    CHECK_RETURN_0(pUser->userPlayLists)
    pUser->userPlayLists[pUser->numOfPlaylists] = *pPlay; // maybe not shallow
    pUser->numOfPlaylists++;
    return 1;
}

int deletePlayListFromUser(User* pUser) // maybe need to free it
{
    if (pUser->numOfPlaylists < 1)
    {
        printf("No Enough PlayLists\n");
        return NOT_ENOUGH;
    }
    printf("Enter Number Of PlayList To Be Deleted. From 1 - %d\n",pUser->numOfPlaylists);
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        printf("%d."ANSI_COLOR_BLUE"%s"ANSI_COLOR_RESET"\n",i+1,pUser->userPlayLists[i].playlistName);
    }
    int choice;
    do{
        scanf("%d",&choice);
    }
    while(choice<0 || choice>pUser->numOfPlaylists);
    if (pUser->userPlayLists[choice - 1].typeOfPlayList == eUser)
        freePlayList(&pUser->userPlayLists[choice - 1]);
    pUser->userPlayLists[choice-1] = pUser->userPlayLists[pUser->numOfPlaylists-1];
    pUser->userPlayLists = (PlayList*)realloc(pUser->userPlayLists,(pUser->numOfPlaylists-1)*sizeof(PlayList));
    pUser->numOfPlaylists--;
    if(pUser->numOfPlaylists>0)
        CHECK_RETURN_0_PRINT(pUser->userPlayLists,ALOC_ERROR)
    return 1;
}
int deleteAlbumFromUser(User* pUser) //maybe need to free it
{
    if (pUser->numOfAlbums < 1)
    {
        printf("Not Enough Albums\n");
        return NOT_ENOUGH;
    }
    printf("Enter Number Of Album To Be Deleted. From 1 - %d\n",pUser->numOfAlbums);
    for (int i = 0; i < pUser->numOfAlbums; i++)
    {
        printf("%d."ANSI_COLOR_BLUE"%s"ANSI_COLOR_RESET"\n",i+1,pUser->userAlbums[i].albumName);
    }
    int choice;
    do{
        scanf("%d",&choice);
    }
    while(choice<0 || choice>pUser->numOfAlbums); 
    pUser->userAlbums[choice-1] = pUser->userAlbums[pUser->numOfAlbums-1];
    freeAlbum(&pUser->userAlbums[choice - 1]);
    pUser->userAlbums = (Album*)realloc(pUser->userAlbums,(pUser->numOfAlbums-1)*sizeof(Album));
    pUser->numOfAlbums--;
    if(pUser->numOfAlbums>0)
        CHECK_RETURN_0_PRINT(pUser->userAlbums,ALOC_ERROR)
    return 1;
}

int addAlbumToUser(User* pUser, Album* pAlbums)
{
    if (hasAlbum(pUser, pAlbums))
    {
        printf(ANSI_COLOR_RED"Cant Add Same Album\n"ANSI_COLOR_RESET);
        return DUPLICATE;
    }
    CHECK_RETURN_0(pAlbums)
    pUser->userAlbums = (Album *)realloc(pUser->userAlbums,(pUser->numOfAlbums+1)*sizeof(Album));
    CHECK_RETURN_0(pUser->userAlbums)

   if(!L_init(&pUser->userAlbums[pUser->numOfAlbums].songs))
       return ERROR;
    pUser->userAlbums[pUser->numOfAlbums].albumName = getDynStr(pAlbums->albumName);
    pUser->userAlbums[pUser->numOfAlbums].artist = pAlbums->artist;
    pUser->userAlbums[pUser->numOfAlbums].numOfSongs = 0;
    NODE* tmp;
    Song* songTmp;
    tmp = pAlbums->songs.head.next;
        while (tmp != NULL) // go over the albums songs
        {
            songTmp = tmp->key;
            addSongToAlbum(&pUser->userAlbums[pUser->numOfAlbums], songTmp, 0);
            tmp = tmp->next;
        }
   // pUser->userAlbums[pUser->numOfAlbums] = *pAlbums; // maybe not shallow
    pUser->numOfAlbums++;
    return 1;
}

void sortPlayListForUser(const User* pUser)
{
    int playListChoice;
    if (pUser->numOfPlaylists < 1)
    {
        printf("Not Enough PlayLists\n");
        return;
    }
    printf("Enter Index Of PlayList To Be Sorted 1 - %d\n", pUser->numOfPlaylists);
    printPlayListForUser(pUser);
    do {
        scanf("%d", &playListChoice);
    } while (playListChoice < 0 || playListChoice > pUser->numOfPlaylists);
    if (pUser->userPlayLists[playListChoice - 1].typeOfPlayList == eUser)
        sortPlayList(&pUser->userPlayLists[playListChoice - 1]);
    else
        printf(ANSI_COLOR_RED"Cant Sort System PlayList.\n"ANSI_COLOR_RESET);
}
void findSongInSortedPlayListForUser(const User* pUser)
{
    int playListChoice;
    if (pUser->numOfPlaylists < 1)
    {
        printf("Not Enough PlayLists\n");
        return;
    }
    printf("Enter Index Of PlayList To Find Song In 1 - %d\n", pUser->numOfPlaylists);
    printPlayListForUser(pUser);
    do {
        scanf("%d", &playListChoice);
    } while (playListChoice < 0 || playListChoice > pUser->numOfPlaylists);
    if (pUser->userPlayLists[playListChoice - 1].typeOfPlayList == eUser)
        findSong(&pUser->userPlayLists[playListChoice - 1]);
    else
        printf(ANSI_COLOR_RED"Cant Sort System PlayList.\n"ANSI_COLOR_RESET);
}



void printUser(const User* pUser)
{
    printf(ANSI_COLOR_GREEN"User Name: %s Has %d PlayLists, %d Albums\n", pUser->userName, pUser->numOfPlaylists, pUser->numOfAlbums);
    printf(ANSI_COLOR_RESET);
    printPlayListForUser(pUser);
    printAlbumsForUser(pUser);
}


void printPlayListForUser(const User* pUser)
{
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        printPlayList(&pUser->userPlayLists[i]);
    }
}

void printAlbumsForUser(const User* pUser)
{
    for (int i = 0; i < pUser->numOfAlbums; i++)
    {
        printAlbum(&pUser->userAlbums[i]);
    }
}

void freeUser(User* pUser)
{
    if(pUser->numOfAlbums)
    freeUserAlbums(pUser->userAlbums,pUser->numOfAlbums);
    if (pUser->userPlayLists)
    freeUserPlayLists(pUser->userPlayLists,pUser->numOfPlaylists);
    if (pUser->userName)
    free(pUser->userName);
}

void freeUserAlbums(Album* albums,int size)
{
    for (int i = 0; i < size; i++)
    {
        freeAlbum(&albums[i]);
    }
    free(albums);
}

void freeUserPlayLists(PlayList* pPlay,int size)
{
    for (int i = 0; i < size; i++)
    {
        if(pPlay[i].typeOfPlayList == eUser) // if it's the system she supposes to free it.
            freePlayList(&pPlay[i]);
    }
    free(pPlay);
}

int createPlayListArr(User* pUser)
{
    if (pUser->numOfPlaylists > 0)
    {
        pUser->userPlayLists = (PlayList*)malloc(pUser->numOfPlaylists * sizeof(PlayList));
        CHECK_RETURN_0_PRINT(pUser->userPlayLists,ALOC_ERROR)
            return 1;
    }
    else
    {
        pUser->userPlayLists = NULL;
        return 1;
    }
    return 0;

}
int createAlbumArr(User* pUser)
{
    if (pUser->numOfAlbums > 0)
    {
        pUser->userAlbums = (Album*)malloc(pUser->numOfAlbums * sizeof(Album));
        CHECK_RETURN_0_PRINT(pUser->userAlbums, ALOC_ERROR)
            for (int i = 0; i < pUser->numOfAlbums; i++)
            {
                L_init(&pUser->userAlbums[i].songs);
            }
            return 1;
    }
    else
    {
        pUser->userAlbums = NULL;
        return 1;
    }
    return 0;
}

int writeUserToTextFile(const User* pUser, const char* fileName)
{
    CHECK_RETURN_0(pUser->userName)
    FILE* fp;
    char temp[MAX_STR_LEN];
    strcpy(temp, pUser->userName);
    strcat(temp, ".txt");
    if (temp == NULL)
        return 0;
    fp = fopen(temp,"w");
    CHECK_RETURN_0(fp)
    fprintf(fp,"%s\n",pUser->userName);
    int numberOfUserPlaylist = numberOfUserPlayList(pUser);
    fprintf(fp,"%d\n", numberOfUserPlaylist); // need change
    for (int i = 0; i < pUser->numOfPlaylists; ++i) {
        if (pUser->userPlayLists[i].typeOfPlayList == eUser)
        {
            if (!writePlayListToTextFile(&pUser->userPlayLists[i], fp)) // need change
                return 0;
        }
    }
    fprintf(fp,"%d\n",pUser->numOfAlbums);
    for (int i = 0; i < pUser->numOfAlbums; ++i) {
        if(!writeAlbumToTextFileWithOpenFile(&pUser->userAlbums[i],fp))
            return 0;
    }
    fclose(fp);
    return 1;
}
int readUserFromTextFile(User* pUser, const char* fileName, Artist* artists, int size,const SongRepository* pSongs)
{
    FILE* fp;
    fp = fopen(fileName,"r");
    CHECK_RETURN_0(fp)
    char temp[MAX_STR_LEN];
    myGets(temp,MAX_STR_LEN, fp);
    pUser->userName = getDynStr(temp);
    CHECK_RETURN_0(pUser->userName)
    if(fscanf(fp,"%d",&pUser->numOfPlaylists) != 1)
    {
        free(pUser->userName);
        return 0;
    }
    if (!createPlayListArr(pUser))
    {
        free(pUser->userName);
        return 0;
    }
    for (int i = 0; i < pUser->numOfPlaylists; i++) {
        if(!readPlayListFromTextFile(&pUser->userPlayLists[i],fp,pSongs))
        {
            freeUserPlayLists(pUser->userPlayLists,i);
            free(pUser->userName);
            return 0;
        }
    }
    if(fscanf(fp,"%d",&pUser->numOfAlbums) != 1)
    {
        freeUserPlayLists(pUser->userPlayLists,pUser->numOfPlaylists);
        free(pUser->userName);
        return 0;
    }
    if (!createAlbumArr(pUser))
    {
        freeUserPlayLists(pUser->userPlayLists, pUser->numOfPlaylists);
        free(pUser->userName);
        return 0;
    }
    for (int i = 0; i < pUser->numOfAlbums; i++) {
        if(!readAlbumFromTextFileWithOpenFile(&pUser->userAlbums[i],fp,artists,size,pSongs))
        {
            freeUserPlayLists(pUser->userPlayLists,pUser->numOfPlaylists);
            freeUserAlbums(pUser->userAlbums,i);
            free(pUser->userName);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}
int writeUserToBFile(const User* pUser, const char* fileName) /// maybe take out fileName in all Write functions
{
    CHECK_RETURN_0(pUser->userName)
    FILE* fp;
    char temp[MAX_STR_LEN];
    strcpy(temp, pUser->userName);
    strcat(temp, ".bin");
    if (temp == NULL)
        return 0;
    fp = fopen(temp,"wb");
    CHECK_RETURN_0_PRINT(fp, "Error Opening File")
        if (!writeStringToFile(pUser->userName, fp, "Error Writing User name"))
            RETURN_0_CLOSE_FILE(fp)
    int numberOfUserPlaylist = numberOfUserPlayList(pUser);
    if(!writeIntToFile(numberOfUserPlaylist,fp,"Error Writing User Number Of PlayLists")) // need change
    RETURN_0_CLOSE_FILE(fp)
    for (int i = 0; i < pUser->numOfPlaylists; i++) {
        if (pUser->userPlayLists[i].typeOfPlayList == eUser)
        {
            if (!writePlayListToBFile(&pUser->userPlayLists[i], fp)) // need change
                RETURN_0_CLOSE_FILE(fp)
        }
    }
    if(!writeIntToFile(pUser->numOfAlbums,fp,"Error Writing User Number Of Albums)"))
        RETURN_0_CLOSE_FILE(fp)
    for (int i = 0; i < pUser->numOfAlbums; i++) {
        if(!writeAlbumToBFileWithOpenFile(&pUser->userAlbums[i],fp))
            RETURN_0_CLOSE_FILE(fp)
    }
    fclose(fp);
    return 1;
}
int readUserFromBFile(User* pUser, const char* fileName, Artist* artists, int size, const SongRepository* pSongs)
{
    FILE* fp;
    fp = fopen(fileName, "rb");
    CHECK_RETURN_0_PRINT(fp,"Error Opening File")
    pUser->userName = readStringFromFile(fp,"Error Reading User Name");
    CHECK_RETURN_0_PRINT(pUser->userName,"Error Reading User Name")
    if(!readIntFromFile(&pUser->numOfPlaylists,fp,"Error Reading User Number Of PlayLists"))
    {
        free(pUser->userName);
        return 0;
    }
    if(!createPlayListArr(pUser))
    {
        free(pUser->userName);
        return 0;
    }
    for (int i = 0; i < pUser->numOfPlaylists; i++) {
        if(!readPlayListFromBFile(&pUser->userPlayLists[i],fp,pSongs))
        {
            freeUserPlayLists(pUser->userPlayLists,i);
            free(pUser->userName);
            return 0;
        }
    }
    if(!readIntFromFile(&pUser->numOfAlbums,fp,"Error Reading User Number Of Albums"))
    {
        freeUserPlayLists(pUser->userPlayLists,pUser->numOfPlaylists);
        free(pUser->userName);
        return 0;
    }
    if (!createAlbumArr(pUser)) {
        freeUserPlayLists(pUser->userPlayLists, pUser->numOfPlaylists);
        free(pUser->userName);
        return 0;
    }
    for (int i = 0; i < pUser->numOfAlbums; i++) {
        if(!readAlbumFromBFileWithOpenFile(&pUser->userAlbums[i],fp,artists,size,pSongs)) {
            freeUserPlayLists(pUser->userPlayLists, pUser->numOfPlaylists);
            freeUserAlbums(pUser->userAlbums, i);
            free(pUser->userName);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

int readUserFromFile(User* pUser, const char* fileName, Artist* artists, int size, const SongRepository* pSongs, int fileType)
{
    if (fileType == FROM_BINARY_FILE)
    {
        if (!readUserFromBFile(pUser, fileName, artists, size, pSongs))
            return 0;
        return 1;
    }
    else
    {
        if (!readUserFromTextFile(pUser, fileName, artists, size, pSongs))
            return 0;
        return 1;
    }
    return 0;
}
int writeUserToFile(const User* pUser, const char* fileName, int fileType)
{
    CHECK_RETURN_0(pUser)
    if (fileType == FROM_BINARY_FILE)
    {
        if (!writeUserToBFile(pUser,fileName))
            return 0;
        return 1;
    }
    else
    {
        if (!writeUserToTextFile(pUser, fileName))
            return 0;
        return 1;
    }
    return 0;
}
int numberOfUserPlayList(const User* pUser)
{
    int count = 0;
    for (int i = 0; i < pUser->numOfPlaylists; i++)
    {
        if (pUser->userPlayLists[i].typeOfPlayList == eUser)
            count++;
    }
    return count;
}



