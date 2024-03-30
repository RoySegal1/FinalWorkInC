#include "stdio.h"
#include "artist.h"

int main() {
    Artist artist;
    initArtist(&artist);
    getArtistName(&artist);
    showArtist(&artist);

	return 0;
}
