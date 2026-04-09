#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "common.h"
#include "types.h"
/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;                        // variables to store width and height
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);        // move file pointer to 18th byte

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);     // read width (4 bytes)
    printf("width = %u\n", width);                 // print width

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);   // read height (4 bytes)
    printf("height = %u\n", height);              // print height

    // Return image capacity
    return width * height * 3;              // return total image capacity (RGB = 3 bytes per pixel)
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r"); // open source BMP file
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)                            // check error
    {
    	perror("fopen");                                           // print system error
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;           // return failure
    
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");   // open secret file
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");// open output image
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }
    // No failure return e_success
    return e_success;    // all files opened successfully
}

    uint get_file_size(FILE *fptr)
    {
        //logic to find secret file size use fseek and ftell
        fseek(fptr, 0, SEEK_END);   // move to end of file
        uint size = ftell(fptr);    // get current position (file size)
        rewind(fptr);               // go back to beginning
        return size;                // return size
    } 

    Status check_capacity(EncodeInfo *encInfo)
    {
        //step 1 -> encInfo ->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image)
        encInfo ->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);     // get image capacity
        
        //step 2 -> encInfo ->size_secret_file = get_file_size(encInfo -> fptr_secret)
        encInfo ->size_secret_file = get_file_size(encInfo -> fptr_secret);            // get secret file size

        //step 3 -> encInfo -> copy_bmp_header(encInfo->stego_image_fname)
        //encInfo -> = copy_bmp_header(encInfo -> stego_image_fname);

        int required_size = encInfo->size_secret_file * 8;      // required bits to store data
        if(encInfo->image_capacity > required_size)             // check if image can hold data
        {
            return e_success;                                   // enough space
        }
        else
        {
            return e_failure;                                   // not enough space
        }
    }

    Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
    {
        // check argv[2]
        if (argv[2] == NULL)                        // check input image argument
        {
            printf("Error: argv[2] is missing\n");
            return e_failure;
        }

        // check the argv[2] is .bmp file or not
            //encInfo->src_image_fname= argv[2];
        // if it is not .bmp file return e_failure
        if(strstr(argv[2],".bmp")!=NULL)                // check .bmp extension
        {
            if(strcmp(strstr(argv[2], ".bmp"), ".bmp") == 0)
            {
                encInfo->src_image_fname= argv[2];          // assign filename
            }
            else
            {
                printf("Error: %s is not a valid .bmp file\n", argv[2]);
                return e_failure;
            }
        }
        else
        {
            printf("Error: argv[2] is not .bmp file\n");
            return e_failure;
        }
    


        // check argv[3]
        if (argv[3] == NULL)                        // check secret file argument
        {
            printf("Error: argv[3] is missing\n");
            return e_failure;
        }
        // check the argv[3] is .txt file or not
            //encInfo->secret_fname= argv[3];
        // if it is not .bmp file return e_failure
        if(strstr(argv[3],".txt")!=NULL)
        {
            if (strcmp(strstr(argv[3], ".txt"), ".txt") == 0)   // check .txt extension
            {
                encInfo->secret_fname = argv[3];
            }
            else
            {
                printf("Error: %s is not a valid .txt file\n", argv[3]);
                return e_failure;
            }
        }
        else
        {
            printf("Error: argv[3] is not .txt file\n");
            return e_failure;
        }
        

        //check argv[4] is present or not 
        //output file
        // check the argv[4] is .bmp file or not
            //encInfo->_stego_image_fname= argv[4];
        // if it is not .bmp file return e_failure
        if(argv[4]!=NULL)                                           // check output file
        {
            if (strstr(argv[4], ".bmp") != NULL)
            {
                if (strcmp(strstr(argv[4], ".bmp"), ".bmp") == 0)
                {
                    encInfo->stego_image_fname = argv[4];           // assign output file
                }
                else
                {
                    printf("Error: %s is not a valid .bmp file\n", argv[4]);
                    return e_failure;
                }
            }
            else
            {
                printf("Error: argv[4] is not .bmp file\n");
                return e_failure;  
            }
        }
        else
        {
            encInfo->stego_image_fname = "stego.bmp";           // default name
        }   

            //store default name 
                //encInfo->_stego_image_fname= "stego.bmb";
            //encInfo->_stego_image_fname= "stego.bmb";

        return e_success;
        
    }
    Status do_encoding(EncodeInfo *encInfo)
    {
        //step 1 ->check open_files(encInfo) return value is e_succcess or not
            //e_failure -> printf error message msg and return e_failure
            //e_success -> printf success message and goto step 2

        if(open_files(encInfo)==e_failure)              // open files
        {
            printf("Error in opening file\n");
            return e_failure;
        }
        //step 2 -> check_capacity(encInfo)
        if(check_capacity(encInfo)==e_failure)          // check capacity
        {
            printf("Insufficient image\n");
            return e_failure;
        }    
        if(copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_failure)
        {
            printf("Error:in copying bmp header\n");
            return e_failure;
        } 
        if(encode_magic_string(MAGIC_STRING, encInfo)==e_failure)
        {
            printf("Error: in encodeing magic string\n");
            return e_failure;
        }
        if(encode_secret_file_extn_size(4, encInfo)==e_failure)
        {
            printf("Error in encoding extn size\n");
            return e_failure;
        }
        if (encode_secret_file_extn(".txt", encInfo) == e_failure)
        {
            printf("Error in encoding extn\n");
            return e_failure;
        }
         if (encode_secret_file_size(encInfo->size_secret_file, encInfo) == e_failure)
        {
            printf("Error in encoding file size\n");
            return e_failure;
        }

        if (encode_secret_file_data(encInfo) == e_failure)
        {
            printf("Error in encoding file data\n");
            return e_failure;
        }

        if (copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_failure)
        {
            printf("Error in copying remaining data\n");
            return e_failure;
        }

        return e_success;
    }


        //step3-> copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image);
             //e_failure -> print error msg and return e_failure
                //return e_success->print success msg and goto step 4


        //step4 ->  encode_magic_string(const char *magic_string, EncodeInfo *encInfo);
            //e_failure -> print error msg and return e_failure
                //return e_success->print success msg and goto step 5


        //step5 -> encode_secret_file_extn_size(int file_extn_size, EncodeInfo *encInfo);
            //e_failure -> print error msg and return e_failure
                //return e_success->print success msg and goto next step 
    

    //step3-> copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image);
        //e_failure -> print error msg and return e_failure
            //return e_success->print success msg and goto step 4
    Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
    {
        char buffer[54];                          // buffer for header
        rewind(fptr_src_image);                  // go to start

        fread(buffer, 54, 1, fptr_src_image);   // read header
        fwrite(buffer, 54, 1, fptr_dest_image); // write header

        return e_success;
    }

    //step4 ->  encode_magic_string(const char *magic_string, EncodeInfo *encInfo);
            //e_failure -> print error msg and return e_failure
                //return e_success->print success msg and goto step 5
    Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
    {
        //Status encode_data_to_image(magic_string, 2, encInfo->fptr_src_image, FILE *fptr_stego_image);
         //e_failure -> print error msg and return e_failure
                //return e_success->print success msg 

        if (encode_data_to_image((char *)magic_string, 2,
                             encInfo->fptr_src_image,
                             encInfo->fptr_stego_image) == e_failure)
        {
            printf("Error: Encoding magic string failed\n");
            return e_failure;
        }
        else
        {
            printf("Magic string encoded successfully\n");
            return e_success;
        }
    }
    Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
    {
        //loop for size times 
        //read 8 bytes of data from src file
        //first char of magic string
        //one by one char from data
        //encode_byte_to_lsb(data[0], image_buffer); /*char image_data[MAX_IMAGE_BUF_SIZE];*/
        //write 8 bytes of image_buffer into stego file

        char image_buffer[8];                         // buffer for 8 bytes
        for (int i = 0; i < size; i++)               // loop for each character
        {
            fread(image_buffer, 8, 1, fptr_src_image); // read 8 bytes

            encode_byte_to_lsb(data[i], image_buffer);  // encode 1 char

            fwrite(image_buffer, 8, 1, fptr_stego_image); // write modified data
        }

        return e_success;
    }
    Status encode_byte_to_lsb(char data, char *image_buffer)
    {
        //loop for 8 times
            //clear the lsb bit of image buffer
            //get 1 bit from data shift to lsb side
            //merge the image buffer and 1 bit data

           int mask = 1;                                // mask to extract 1 bit

        // loop for 8 bits
        for(int i = 0; i < 8; i++)                      // loop for 8 bits
        {
            // clear LSB of image_buffer
            image_buffer[i] = image_buffer[i] & (~mask);   // clear LSB

            // get bit from data (MSB to LSB)
            int bit = (data >> (7 - i)) & mask;         // get bit from data

            // merge bit into image_buffer
            image_buffer[i] = image_buffer[i] | bit;    // set LSB
        }

        //return e_success
        return e_success;
    }

    Status encode_int_to_lsb(int data, char *image_buffer)
    {
        //loop for 32 times
            //clear the lsb bit of image buffer
            //get 1 bit from data shift to lsb side
            //merge the image buffer and 1 bit data

             int mask = 1;

        // loop for 32 bits
        for(int i = 0; i < 32; i++)
        {
            // clear LSB
            image_buffer[i] = image_buffer[i] & (~mask);

            // get bit from int
            int bit = (data >> (31 - i)) & mask;

            // merge bit
            image_buffer[i] = image_buffer[i] | bit;
        }
        //return e_success
        return e_success;

    }
    Status encode_secret_file_extn_size(int file_extn_size, EncodeInfo *encInfo)
    {
        //read 32 bytes from src file
        //encode_int_to_lsb(file_extn_size, image_buffer);
        //write 32 bytes in stego file

        char image_buffer[32];                                  // buffer for 32 bytes

        fread(image_buffer, 32, 1, encInfo->fptr_src_image);   // read image data

        encode_int_to_lsb(file_extn_size, image_buffer);      // encode size

        fwrite(image_buffer, 32, 1, encInfo->fptr_stego_image); // write

        return e_success;
    }

    //step5 -> encode_secret_file_extn_size(int file_extn_size, EncodeInfo *encInfo);
            //e_failure -> print error msg and return e_failure
                //return e_success->print success msg and goto next step
    Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
    {
        return encode_data_to_image((char *)file_extn, 4,
                                            encInfo->fptr_src_image, 
                                            encInfo->fptr_stego_image);
    }
    
    Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
    {
        char image_buffer[32];

        fread(image_buffer, 32, 1, encInfo->fptr_src_image);        // read

        encode_int_to_lsb(file_size, image_buffer);                // encode size

        fwrite(image_buffer, 32, 1, encInfo->fptr_stego_image);   // write

        return e_success;
    }
    Status encode_secret_file_data(EncodeInfo *encInfo)
    {
        char data[1];                                       // buffer for 1 byte

        while(fread(data, 1, 1, encInfo->fptr_secret))      // read byte by byte
        {
            encode_data_to_image(data, 1,
                                encInfo->fptr_src_image,
                                encInfo->fptr_stego_image);
        }

        return e_success;
    }
    Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
    {
        char data[1];                                           // buffer for 1 byte

        while(fread(data, 1, 1, fptr_src))                      // read remaining bytes
        {
            fwrite(data, 1, 1, fptr_dest);                      // copy directly
        }

        return e_success;
    }
