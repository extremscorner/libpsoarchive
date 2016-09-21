/*
    This file is part of libpsoarchive.

    Copyright (C) 2015, 2016 Lawrence Sebald

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 2.1 or
    version 3 of the License.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PSOARCHIVE__PRSD_H
#define PSOARCHIVE__PRSD_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include "psoarchive-error.h"

/* Endianness values. Auto is only valid for decompression. */
#define PSO_PRSD_AUTO_ENDIAN            0
#define PSO_PRSD_BIG_ENDIAN             1
#define PSO_PRSD_LITTLE_ENDIAN          2

/* Compress a buffer with PRSD compression and encryption.

   This function compresses the data in the src buffer into a new buffer. This
   function will never produce output larger than that of the prsd_archive
   function, and will usually beat that function rather significantly.

   It is the caller's responsibility to free *dst when it is no longer in use.

   Returns a negative value on failure (specifically something from
   psoarchive-error.h). Returns the size of the compressed output on success.
*/
int pso_prsd_compress(const uint8_t *src, uint8_t **dst, size_t src_len,
                      uint32_t key);

/* Archive and encrypt a buffer in PRSD format.

   This function archives the data in the src buffer into a new buffer. This
   function will always produce output that is larger in size than the input
   data (it does not actually compress the output. There's probably no good
   reason to ever use this, but it is here if you want it for some reason.

   All the notes about parameters and return values from prs_compress also apply
   to this function. The size of the output from this function will be equal to
   the return value of prsd_max_compressed_size when called on the same length.
*/
int pso_prsd_archive(const uint8_t *src, uint8_t **dst, size_t src_len,
                     uint32_t key);

/* Return the maximum size of archiving a buffer in PRSD format.

   This function returns the size that prsd_archive will spit out. This is used
   internally to allocate memory for prsd_archive and prsd_compress and probably
   has little utility outside of that.
*/
size_t pso_prsd_max_compressed_size(size_t len);

/* Decompress a PRSD archive from a file.

   This function opens the file specified and decompresses the data from the
   file into a newly allocated memory buffer.

   It is the caller's responsibility to free *dst when it is no longer in use.

   Returns a negative value on failure (specifically something from
   psoarchive-error.h). Returns the size of the decompressed output on success.
*/
int pso_prsd_decompress_file(const char *fn, uint8_t **dst, int endian);

/* Decompress PRSD-compressed data from a memory buffer.

   This function decompresses PRSD-compressed data from the src buffer into a
   newly allocated memory buffer.

   It is the caller's responsibility to free *dst when it is no longer in use.

   Returns a negative value on failure (specifically something from
   psoarchive-error.h). Returns the size of the decompressed output on success.
*/
int pso_prsd_decompress_buf(const uint8_t *src, uint8_t **dst, size_t src_len,
                            int endian);

/* Decompress PRSD-compressed data from a memory buffer into a previously
   allocated memory buffer.

   This function decompresses PRSD-compressed data from the src buffer into the
   previously allocated allocated memory buffer dst. You must have already
   allocated the buffer at dst, and it should be at least the size returned by
   prsd_decompress_size on the compressed input (otherwise, you will get an
   error back from the function).

   Returns a negative value on failure (specifically something from
   psoarchive-error.h). Returns the size of the decompressed output on success.
*/
int pso_prsd_decompress_buf2(const uint8_t *src, uint8_t *dst, size_t src_len,
                             size_t dst_len, int endian);

/* Determine the size that the PRSD-compressed data in a buffer will expand to.

   This function examines the header from the PRSD data to determine the
   ultimate length that the data would expand to if it were to be decompressed.

   Returns a negative value on failure (specifically something from
   psoarchive-error.h). Returns the size of the decompressed output on success.
*/
int pso_prsd_decompress_size(const uint8_t *src, size_t src_len,
                             int endian);

#endif /* !PSOARCHIVE__PRS_H */
