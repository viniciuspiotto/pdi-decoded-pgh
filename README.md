# PGH Image Decoder

This project is a C implementation of a decoder for a custom image format called PGH. The decoder reads a `.pgh` file, decompresses it using Huffman decoding, and saves the result as a standard `.pgm` (Portable Graymap) image file.

## Functionality

The main program, `decode`, takes a single argument: the path to a `.pgh` image file. It then performs the following steps:

1.  **Reads the PGH file:** It parses the header to get the image dimensions and maximum pixel intensity.
2.  **Extracts the Huffman table:** The PGH file contains a frequency histogram which is used to reconstruct the Huffman tree.
3.  **Decodes the image data:** The compressed pixel data is read as a sequence of bits, which are then traversed through the Huffman tree to recover the original pixel values.
4.  **Writes the PGM file:** A new file with the `-result.pgm` suffix is created, containing the decoded image in the standard PGM format.
5.  **Displays the image:** The program attempts to open the resulting image using the `eog` (Eye of GNOME) image viewer.

## File Descriptions

*   **`decode.c`**: The main entry point of the program. It handles command-line arguments and orchestrates the decoding process by calling functions from the other modules.

*   **`include/descompact.c`** and **`include/descompact.h`**: This module is responsible for the high-level decompression logic. It reads the PGH file, extracts the histogram and the compressed data, and calls the Huffman decoding functions.

*   **`include/huffman.c`** and **`include/huffman.h`**: This module implements the Huffman decoding algorithm. It contains functions to build the Huffman tree from the frequency histogram and to decode the compressed bitstream back into pixel values.

*   **`include/imagelib.c`** and **`include/imagelib.h`**: A small library for basic image manipulation. It provides functions for creating, freeing, and saving images in the PGM format.

*   **`makefile`**: The build script for the project. It compiles the C source files and links them to create the `decode` executable.

## How to Compile and Run

### Compiling

To compile the project, simply run the `make` command in the project's root directory:

```bash
make
```

This will generate an executable file named `decode`.

### Running

To decode a PGH image, run the `decode` executable with the path to the `.pgh` file as an argument:

```bash
./decode image.pgh
```

This will create a new file named `image-result.pgm` in the same directory.

## PGH File Format

The PGH file format is a custom format for storing compressed grayscale images. Based on the decoder's implementation, the format seems to be structured as follows:

1.  **Header:**
    *   A magic number "PH" to identify the file type.
    *   Image dimensions (width and height).
    *   Maximum pixel intensity.
2.  **Histogram:** A frequency table of the pixel intensities, used to build the Huffman tree.
3.  **Compressed Data:** The image's pixel data, compressed using the Huffman coding algorithm.
