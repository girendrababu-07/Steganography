#ifndef ENCODE_H                      // Prevent multiple inclusion of this header file
#define ENCODE_H                      // Define macro ENCODE_H

#include "types.h"                   // Include user-defined types

/* 
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

#define MAX_SECRET_BUF_SIZE 1        // Define maximum size for secret buffer
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)  // Define image buffer size (8 bits per byte)
#define MAX_FILE_SUFFIX 4            // Define maximum file extension size

typedef struct _EncodeInfo          // Define structure for encoding information
{
    /* Source Image info */
    char *src_image_fname;          // Pointer to source image file name
    FILE *fptr_src_image;           // File pointer for source image
    uint image_capacity;            // Stores total capacity of the image
    uint bits_per_pixel;            // Stores bits per pixel of image
    char image_data[MAX_IMAGE_BUF_SIZE];  // Buffer to store image data

    /* Secret File Info */
    char *secret_fname;             // Pointer to secret file name
    FILE *fptr_secret;              // File pointer for secret file
    char extn_secret_file[MAX_FILE_SUFFIX]; // Array to store secret file extension
    char secret_data[MAX_SECRET_BUF_SIZE];  // Buffer to store secret data
    long size_secret_file;          // Size of secret file

    /* Stego Image Info */
    char *stego_image_fname;        // Pointer to stego image file name
    FILE *fptr_stego_image;         // File pointer for stego image

} EncodeInfo;                       // Structure name


/* Encoding function prototype */

/* Check operation type */
OperationType check_operation_type(char *argv[]);  // Function to check encode/decode operation

/* Read and validate Encode args from argv */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo);  // Validate encode arguments

/* Perform the encoding */
Status do_encoding(EncodeInfo *encInfo);  // Main encoding function

/* Get File pointers for i/p and o/p files */
Status open_files(EncodeInfo *encInfo);   // Function to open required files

/* check capacity */
Status check_capacity(EncodeInfo *encInfo); // Check if image can hold secret data

/* Get image size */
uint get_image_size_for_bmp(FILE *fptr_image); // Get BMP image size

/* Get file size */
uint get_file_size(FILE *fptr);  // Get size of any file

/* Copy bmp image header */
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image); // Copy BMP header

/* Store Magic String */
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo); // Encode magic string

/* Encode secret file extenstion */
Status encode_secret_file_extn_size(int file_extn_size, EncodeInfo *encInfo); // Encode extension size


/* Encode secret file extenstion */
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo); // Encode extension

/* Encode secret file size */
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo); // Encode file size

/* Encode secret file data*/
Status encode_secret_file_data(EncodeInfo *encInfo); // Encode actual file data

/* Encode function, which does the real encoding */
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image); // Core encoding

/* Encode a byte into LSB of image data array */
Status encode_byte_to_lsb(char data, char *image_buffer); // Encode 1 byte into LSB

Status encode_int_to_lsb(int data, char *image_buffer); // Encode integer into LSB

/* Copy remaining image bytes from src to stego image after encoding */
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest); // Copy remaining data

#endif                                 // End of header guard
