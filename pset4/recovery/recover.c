#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512
#define MAX_LENGTH 100

int main(int argc, char *argv[])
{
    // Open the memory card
    FILE *input = fopen(argv[1], "r");

    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }



    if (input != NULL)
    {
        int count_img = 0;
        BYTE buffer[BLOCK_SIZE];
        char output[MAX_LENGTH];
        FILE *img;
        bool found = false;
        int offset = 0x00;

        // fread returns 0 (which is effectively false), loop will end
        while ( fread(&buffer, sizeof(BYTE), BLOCK_SIZE, input) )
        {
            // keep track of next offset in the memory card
            offset += 0x200;

            bool condition = (buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0);

            if (condition)
            {
                // first jpeg
                if (count_img == 0)
                {
                    sprintf(output, "%03i.jpg", count_img);
                    img = fopen(output, "w");
                    fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);

                    // found the jpegs
                    found = true;
                    count_img++;
                }

                //next jpegs
                else
                {
                    // close previous jpeg
                    fclose(img);

                    // write to the next jpeg
                    sprintf(output, "%03i.jpg", count_img);
                    img = fopen(output, "w");
                    fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);

                    count_img++;
                }
            }

            // countinue writing the remaining blocks of a jpeg
            else
            {
                if (count_img >= 0 && found)
                    fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);

                // from the beginning of the memory card, no jpeg detected yet, then countinue detecting/reading
                else
                    continue;
            }

        }

        fclose(input);
    }

    return EXIT_SUCCESS;
}
