//
// Created by User on 31/03/2024.
//

#ifndef FINALWORKINC_MACROS_H
#define FINALWORKINC_MACROS_H

#define ERROR 0
#define FROM_TEXT_FILE 1
#define FROM_BINARY_FILE 2
#define ALOC_ERROR "Allocation error"
#define SONGS_REPO_FROM_TEXT "Songs.txt"
#define SONGS_REPO_FROM_BIN "Songs.bin"
#define ARTIST_REPO_FROM_TEXT "Artist.text"
#define ARTIST_REPO_FROM_BIN "ComperssArtistRepo.bin"
#define PLAYLIST_REPO_FROM_TEXT "PlayList.txt"
#define PLAYLIST_REPO_FROM_BIN "PlayList.bin"




#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define CHECK_RETURN_NULL(ptr) {if(!ptr) return NULL;}
#define CHECK_RETURN_0(fp) if(!fp) return 0;
#define CHECK_CLOSE_RETURN_NULL(ptr,fp) {if(!ptr){fclose(fp); return NULL;}}
#define CHECK_CLOSE_PRINT_RETURN_0(ptr,fp,str) {if(!ptr){printf(#str"\n"); fclose(fp); return 0;}}
#define CHECK_RETURN_0_PRINT(ptr,str) {if(!ptr){ printf(#str"\n"); return 0;}}
#define CHECK_RETURN(fp) if(!fp) return;
#define RETURN_0_CLOSE_FILE(fp) {fclose(fp); return 0;}

#endif //FINALWORKINC_MACROS_H
