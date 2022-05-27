// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];    // 8 bits = 1 byte
    fread(&header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(&header, sizeof(uint8_t), HEADER_SIZE, output);

// will return 1 if successful
// fread(&header, HEADER_SIZE, 1, input);

// will return upto what ever HEADER_SIZE is
// fread(&header, sizeof(uint8_t), HEADER_SIZE, output);

    // Read samples from input file and write updated data to output file
    // don't need to use uint16_t, values can be negative!
    // just use int16_t
    int16_t sound;
    int16_t sound_factor;

    while (fread(&sound, sizeof(int16_t), 1, input) > 0)
    {
        // change the content of "sound"
        sound_factor = sound * factor;
        fwrite(&sound_factor, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
