#ifndef DECODE_H                      // Prevent multiple inclusion of this header file
#define DECODE_H                      // Define macro DECODE_H

#include "types.h"                   // Include user-defined types



#define MAX_SECRET_BUF_SIZE 1        // Define maximum size for secret buffer
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)  // Define image buffer size (8 bits per byte)
#define MAX_FILE_SUFFIX 4            // Define maximum file extension size

typedef struct _DecodeInfo          // Define structure for decoding information
{
    /* Stego Image info */
    char *stego_image_fname;        // Pointer to stego image file name
    FILE *fptr_stego_image;         // File pointer for stego image
    char magic_string[3];           // Array to store extracted magic string
    /*uint image_capacity;          // (Commented) Image capacity
    uint bits_per_pixel;            // (Commented) Bits per pixel
    char image_data[MAX_IMAGE_BUF_SIZE];*/ // (Commented) Image data buffer

    /* Output File Info */
    char *output_fname;             // Pointer to output file name
    FILE *fptr_output;              // File pointer for output file
    long extn_size;                 // Size of file extension
    char extn_output_file[4];       // Array to store output file extension
    //char secret_data[MAX_SECRET_BUF_SIZE]; // (Commented) Buffer for secret data
    long size_output_file;          // Size of decoded output file

} DecodeInfo;                       // Structure name


/* Decoding function prototype */   // Section for decoding function declarations


/* Read and validate Encode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo); // Function to validate decode arguments

/* Perform the decoding */
Status do_decoding(DecodeInfo *decInfo); // Main decoding function

/* Get File pointers for i/p and o/p files */
Status open_files_for_decode(DecodeInfo *decInfo); // Function to open files for decoding


/* Skip bmp image header */
Status skip_bmp_header(FILE *fptr_src_image); // Function to skip BMP header

/* Get Magic String */
Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo); // Decode magic string

/* Decode secret file extenstion */
Status Decode_secret_file_extn_size(DecodeInfo *decInfo);// Decode extension size


/* Decode secret file extenstion */
Status decode_secret_file_extn(const char *file_extn, DecodeInfo *decInfo);// Decode extension

/* Decode secret file size */
Status decode_secret_file_size(DecodeInfo *decInfo);// Decode file size

/* Decode secret file data*/
Status decode_secret_file_data(DecodeInfo *decInfo);// Decode actual file data

/* Decode function, which does the real encoding */
Status decode_image_to_data(char *data, int size,FILE *fptr_stego_image); // Core decoding function

/* Decode a byte into LSB of image data array */
char decode_lsb_to_byte(char *image_buffer); // Decode one byte from LSB

/* Decode a byte into LSB of image data array */
int decode_lsb_to_int(char *image_buffer); // Decode integer from LSB


#endif                                // End of header guard
