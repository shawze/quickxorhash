#ifndef QUICKXORHASH_H
#define QUICKXORHASH_H

#include <stdint.h>

struct qxhash {
    size_t      width;
    size_t      shift;
    size_t      shifted;
    uint64_t      len;
    // long long int      len;

    size_t      cell_len;
    uint64_t    *cell;
};

typedef struct qxhash qxhash;

qxhash  *qxh_new( void );
void    qxh_update( qxhash *, uint8_t *, size_t );
char    *qxh_finalize( qxhash * );
void    qxh_free( qxhash * );
char    *qxh_file(qxhash *, const char * filename);

#endif /* QUICKXORHASH_H */
