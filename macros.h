//
// Created by User on 31/03/2024.
//

#ifndef FINALWORKINC_MACROS_H
#define FINALWORKINC_MACROS_H

#define ERROR 0
#define FROM_TEXT_FILE 1
#define FROM_BINARY_FILE 2



#define CHECK_RETURN_NULL(ptr) {if(!ptr) return NULL;}
#define CHECK_RETURN_0(fp) if(!fp) return 0;
#define CHECK_COLSE_RETURN_NULL(ptr,fp) {if(!ptr){fclose(fp); return NULL;}}
#define CHECK_RETURN_0_PRINT_ALOC(ptr) {if(!ptr){ printf("Alocation error\n"); return 0;}}


#endif //FINALWORKINC_MACROS_H
