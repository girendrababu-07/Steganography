#ifndef TYPES_H              // Prevent multiple inclusion of this header file
#define TYPES_H              // Define the macro TYPES_H

/* User defined types */     // Comment indicating custom type definitions

typedef unsigned int uint;   // Create alias 'uint' for 'unsigned int'

/* Status will be used in fn. return type */   // Comment explaining purpose of Status enum
typedef enum                  // Define an enumeration for status
{
    e_success,               // Indicates successful operation
    e_failure                // Indicates failed operation
} Status;                    // Name of enum type is 'Status'

typedef enum                  // Define an enumeration for operation types
{
    e_encode,                // Represents encoding operation
    e_decode,                // Represents decoding operation
    e_unsupported            // Represents unsupported operation
} OperationType;             // Name of enum type is 'OperationType'

#endif                       // End of header guard

