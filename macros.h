//
// Created by User on 31/03/2024.
//

#ifndef FINALWORKINC_MACROS_H
#define FINALWORKINC_MACROS_H

#define CHECK_RETURN_NULL(ptr) {if(!ptr) return NULL;}
#define CHECK_COLSE_RETURN_NULL(ptr,fp) {if(!ptr){fclose(fp); return NULL;}}


#endif //FINALWORKINC_MACROS_H
