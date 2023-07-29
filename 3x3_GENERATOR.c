#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

int RandomNumber(); //This is a function that generates a random number from an array of numbers from 1 to 9. 
void GetNumber(); //This function GetNumber() is responsible for getting input from the user to fill the empty cells of the Sudoku grid.
void PrintSudoku(); //This function PrintSudoku() is used to print the current state of the Sudoku grid
void PrintBorder(); //This function PrintBorder() is used to print a horizontal border to separate different sections of the output, respectively.

int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // Holds the numbers 1 to 9 in order. This array is used to ensure that each number appears exactly once in the Sudoku grid.
int sudoku[3][3] = {{0, 0, 0}, //Each element of the array is initialized to 0,
                    {0, 0, 0}, //indicating that the corresponding cell in the grid is currently empty.
                    {0, 0, 0}}; 

int main() {
    int difficulty[3] = {6, 4, 2}; //Each element represents the number of random numbers that will be inserted into the Sudoku grid at the beginning of the game for different difficulty levels. 
    char tryAgain; //Declares a character variable will store the user's choice to play the game again or not.
    char username[20]; //Declares a character array username with 20 elements that will store the user's name.
    time_t startTime, endTime; //declares two variables that will be used to store the start and end time of the game respectively. 
    int userDiff;
    char confirm;
    
    PrintBorder();

    printf("<<Welcome to SudoKOOL!>>\n\n");
    printf("Please enter the player's name: "); //The program will ask the player's name.
    gets(username);

    printf("To play SudoKool:\n"); //Instruction on how to play in the program.
    printf("\n\t1. First: Select a difficulty level:\n\t\ta). EASY has 6 random given numbers\n\t\tb). NORMAL has 4 random given numbers\n\t\tc). HARD has 2 random given numbers");
    printf("\n\t2. Select a random cell in the grid and insert a number from the array of numbers 1 to 9, as long as that number hasn't already been used in the grid");
    printf("\n\t3. Repeat this process until the required number of numbers have been inserted.\n");

    do{ //The program then enters a do-while loop that allows the user to play multiple games.
        do {
            PrintBorder(); ////Call PrintBorder() to print a horizontal border.
            printf("Please, select the game difficulty level:\n"); //The user is prompted to select the game difficulty level, 
            printf("[1] EASY\n[2] NORMAL\n[3] HARD\nSELECT THE DIFFICULTY: "); //with options for easy, normal, and hard levels.
            if (scanf("%d", &userDiff) != 1 || userDiff < 1 || userDiff > 3) { //The input is validated to ensure that it is a number between 1 and 3. 
                printf("\nINVALID INPUT! Please enter only 1, 2, or 3.\n"); //If the input is not valid, the user is prompted to enter valid input
                while (getchar() != '\n')
                    continue;
            } 
            else {
                printf("\nYou have selected %s", (userDiff == 1 ? "EASY" : userDiff == 2 ? "NORMAL" : "HARD")); //If the input is valid, the switch statement is used to print the difficulty level selected by the user.
                
                printf(".\nConfirm the game difficulty level. Enter [Y] to Continue and [N] to back to Select Difficulty Level: "); 
                scanf(" %c", &confirm);

                if (confirm == 'Y' || confirm == 'y') { //If the user confirms their selection by typing 'Y' or 'y', a message is printed indicating that the game is starting
                    printf("\nGreat! Let's start the game. TIME IS TICKING!\n");
                    break;
                }
                else if (confirm == 'N' || confirm == 'n') //If the user chooses to go back and select a different difficulty level by typing 'N' or 'n', a message is printed indicating that they will be redirected to select the difficulty level again.
                    printf("\nYou'll be redirecting in SELECT THE DIFFICULTY, choose again.\n");
                else 
                    printf("\nINVALID INPUT! Please enter only [Y] or [N].\n"); //If the user enters an invalid input for confirmation, a message is printed indicating that they should enter only 'Y' or 'N'.
                
            }
        } while (1); //The loop then starts again, prompting the user to select the game difficulty level.

        for (int i = 0; i < difficulty[userDiff - 1]; i++){ //Once a valid difficulty level has been selected, 
            int row, column, number; //The program enters a for loop that runs a certain number of times based on the selected difficulty level.
            number = RandomNumber();
            
            do { //The loop generates a random number and selects a random location on the Sudoku grid that has not already been filled in. It then places the random number at that location,
                row = rand() % 3;
                column = rand() % 3;
            } while (sudoku[row][column] != 0);

            sudoku[row][column] = number; //The random number is placed at that location in the grid.
        }

        PrintSudoku();  //After the loop has finished generating numbers and placing them on the grid, the PrintSudoku() function is called to display the partially filled-in grid to the user.

        time(&startTime); //The program records the end time of the game using the time() function,
        GetNumber(); //GetNumber() function which prompts the user to enter numbers for the empty cells until the entire grid is filled.      
        time(&endTime); 

        double timeDiff = difftime(endTime, startTime); //Calculates the difference between the start and end times using the difftime() function. 

        printf("\nCongratulations, Mr/Ms. %s! You completed the Sudoku puzzle in %.2f seconds.\n", username, timeDiff); //Provides the user a message if they completed the Sudoku grid.

        do{ //Prompts the user to play again by displaying a message and accepting input.
            PrintBorder(); //Call PrintBorder() to print a horizontal border.
            printf("Mr/Ms. %s, would you like to try again? (Y/N): ", username);
            scanf(" %c", &tryAgain);

            tryAgain = toupper(tryAgain);

        } while (tryAgain != 'Y' && tryAgain != 'N');

        if (tryAgain == 'Y'){ //If the user chooses to play again, the program clears the Sudoku grid by setting all values to 0.
            for (int i = 0; i < 9; i++){
                numbers[i] = i + 1;
                if (i > 3)
                    continue;

                for (int j = 0; j < 3; j++)         
                    sudoku[i][j] = 0;                
            }
        }
    } while (tryAgain == 'Y'); //The program then repeats the outer do-while loop to begin a new game.

    printf("\nThank you for using our program, Mr/Ms. %s. Come again!", username); // If the user chooses not to play again, the program displays a message and exits.
    PrintBorder(); //Call PrintBorder() to print a horizontal border.
    
    return 0;
}

int RandomNumber(){
    srand(time(NULL)); //srand() function ensures that each time the program runs, the random numbers generated will be different.

    int index, number;

    do { //the function generates a random index between 0 and 8 using the rand() function, and uses this index to select a number from the numbers array.
        index = (rand() % 9);
        number = numbers[index];
    } while (number == 0); //checks if the selected number is equal to 0. If it is, the function continues to generate a new random index and select a new number until it finds a non-zero number.

    numbers[index] = 0; //Once a non-zero number is selected, the function sets the corresponding element of the numbers array to zero to indicate that this number has been used and should not be selected again.

    return number; //returns the selected number to be used in the Sudoku puzzle.
}

void GetNumber(){
    int tempValue, count = 1;

    for (int i = 0; i < 3; i++) { //Uses two nested for loops to iterate through each element of the 3x3 Sudoku grid.
        for (int j = 0; j < 3; j++) {
            if (sudoku[i][j] == 0) { //For each empty grid space (denoted by a 0)

                do { // repeat indefinitely
                    printf("Enter a number for the row [%d] and column [%d]: ", i + 1, j + 1); // prompts the user to input a number for that space using printf() and scanf() and store the number.

                    if (scanf("%d", &tempValue) != 1 || tempValue < 1 || tempValue > 9) { // check if input is a number
                        printf("Invalid input. Please enter a number between 1 and 9.\n\n");

                        while (getchar() != '\n') 
                            continue;
                    }
                    else if (numbers[tempValue - 1] == 0) // check if number is already used
                        printf("Number already used in the grid.\n\n");
                    else 
                        break;
    
                } while (1);
            
                numbers[tempValue - 1] = 0; //it updates the numbers[] array to indicate that the number is no longer available,
                sudoku[i][j] = tempValue; //sets the sudoku array at the corresponding position to the input value. 
                PrintSudoku(); //prints the updated Sudoku grid using PrintSudoku() function.
            }   
        }
    }
}


void PrintSudoku(){ 
    PrintBorder(); //Call PrintBorder() to print a horizontal border.

    for (int i = 0; i < 3; i++){
        printf("\t---------------\n\t");
        for (int j = 0; j < 3; j++){
            printf("| %d |", sudoku[i][j]);
        }
        printf("\n");
    }
    printf("\t---------------\n");
}

void PrintBorder(){ //Print a horizontal border with equal signs, with "<=" and "=>" at the beginning and end respectively to provide a decorative border for the output.
    printf("\n<==================================================>\n\n");
}
