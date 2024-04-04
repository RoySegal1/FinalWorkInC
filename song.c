#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "song.h"
#include "General.h"
#include "macros.h"
#include "fileHelper.h"
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL_audio.h>




void initSong(Song* pSong ,Artist* pArtist)
{
    pSong->songName = getStrExactName("Enter Song Name");
    getCode(pSong->songCode,codeHelper);
    codeHelper++;
    getLength(pSong);
    pSong->typeOfSong = genreMenu();
    pSong->amountPlayedSong = 0;
    pSong->artist = *pArtist;
}

void getCode(char code[5],int num)
{
    for (int i = 3; i >= 0; i--) {
        code[i]= num%10 + '0';
        num/=10;
    }
    code[4] = '\0';
}

void getLength(Song* pSong)
{
    int minutes,seconds;
    do{
        printf("Enter minutes\n");
        scanf("%d",&minutes);
    }
    while(minutes<0||minutes>60);
    pSong->minutes = minutes;
    do{
        printf("Enter seconds\n");
        scanf("%d",&seconds);
    }
    while(seconds<0||seconds>60);
    pSong->seconds = seconds;
}



int playSong(Song* pSong)
{

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        printf("SDL initialization error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_AudioSpec wavespec;
    Uint8* wavbuf = NULL;
    Uint32 wavelen = 0;
    char temp[9] = {0};
    strcpy(temp, pSong->songCode);
    strcat(temp, ".wav");
    printf(ANSI_COLOR_CYAN"Playing: %s Press Any Key To Stop The Music.\n"ANSI_COLOR_RESET, pSong->songName);
    if (SDL_LoadWAV(temp, &wavespec, &wavbuf, &wavelen) == NULL)
        printf(stderr, "DIDNT WORK %s\n", SDL_GetError);
    // Initialize SDL Mixer
    if (Mix_OpenAudio(0, &wavespec) == -1) {
        printf("SDL Mixer initialization error: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

    // Load audio files
    Mix_Chunk* audio1 = Mix_LoadWAV(temp);
    if (!audio1) {
        printf("Failed to load audio file: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }
    Mix_Volume(0, 50);

    // Play audio on different channels
    int channel1 = Mix_PlayChannel(-1, audio1, 0);
    if (channel1 == -1) {
        printf("Failed to play audio: %s\n", Mix_GetError());
        Mix_FreeChunk(audio1);
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Wait for audio to finish playing
   // while (Mix_Playing(channel1)) {
   //     SDL_Delay(100); // Adjust delay as needed
  //  }
   // SDL_Delay(time * 1000);
    int quit = 0;
    while (!quit) {
        if (_kbhit()) {  // Check if a key has been pressed
            getchar();   // Clear the key from the buffer
            quit = 1;    // Quit the loop if a key is pressed
            Mix_FreeChunk(audio1);
            Mix_CloseAudio();
            SDL_free(wavbuf);
            SDL_Quit();
            pSong->amountPlayedSong++;
        }
        SDL_Delay(100); // Adjust delay as needed
    }
    // Clean up


}


void printSong(const void* pSong)
{
    Song* tempSong = (Song*) pSong;
    showArtist(&tempSong->artist);
    printf("Song Name: %s\nSong Length: %d.%d minutes\nSong Listener's: %d\n",tempSong->songName,tempSong->minutes,tempSong->seconds,tempSong->amountPlayedSong);
    printf("Song Genre: %s\n",typeOfGenre[tempSong->typeOfSong]);
    printf("Song Code: %s\n",tempSong->songCode);
}
void printSongForAlbum(const void* pSong)
{
    Song* tempSong = (Song*)pSong;
    printf("Name: %s\nLength: %d.%d minutes\n", tempSong->songName, tempSong->minutes, tempSong->seconds);
}
void printSongForPlayList(const void* pSong)
{
    Song* tempSong = (Song*)pSong;
    printf("Name:""\x1b[34m""%s"ANSI_COLOR_RESET"- By %s\nLength: %d.%d minutes\n", tempSong->songName,tempSong->artist.name,tempSong->minutes, tempSong->seconds);
}


eGenreOptions genreMenu()
{
    int opt;
    printf("Genre Options:\n");
    do {
        for (int i = 1; i < eNumOfOptions; i++)
            printf("Enter %d for %s\n", i, typeOfGenre[i]);
        scanf("%d", &opt);
    } while (opt < 0 || opt >=eNumOfOptions);

    return (eGenreOptions)opt;
}


int isSongType(const Song* pSong,eGenreOptions genre)
{
    return pSong->typeOfSong == genre;
}
void freeSong(void* pSong)
{
    Song* temp = (Song*) pSong;
    free(temp->songName);
}

int compareByArtistName(const void* pSong1,const void* pSong2)
{
    Song* temp1 = *(Song**) pSong1;
    Song* temp2 = *(Song**) pSong2;
    return _stricmp(temp1->artist.name, temp2->artist.name);
}
int compareByName(const void* pSong1,const void* pSong2)
{
    Song* temp1 = *(Song**) pSong1;
    Song* temp2 = *(Song**) pSong2;
    return _stricmp(temp1->songName,temp2->songName);
}
int compareByAmountPlayed(const void* pSong1,const void* pSong2)
{
    Song* temp1 = *(Song**) pSong1;
    Song* temp2 = *(Song**) pSong2;
    return (temp1->amountPlayedSong-temp2->amountPlayedSong);
}
int compareByGenre(const void* pSong1,const void* pSong2)
{
    Song* temp1 = *(Song**) pSong1;
    Song* temp2 = *(Song**) pSong2;
    return (int)(temp1->typeOfSong-temp2->typeOfSong);
}
int compareSongByCode(const void* pSong1,const void* pSong2)
{
    Song* temp1 = (Song*) pSong1;
    Song* temp2 = (Song*) pSong2;
    return _stricmp(temp1->songCode,temp2->songCode);
}


int readSongFromBFile(Song* pSong,FILE* fp, Artist* artists, int size)
{
    //READ ARTIST
    char *temp;
    temp = readStringFromFile(fp, "Error Reading Artist Name");
    pSong->artist = *findArtistInArr(artists, size, temp);
    // GET Artist With Temp
    free(temp); //maby Change to new Function
    pSong->songName = readStringFromFile(fp,"Error Reading Song Name");
    if(pSong->songName == NULL)
        return 0;
    if(!readCharsFromFile(pSong->songCode, CODE_LENGTH,fp,"Error Reading Song Code"))
    {
        free(pSong->songName);
        return 0;
    }
    if(!readIntFromFile(&pSong->minutes,fp,"Error Reading Minutes"))
    {
        free(pSong->songName);
        return 0;
    }
    if(!readIntFromFile(&pSong->seconds,fp,"Error Reading Seconds"))
    {
        free(pSong->songName);
        return 0;
    }
    if(!readIntFromFile(&pSong->amountPlayedSong,fp,"Error Reading Amount Played"))
    {
        free(pSong->songName);
        return 0;
    }
    int temp1;
    if(!readIntFromFile(&temp1,fp,"Error Reading Type Of Song"))
    {
        free(pSong->songName);
        return 0;
    }
    pSong->typeOfSong = temp1;
    codeHelper++;
    return 1;
}
int writeSongToBFile(Song* pSong,FILE* fp)
{
    //WriteArtist
    if (!writeStringToFile(pSong->artist.name, fp, "Error Writing Artist Name"))
        return 0;
    if(!writeStringToFile(pSong->songName,fp,"Error Writing Song Name"))
        return 0;
    if(!writeCharsToFile(pSong->songCode, CODE_LENGTH,fp,"Error Writing Song Code"))
        return 0;
    if(!writeIntToFile(pSong->minutes,fp,"Error Writing Minutes"))
        return 0;
    if(!writeIntToFile(pSong->seconds,fp,"Error Writing Seconds"))
        return 0;
    if(!writeIntToFile(pSong->amountPlayedSong,fp,"Error Writing Amount Played"))
        return 0;
    if(!writeIntToFile(pSong->typeOfSong,fp,"Error Writing Type of song"))
        return 0;
    return 1;
}
int readSongFromTextFile(Song* pSong, FILE* fp,Artist* artists,int size)
{
    char temp[MAX_STR_LEN];
    if (!pSong)
        return 0;
    //Artist
    myGets(temp, MAX_STR_LEN, fp);
    if(findArtistInArr(artists,size, temp) == NULL)
        return 0;
    pSong->artist = *findArtistInArr(artists,size, temp);
    myGets(temp, MAX_STR_LEN, fp);
    pSong->songName = getDynStr(temp);
    myGets(pSong->songCode, MAX_STR_LEN, fp); // maby Not MAX_STR and USING 5 instad
    if (4 != fscanf(fp, "%d,%d,%d,%d", &pSong->minutes, &pSong->seconds, &pSong->amountPlayedSong, &pSong->typeOfSong)) {
        free(pSong->songName);
        return 0;
    }
    codeHelper++;
    return 1;

}
int writeSongToTextFile(Song* pSong, FILE* fp)
{
    //Artist
    fprintf(fp,"%s\n", pSong->artist.name);
    if (!pSong)
        return 0;
    fprintf(fp, "%s\n", pSong->songName);
    fprintf(fp, "%s\n", pSong->songCode);
    fprintf(fp, "%d,%d,%d,%d\n", pSong->minutes, pSong->seconds, pSong->amountPlayedSong, pSong->typeOfSong);
    return 1;
}
Artist* findArtistInArr(const Artist* pArr,int size, const char* name)
{
    for (int i = 0; i < size; i++)
    {
        if (!strcmp(pArr[i].name, name))
            return &pArr[i];
    }
    return NULL;
}