#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <time.h>
#include "artist.h"
#include "song.h"
#include "album.h"
#include "songRepository.h"
#include "playlistRepository.h"
#include "artistRepository.h"
#include "playList.h"
#include "user.h"
#include "macros.h"

void mainMenu();
void userSubMenu(User* pUser,const SongRepository*,const PlayListRepository* pPlayList);
int initSystemFromFile(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists, int typeFile);
int saveSystemFiles(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists, int typeFile);




