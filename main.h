#pragma once



int userSubMenu(User* pUser, const SongRepository* pSongs, const PlayListRepository* pPlayLists,const AlbumManager* pAlbums);
int initSystemFromFile(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum, int typeFile);
int saveSystemFiles(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum,User* pUser);//need to check that user isn't null
void endProgram(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum,User* pUser);//need to check that user isn't null
void freeSystem(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum,User* pUser);


void freeSystem(SongRepository* pSong, PlayListRepository* pPlayList, ArtistRepository* pArtists,AlbumManager* pAlbum,User* pUser);