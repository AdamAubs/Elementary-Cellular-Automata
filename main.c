/* -------------------------------------------
Project 1: Elementary Cellular Automaton
Course: CS 211, Summer 2024, UIC
System: Advanced zyLab
Author: Adam Aubry
---------------------------------------------- */

#include <stdio.h>
#include <stdbool.h> 

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    bool state[3]; //active status for [left, me, right] cells 
    bool active; //current active status for this cell
} cell;

//convert an 8-bit integer rule (0-255) to array of bits 
//(stored in reverse order)
//   ex: rule = 6  = 00000110 -> [01100000] 
//   ex: rule = 30 = 00011110 -> [01111000] 
//   ex: rule = 65 = 01000001 -> [10000010]
//return true if input rule is valid (0-255)
//return false if input rule is invalid
bool setBitArray(bool bitArray[8], int rule) {

        //TODO: Task 1 - write the setBitArray() function

        // Check for valid rule (0-255)
        if (rule < 0 || rule > 255)
        {
            return false;
        }

        // Convert decimal (rule#) -> (8-bit binary#)
        for (int i = 0; i < 8; i++)
        {
            bitArray[i] = rule % 2;
            rule = rule / 2;
        }

        return true;
}

//convert a 3-bit state array to its 
//associated index of the rule# bit array
//   ex: {0 0 0} -> 0
//   ex: {0 0 1} -> 1
//   ex: {1 0 1} -> 5
// return binary to decimal result
int stateToIndex(bool state[3]) {

    //TODO: Task 4 - write the stateToIndex() function

    // 3-bit binary to decimal converter
    int result = 0;

    for (int i = 0; i < 3; i++)
    {
        if (state[i] == 1)
        {
            switch (i) 
            {
                case 0:
                    result += 4;
                    break;
                case 1:
                    result += 2;
                    break;
                case 2:
                    result += 1;
                    break;
            }
        }
    }
    
    return result;
}

//Update the state array for each cell in the world array based on the
//current status of active for the nearby [left,me,right] cells
//note: world is assumed periodic/cyclic,
//with front-to-back and back-to-front wrapping 
void setStates(cell world[WORLD_SIZE]) {

    //TODO: Task 5 - write the setStates() function

    // For each world (row of 65 cells)
    // set active status
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        if (i == 0)
        {
            world[i].state[0] = world[WORLD_SIZE - 1].active;
            world[i].state[1] = world[i].active;
            world[i].state[2] = world[i + 1].active;
        }
        else if (i == WORLD_SIZE - 1)
        {
            world[i].state[0] = world[i - 1].active;
            world[i].state[1] = world[i].active;
            world[i].state[2] = world[0].active;
        }
        else
        {
            world[i].state[0] = world[i - 1].active;
            world[i].state[1] = world[i].active;
            world[i].state[2] = world[i + 1].active;
        }
        
    }

    return;
}

//evolve each cell's active status to the next generation 
//  using its state array
//ruleBitArray contains the 8-bits for the rule#, 
//  stored in reverse order
void evolveWorld(cell world[WORLD_SIZE], bool ruleBitArray[8]) {

    //TODO: Task 7 - write the evolveWorld() function

    // Determine the next generations state 
    bool nextState[WORLD_SIZE];

    for (int i = 0; i < WORLD_SIZE; i++)
    {
        int index = stateToIndex(world[i].state);
        nextState[i] = ruleBitArray[index];
    }
    
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        world[i].active = nextState[i];
    }
    setStates(world);

    return;
}

// Reverses bit array
// Paramater: 8-bit binary array stored backward
void reverseBitArray(bool bitArray[8])
{
    const int BIT_SIZE = 8;
    for(int i = 0; i < BIT_SIZE / 2; i++)
    {
        int tmp;
        tmp = bitArray[i];
        bitArray[i] = bitArray[BIT_SIZE - 1 - i];
        bitArray[BIT_SIZE - 1 - i] = tmp;
    }
}

// Prints bit array for rule # in correct binary format
// Paramaters: 8-bit binary array,
//             user inputed rule #
void printBitArray(bool bitArray[8],int rule)
{
    const int BIT_SIZE = 8;
    printf("The bit array for rule #%d is ", rule);
    for(int i = 0; i < BIT_SIZE; i++)
    {
        printf("%d", bitArray[i]);
    }
    printf("\n");
}

// Prints all possible evolution states 
// Parameter: 8-bit binary array
void printEvolutionCellStates(bool bitArray[8])
{
    const int BIT_SIZE = 8;
    printf("The evolution of all possible states are as follows:\n");
    printf("|***|   |** |   |* *|   |*  |   | **|   | * |   |  *|   |   |\n");
    char* emptySpace = " ";
    printf("%s", emptySpace);
    for(int i = 0; i < BIT_SIZE; i++)
    {
        if(bitArray[i] == 1)
        {
            printf("|*|");
        }
        else
        {
            printf("| |");
        }
        printf("%-5s", emptySpace);
    }
    printf("\n");
}

// Takes in parameters bitArray and rule to reset
// the bitArray to its original format before being reversed
// i.e {0,0,0,0,0,1,1,1} -> {1,1,1,0,0,0,0,0}
void resetBitArray(bool bitArray[], int rule)
{
    for (int i = 0; i < 8; i++)
    {
        bitArray[i] = rule % 2;
        rule = rule / 2;
    }
}

int main() {
    cell world[WORLD_SIZE];

    printf("Welcome to the Elementary Cellular Automaton!\n");

    //TODO: Task 2 - read in a valid rule# and
    //      generate the rule's 8-bit rule bit array 
    //      print the bit array in correct binary number order
    int rule;
    bool bitArray[8];

    printf("Enter the rule # (0-255): ");
    scanf("%d", &rule);
    
    // Check for valid rule # and convert it to an 8 bit binary # (reversed)
    while(!(setBitArray(bitArray, rule)))
    {
        printf("Enter the rule # (0-255): ");
        scanf("%d", &rule);
    }

    reverseBitArray(bitArray);

    printBitArray(bitArray, rule);

    //TODO: Task 3 - use the rule bit array to report the evolution 
    //      step for all possible cell states.
    //      follow the format of the sample output exactly
    printEvolutionCellStates(bitArray);

    //TODO: Task 6 - read in the total number of generation evolution 
    //      steps from the user and initialize the world with ONLY the 
    //      middle cell active, all other cells should be inactive; 
    //      make sure to set the state array for each cell.

    int generations;

    printf("Enter the number of generations: ");
    scanf("%d", &generations);
    printf("\n");
    printf("Initializing world & evolving...\n");

    // Initialize the first generation
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        if (i == WORLD_SIZE / 2)
        {
            world[i].active = true;
            printf("*");
        }
        else
        {
            world[i].active = false;
            printf(" ");
        }
    }

    setStates(world);
    printf("\n");
    
    resetBitArray(bitArray, rule);
    
    //TODO: Task 8 - evolve the world the user-specified number  
    //      of generations, printing each active cell as '*' and
    //      each non-active cell as ' ' (whitespace) after each
    //      evolution step to the next generation

   // For each generation (1 less since 0 generation is already initialized) 
   // evolve the world based on the 8-bit rule.
   // print '*' for active cells and ' ' for inactive cells
   for (int i = 0; i < generations - 1; i++)
   {
        evolveWorld(world, bitArray);
        for(int j = 0; j < WORLD_SIZE; j++)
        {
            printf("%c", world[j].active ? '*' : ' ');
        }
        printf("\n");
   }

    return 0;
}

