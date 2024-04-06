//
// Created by אילון אהרוני on 05/04/2024.
//

#ifndef FINALWORKINC_ARTISTREPOSITORY_H
#define FINALWORKINC_ARTISTREPOSITORY_H
#include "artist.h"


typedef struct {
    Artist *allArtists;
    int numOfArtist;

} ArtistRepository;


int initArtistRepositoryFromFile(ArtistRepository* artistRepository,const char* fileName, int typeFile);
int saveArtistRepositoryToFile(ArtistRepository* artistRepository, const char* fileName, int typeFile);
int addArtistToRepository(ArtistRepository* artistRepository);
int showArtistRepository(ArtistRepository* artistRepository);
int	createArtistArr(ArtistRepository* artistRepository);
void freeArtistRepository(ArtistRepository * artistRepository);
#endif //FINALWORKINC_ARTISTREPOSITORY_H
