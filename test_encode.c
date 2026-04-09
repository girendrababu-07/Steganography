#include <stdio.h>          // Standard input-output functions
#include <string.h>         // String handling functions like strcmp
#include "encode.h"         // Header file for encoding functions and structures
#include "decode.h"         // Header file for decoding functions and structures
#include "types.h"          // Header file for user-defined types

/*
    MAIN FUNCTION
    -------------
    This is the starting point of the program.
    It controls the complete Image Steganography application.

    Responsibilities of main():
    1. Read command-line arguments (encode/decode option).
    2. Identify operation type (-e for encode, -d for decode).
    3. Validate input arguments.
    4. Call encoding function to hide secret data into image.
    5. Call decoding function to extract hidden data from image.
    6. Display success or error messages.
*/

int main(int argc, char *argv[])   // Main function with argument count and argument vector
{
    EncodeInfo encInfo;            // Structure variable to store encoding details
    DecodeInfo decInfo;            // Structure variable to store decoding details
    
    //validate argc>=2
    if(argc<2)                     // Check if minimum arguments are provided
    {
        printf("Usage: ./a.out -e/-d ...\n");   // Print usage message
        return e_failure;          // Return failure status
    }
    
    int ret = check_operation_type(argv);   // Determine operation type based on arguments

    if(ret == e_encode)           // Check if operation is encoding
    {
        if (argc>=4)              // Ensure enough arguments for encoding
        {
            if (read_and_validate_encode_args(argv, &encInfo)== e_success)  // Validate encode arguments
            {
                if(do_encoding(&encInfo)==e_success)   // Perform encoding
                {
                    printf("\nEncoding completed successfully\n");  // Success message
                    //encoding completed successfully
                }
                else
                {
                    printf("\nError: in do_encoding\n");   // Error message for encoding failure
                    return e_failure;      // Return failure
                    // error message and terminate the program
                }
                
            }
        }    
        else
        {
            printf("\nErro: argument count should be greater than or equal to 4\n"); // Argument error
            return  e_failure;      // Return failure
            // error message and terminate the program
        }
            
        //encoding
    }
    else if(ret == e_decode)      // Check if operation is decoding
    {
        if (read_and_validate_decode_args(argv, &decInfo) == e_success)  // Validate decode arguments
        {
            if (do_decoding(&decInfo) == e_success)   // Perform decoding
            {
                printf("\nDecoding completed successfully\n");  // Success message
            }
            else
            {
                printf("\nError: in decoding\n");   // Error message for decoding failure
                return e_failure;                  // Return failure
            }
        }
        else
        {
            printf("\nError: invalid decode arguments\n");  // Invalid argument message
            return e_failure;            // Return failure
        }
    }
    else
    {
        printf("Invalid input\nUnsupported\n");  // Unsupported operation message
    }
    
     return 0;             // Return success (program end)
}
    
OperationType check_operation_type(char *argv[])   // Function to check operation type
{
    //strcmp
    //check the argv[1] is -e or not
        // return e_encode
    if(strcmp(argv[1], "-e")==0)   // Compare argument with "-e"
    {
        return e_encode;           // Return encode type
    }
    
    //check the argv[1] is -d or not
        // return_decode
    if(strcmp(argv[1], "-d")==0)   // Compare argument with "-d"
    {
        return e_decode;           // Return decode type
    }
    //else
        //return e_unsupported
    else
    {
        return e_unsupported;      // Return unsupported type
    }
}
