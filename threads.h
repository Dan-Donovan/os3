#ifndef __THREADS_H__
#define __THREADS_H__



/*
typedef struct __attribute__ ((packed)) {
        uint8_t dir_name[11];           // short name
        uint8_t dir_attr;               // File sttribute
        uint8_t dir_NTRes;              // Set value to 0, never chnage this
        uint8_t dir_crtTimeTenth;       // millisecond timestamp for file creation time
        uint16_t dir_crtTime;           // time file was created
        uint16_t dir_crtDate;           // date file was created
        uint16_t dir_lstAccDate;        // last access date
        uint16_t dir_fstClusHI;         // high word fo this entry's first cluster number
        uint16_t dir_wrtTime;           // time of last write
        uint16_t dir_wrtDate;           // dat eof last write
        uint16_t dir_fstClusLO;         // low word of this entry's first cluster number
        uint32_t dir_fileSize;          // 32-bit DWORD hoding this file's size in bytes
} dirEnt;*/


extern void bigger_number(void * arg);




#endif
