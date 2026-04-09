🖼️ Image Steganography using C (LSB Technique)

📌 Project Overview

This project implements **Image Steganography** using the **Least Significant Bit (LSB)** technique in C. It allows users to securely hide a secret text file inside a BMP image and generate a stego image without visibly altering the original image.

---

🔐 Key Features

* Hide secret `.txt` file inside `.bmp` image
  
* Extract data using decoding (can be implemented separately)
  
* Uses LSB (Least Significant Bit) encoding technique
  
* Maintains original image quality
  
* Modular and structured C code

---

🧠 How It Works

1. The program reads a BMP image file.
   
2. It checks whether the image has enough capacity.
   
3. The BMP header (first 54 bytes) is copied directly.
   
4. Secret data is embedded into the image using LSB:

   * Magic string
     
   * File extension
     
   * File size
     
   * File data
     
7. A new **stego image** is generated with hidden data.

---

⚙️ Technologies Used

* Programming Language: C
  
* File Handling
  
* Bitwise Operations
  
* BMP Image Format

---

📂 Project Structure

```

├── encode.c

├── encode.h

├── decode.c        

├── decode.h

├── common.h

├── test_encode.c

├── types.h




▶️ Compilation & Execution

🔧 Compile

```bash

gcc test_encode.c encode.c decode.c

```

▶️ Run

encoding

./a.out -e beautiful.bmp secret.txt stego.bmp

decoding

./a.out -d stego.bmp output.txt

---

📊 Encoding Process

* Each character (8 bits) is stored in 8 bytes of image data
  
* LSB of each byte is modified to store 1 bit of data

Example:


Original Byte : 10110110

Modified Byte : 10110111



⚠️ Important Notes

* Only **.bmp images** are supported (no compression)
  
* Secret file must be **.txt**
  
* Use **binary mode (rb, wb)** for file handling
  
* Image must have sufficient capacity



🚀 Future Enhancements

* Implement decoding functionality
  
* Add password protection
  
* Support PNG/JPG formats
  
* GUI-based application
  
* Encrypt data before embedding



📌 Applications

* Secure communication
  
* Digital watermarking
  
* Data hiding in cyber security
  
* Military communication systems


 🧪 Sample Output


Magic string encoded successfully

Encoding file size completed

Data embedded successfully


👨‍💻 Author

 T GIRENDRA BABU


📄 License

This project is for educational purposes.


🙌 Acknowledgement

This project is developed as part of learning **Information Security and C Programming concepts**.

---
