#include <stdio.h>              // Standard input-output header
#include <string.h>             // String handling functions
#include "encode.h"             // Encoding header file
#include "decode.h"             // Decoding header file
#include "common.h"             // Magic string definitions
#include "types.h"              // User-defined types


Status open_files_for_decode(DecodeInfo *decInfo)   // Function to open required files for decoding
{
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "r"); // open stego image file

    if (decInfo->fptr_stego_image == NULL)   // check if file open failed
    {
    	perror("fopen");   // print system error
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->stego_image_fname); // print error message

    	return e_failure;   // return failure
    }
    decInfo->fptr_output = fopen(decInfo->output_fname, "w"); // open output file
    if (decInfo->fptr_output == NULL)   // check if file open failed
    {
    	perror("fopen");   // print system error
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->output_fname); // print error message

    	return e_failure;   // return failure
    }

    //here there is no secret file because the secrete msg already stored into stego.bmp

    return e_success;   // return success

}
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)   // validate decode arguments
{
    if(strstr(argv[2],".bmp")!=NULL)   // check if input is bmp
    {
        decInfo->stego_image_fname = argv[2];   // assign stego image filename
    }
    else   // if not bmp
    {
        return e_failure;   // return failure
    }

    if(strstr(argv[3],".txt")!=NULL)   // check if output is txt
    {
        decInfo->output_fname= argv[3];   // assign output filename
    }
    else   // if not txt
    {
        return e_failure;   // return failure
    }

    if(argv[4]!=NULL)   // check if optional argument exists
    {
        decInfo->output_fname = argv[4];   // override output filename
    }
    else   // if not provided
    {
        decInfo->output_fname = "output.txt";   // default filename
    }
    return e_success;   // return success
}
Status do_decoding(DecodeInfo *decInfo)   // main decoding function
{
    // Step 1: open files
    if (open_files_for_decode(decInfo) == e_failure)   // open files
    {
        printf("Error: opening files\n");   // print error
        return e_failure;   // return failure
    }

    // Step 2: skip bmp header
    if (fseek(decInfo->fptr_stego_image, 54, SEEK_SET) != 0)   // skip header
    {
        printf("Error: skipping bmp header\n");   // error message
        return e_failure;   // return failure
    }

    // Step 3: decode magic string
    if (decode_magic_string(MAGIC_STRING, decInfo) == e_failure)   // decode magic
    {
        printf("Error: decoding magic string\n");   // error
        return e_failure;   // return failure
    }

    // Step 4: decode extension size
    if (Decode_secret_file_extn_size(decInfo) == e_failure)   // decode extn size
    {
        printf("Error: decoding extension size\n");   // error
        return e_failure;   // return failure
    }

    // Step 5: decode extension
    if (decode_secret_file_extn(decInfo->extn_output_file, decInfo) == e_failure)   // decode extension
    {
        printf("Error: decoding extension\n");   // error
        return e_failure;   // return failure
    }

    // Step 6: decode file size
    if (decode_secret_file_size(decInfo) == e_failure)   // decode file size
    {
        printf("Error: decoding file size\n");   // error
        return e_failure;   // return failure
    }

    // Step 7: decode actual data
    if (decode_secret_file_data(decInfo) == e_failure)   // decode data
    {
        printf("Error: decoding file data\n");   // error
        return e_failure;   // return failure
    }

    printf("Decoding completed successfully\n");   // success message

    return e_success;   // return success
}
Status skip_bmp_header(FILE *fptr_src_image)   // function to skip bmp header
{
    fseek(fptr_src_image, 54, SEEK_SET);   // move pointer to pixel data
    return e_success;   // return success
}

Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo)   // decode magic string
{
    
    char user_magic[3];   // buffer for user input

    printf("Enter magic string: ");   // prompt user
    scanf("%s", user_magic);   // read input

    char buffer[2];   // buffer to store decoded data
    if(decode_image_to_data(buffer, 2,decInfo->fptr_stego_image)==e_failure)   // decode magic
    {
        printf("Error: decoding magic string failed\n");   // error
        return e_failure;   // return failure
    }
    if(buffer[0] != user_magic[0] || buffer[1] != user_magic[1])   // compare strings
    {
        printf("Error: magic string mismatched\n");   // error
        return e_failure;   // return failure
    }
    else   // if matched
    {
        printf("Magic string decoded successfully\n");   // success
        return e_success;   // return success
    }
}
Status decode_image_to_data(char *data, int size,FILE *fptr_stego_image)   // decode data from image
{
    char image_buffer[8];   // buffer

    for (int i = 0; i < size; i++)   // loop
    {
        fread(image_buffer, 8, 1, fptr_stego_image);   // read 8 bytes

        data[i] = decode_lsb_to_byte( image_buffer);   // decode byte
    }
    return e_success;   // return success
}
char decode_lsb_to_byte(char *image_buffer)   // convert LSB to byte
{
    char ch = 0;   // initialize char
    int mask = 1;   // mask
    for(int i=0; i<8; i++)   // loop
    {
        ch = ch<<1;   // shift left

        ch = ch | (image_buffer[i] & mask);   // extract bit and merge
    }
    return ch;   // return decoded char
}
int decode_lsb_to_int(char *image_buffer)   // convert LSB to int
{
    int mask = 1;   // mask
    int data = 0;   // initialize

    for(int i=0; i<32; i++)   // loop
    {
        data = data<<1;   // shift left

        int bit = image_buffer[i]&mask ;   // extract bit

        data = data|bit ;   // merge bit
    }
    return data;   // return integer
}
Status Decode_secret_file_extn_size(DecodeInfo *decInfo)   // decode extension size
{
    char image_buffer[32];   // buffer

    fread(image_buffer, 32, 1, decInfo->fptr_stego_image);   // read data

    decInfo->extn_size = decode_lsb_to_int(image_buffer);   // decode size

    return e_success;   // return success
}
Status decode_secret_file_extn(const char *file_extn, DecodeInfo *decInfo)   // decode extension
{
    char buffer[4];   // buffer
    if(decode_image_to_data(buffer, 4, decInfo->fptr_stego_image)==e_failure)   // decode
    {
        return e_failure;   // return failure
    }
    for(int i=0; i<4; i++)   // loop
    {
        decInfo->extn_output_file[i]=buffer[i];   // store extension
    }

    return e_success;   // return success
}
Status decode_secret_file_size(DecodeInfo *decInfo)   // decode file size
{
    char image_buffer[32];   // buffer

    fread(image_buffer, 32, 1, decInfo->fptr_stego_image);   // read

    decInfo->size_output_file= decode_lsb_to_int(image_buffer);   // decode size


    return e_success;   // return success
}
Status decode_secret_file_data(DecodeInfo *decInfo)   // decode actual data
{
    char ch;   // variable to store char


    for(int i=0; i< decInfo->size_output_file; i++)   // loop through file size
    {
        decode_image_to_data(&ch,1,  decInfo->fptr_stego_image);   // decode one byte
        fwrite(&ch,1,1,decInfo->fptr_output);   // write to output file
    }
    
    return e_success;   // return success
}
