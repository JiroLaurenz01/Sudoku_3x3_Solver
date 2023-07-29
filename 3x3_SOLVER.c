#include <stdio.h>
#include <ctype.h>

void GetNumber(int dataNums); // This is a function responsible for getting the input from the user to fill in numbers in the Sudoku grid.
void SudokuSolver(); // This is a function that solves the Sudoku puzzle by filling in the remaining empty cells in the grid.
void PrintSudoku();// This is a function that prints the current state of the Sudoku grid.
void PrintBorder(); // This is a function that prints a horizontal border with equal signs, with "<=" at the beginning and "=>" at the end.

int sudokuElements[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; //sudokuElements is an integer array that stores the numbers 1 to 9. It represents the possible values that can be inserted into the Sudoku grid.
int sudoku[3][3] = {{0, 0, 0}, //sudoku is a 2-dimensional array with dimensions 3x3. It represents the Sudoku grid and is initially filled with zeros.
                    {0, 0, 0},
                    {0, 0, 0}};

int main()
{
    int dataNums = 1; // This variable is an integer named dataNums initialized to 1. It is used to store the number of Sudoku elements (numbers) the user wants to input.
    char username[20]; //This variable is a character array (string) named username with a size of 20 characters. It is used to store the name of the player.
    int tries = 0; //This variable is an integer named tries initialized to 0. It is used to keep track of the number of attempts the user has made for a particular action.
    const int maxTries = 3; //This variable is a constant integer named maxTries initialized to 3. It is used to define the maximum number of tries allowed for a specific action.
    char tryAgain; //This variable is a character named tryAgain. It is used to store the user's choice of whether to try the game again or not.
    char confirmChoice; //This variable is a character named confirmChoice. It is used to store the user's choice of whether to confirm a particular action or not.

    PrintBorder();
    
    printf("<<Welcome to SudoKOOL!>>\n\n");
    printf("Please enter the player's name: "); //The program will ask the player's name.
    gets(username);

    printf("To play SudoKool:\n"); //Instruction on how to play in the program.
    printf("\n\t1. Choose how many number you want to input, minimum of 2 and maximum of 6.");
    printf("\n\t2. Select the row and column where you would like to place your desired input number.");
    printf("\n\t3. Enter the number on [1 - 9] you want to insert. Number must not be repeated");        
    printf("\n\t4. Repeat this process until the required number of input have been inserted.\n"); // 1. GUMASING

    PrintBorder(); // This function is called to print a horizontal border, providing a decorative separator.
    do{ // The outermost do-while loop is used to repeat the entire game until the player chooses not to play again.
            while (dataNums < 2 || dataNums > 6) { // The purpose of this loop is to validate and ensure that the user enters a valid number of Sudoku elements to input.
            printf("MINIMUM: 2 | MAXIMUM: 6\nEnter the number of sudoku elements you want to input: "); // This line prints a message to prompt the user to enter the number of Sudoku elements they want to input.
            if (scanf("%d", &dataNums) != 1 || dataNums < 2 || dataNums > 6) { //This condition checks if the input read by scanf is not an integer or if it is less than 2 or greater than 6. If the condition is true, it means the input is invalid. The block of code inside this if statement will be executed.
                tries++;
                if (tries >= maxTries) { // This condition checks if the number of tries has reached or exceeded the maximum allowed tries (maxTries).
                    PrintBorder(); //This function is called to print a horizontal border.
                    printf("Mr/Ms. %s, You have exceeded the maximum number of tries. Please try again later.\n", username); //If the condition is true, it means the user has exceeded the maximum number of tries. The block of code inside this if statement will be executed.
                    return 1;  // Exit the program
                }
                PrintBorder();
                printf("Mr/Ms. %s, Invalid Input. Enter a number between 2 and 6 only.\n\n", username);
                while (getchar() != '\n');  // Clear the input buffer
            }
        }
    
        PrintSudoku(); // 2. ORDE // The PrintSudoku() function is responsible for printing the Sudoku grid in a formatted manner, separating each row and column with horizontal lines and using vertical bars to enclose the individual cell values.

        do { //Inside the outer loop, the program prompts the user to confirm their choice of the number of Sudoku elements they want to input.
            printf("\nAre you sure you want to input %d sudoku elements? (Y/N): ",dataNums); // The inner do-while loop is used to validate the user's confirmation choice (Y or N). 
            scanf(" %c", &confirmChoice);                                                   // It continues to prompt the user until a valid input is provided.
            confirmChoice = toupper(confirmChoice);
            if (confirmChoice != 'Y' && confirmChoice != 'N') {
                printf("Invalid input. Please enter 'Y' or 'N'.\n");
            }
            else if (confirmChoice == 'N') { //If the user chooses not to proceed (confirmChoice == 'N'), the program resets the number of Sudoku elements and asks the user to input a new value within a valid range (2 to 6).
                printf("\nMr/Ms. %s, You have chosen to undo your previous choice.\n", username);
                dataNums = 0;  // Reset the number of sudoku elements.

                PrintBorder(); // Go back to the number of sudoku elements selection.
                tries = 0;
                while (dataNums < 2 || dataNums > 6) {
                    printf("MINIMUM: 2 | MAXIMUM: 6\nEnter the number of sudoku elements you want to input: ");
                    if (scanf("%d", &dataNums) != 1 || dataNums < 2 || dataNums > 6) {
                        tries++;
                        if (tries >= maxTries) {
                            PrintBorder();
                            printf("Mr/Ms. %s, You have exceeded the maximum number of tries. Please try again later.\n", username);
                            return 1;  // Exit the program.
                        }
                        PrintBorder();
                        printf("Mr/Ms. %s, Invalid Input. Enter a number between 2 and 6 only.\n\n", username);
                        while (getchar() != '\n');  // Clear the input buffer..
                    }
                }

                PrintSudoku(); 
            }
        } while (confirmChoice != 'Y'); // 3. SEVA

        PrintSudoku(); // After a valid number of Sudoku elements is entered, the PrintSudoku() function is called to display the Sudoku grid.
        GetNumber(dataNums); // The GetNumber(dataNums) function is then called to prompt the user to input the Sudoku numbers according to the specified number of elements.
        SudokuSolver(); // The SudokuSolver() function is called to solve the Sudoku puzzle based on the provided numbers.
        printf("\nCongratulations, Mr/Ms. %s! You completed the Sudoku puzzle.\n", username); //Once the puzzle is solved, a congratulatory message is displayed.
        
        do { //The program then prompts the user to choose whether they want to try again (Y or N) using a similar do-while loop for validation.
            PrintBorder();
            printf("Mr/Ms. %s, would you like to try again? (Y/N): ", username); // If the user chooses to play again (tryAgain == 'Y'), 
            scanf(" %c", &tryAgain);                                            // the Sudoku grid is cleared by resetting the values to 0 and the program asks for a new number of Sudoku elements.
            tryAgain = toupper(tryAgain);

            if (tryAgain != 'Y' && tryAgain != 'N') // If the user input a choices not in the choices it will print Invalid and only enter what is in the choices.
                    printf("Invalid input. Please enter only Y or N.\n");
                    
        } while (tryAgain != 'Y' && tryAgain != 'N');

        if (tryAgain == 'Y') { // If the user chooses to play again, the program clears the Sudoku grid by setting all values to 0.
            for (int i = 0; i < 9; i++) {
                sudokuElements[i] = i + 1;
                if (i > 3)
                    continue;

                for (int j = 0; j < 3; j++)
                    sudoku[i][j] = 0;
            }

            PrintSudoku();
            dataNums = 0; // Clear the number of Sudoku elements.
            confirmChoice = 'N';
        }
    
    } while (tryAgain == 'Y');
    
    printf("\nGoodbye, Mr/Ms. %s! Thank you for playing SudoKOOL. Come back soon!\n", username); // If the user chooses not to play again (tryAgain == 'N'), 
    PrintBorder();  
                                                                                // a goodbye message is displayed, and the program exits.
    return 0;
} 

void GetNumber(int dataNums){ //The function takes an argument dataNums, which represents the number of Sudoku elements to be inputted.
    int row, column, tempValue; // It declares local variables row and column to store the user's chosen row and column values, respectively, and tempValue to store the temporary Sudoku value.
    static int inputCounter = 0; // The inputCounter variable is declared as a static variable to keep track of the number of inputs.

    if (dataNums == 0) //If dataNums is 0, indicating that all the Sudoku elements have been inputted, the function returns, effectively ending the recursive function calls.
        return;

    PrintBorder(); //The PrintBorder function is called to print a border line before prompting for user input.

    do { //The function enters a do-while loop, which prompts the user to select a location (row and column) for the Sudoku element input. 
        do { //Within the loop, the user is asked to input the row number, which must be between 1 and 3. If the input is invalid, an error message is displayed, and the loop continues until a valid input is provided.
            while (1) { //The user is asked to input the row number, which must also be between 1 and 3.
                printf("Select the location, Enter the number on what row [1 - 3] (Input %d): ", inputCounter + 1); //The row variables are adjusted to be zero-based by decrementing them by 1.
                if (scanf("%d", &row) != 1 || row < 1 || row > 3) {  // Invalid inputs are handled similarly to the previous inputs, with appropriate error messages and input validation.
                    printf("Invalid input. Please enter a number between 1 and 3.\n");
                    while (getchar() != '\n'); // Clear input buffer
                }
                else
                    break; // Valid input, exit the loop
            }
        } while (row < 1 || row > 3);

        do {
            while (1) { //The user is asked to input the column number, which must also be between 1 and 3.
                printf("\nSelect the location, Enter the number on what column [1 - 3] (Input %d): ", inputCounter + 1); //The column variables are adjusted to be zero-based by decrementing them by 1.
                if (scanf("%d", &column) != 1 || column < 1 || column > 3) { // Invalid inputs are handled similarly to the previous inputs, with appropriate error messages and input validation.
                    printf("Invalid input. Please enter a number between 1 and 3.\n");
                    while (getchar() != '\n'); // Clear input buffer
                }
                else
                    break; // Valid input, exit the loop
            }
        } while (column < 1 || column > 3);

        row--; column--;

        if (sudoku[row][column] != 0) //If the position in the Sudoku grid (sudoku[row][column]) is already occupied (non-zero value), an error message is displayed, and the loop continues until an empty position is selected.
            printf("\nThe position is already occupied. Input another row and column.\n");

    } while (sudoku[row][column] != 0);

    do {
        while (1) {
            printf("\nEnter the number on [1 - 9] you want to insert (Input %d): ", inputCounter + 1); // The function then prompts the user to enter the Sudoku value they want to insert, which must be between 1 and 9. 
            if (scanf("%d", &tempValue) != 1 || tempValue < 1 || tempValue > 9) { // Invalid inputs are handled similarly to the previous inputs, with appropriate error messages and input validation.
                printf("Invalid input. Please enter a number between 1 and 9.\n"); 
                while (getchar() != '\n'); // Clear input buffer
            }
            else
                break; // Valid input, exit the loop
        }

        if (sudokuElements[tempValue - 1] == 0) // If the chosen value (tempValue) has already been used in the Sudoku (marked as 0 in sudokuElements), an error message is displayed, and the loop continues until a valid value is chosen.
            printf("Number %d has already been used in the sudoku.\n", tempValue);

    } while (sudokuElements[tempValue - 1] == 0);

    sudokuElements[tempValue - 1] = 0; // Once a valid value is chosen, the tempValue is marked as used by setting the corresponding index in sudokuElements to 0, 
    sudoku[row][column] = tempValue;   // and the value is assigned to the selected position in the Sudoku grid (sudoku[row][column]).

    PrintSudoku(); // The PrintSudoku function is called to display the updated Sudoku grid.

    inputCounter++; // The inputCounter is incremented to keep track of the number of inputs made.
    GetNumber(dataNums - 1); //The function calls itself recursively with dataNums - 1 as the argument to continue the process of getting the remaining Sudoku elements.
} 
void SudokuSolver(){ // The SudokuSolver function, which is responsible for solving the Sudoku puzzle.
    int count = 0; //The function declares a local variable count to keep track of the index in sudokuElements while filling in the empty positions in the Sudoku grid.

    for (int i = 0; i < 3; i++) //The function enters a nested for loop to iterate over each position in the Sudoku grid (sudoku[3][3]).
        for (int j = 0; j < 3; j++)
            if (sudoku[i][j] == 0){ //Inside the if statement, a while loop is used to find the next available value in sudokuElements that hasn't been used yet.
                while (sudokuElements[count] == 0 && count < 9)
                    count++; //The loop increments count until it finds a non-zero value in sudokuElements or reaches the end of the array.

                sudoku[i][j] = sudokuElements[count]; //Once a non-zero value is found, it is assigned to the current empty position in the Sudoku grid (sudoku[i][j]).
                count++; //The count variable is incremented to move to the next available value in sudokuElements.
            }  // The process continues until all the empty positions in the Sudoku grid have been filled.

    PrintSudoku(); // The PrintSudoku function is called to display the solved Sudoku grid.
} 

void PrintSudoku(){ 
    PrintBorder(); //Call PrintBorder() to print a horizontal border.

    for (int i = 0; i < 3; i++){  // The code then enters a nested loop with the outer loop iterating three times and the inner loop also iterating three times.
        printf("\t---------------\n\t"); // This is done to iterate through a 3x3 section of the Sudoku board.
        for (int j = 0; j < 3; j++){ // The inner loop iterates three times to print the content of each cell within the section. It uses the printf function to print the value stored in the sudoku array at the current position (i, j). 
            printf("| %d |", sudoku[i][j]); // The value is printed between two vertical bars (pipes) for visual separation.
        }                                   // Note that sudoku is assumed to be a two-dimensional integer array containing the values of the Sudoku board.                                
        printf("\n"); // After printing the three cells in the current row of the section, a new line character is printed to move to the next row.
    }
    printf("\t---------------\n"); // The code then prints another horizontal line to separate the last row of the section.
} 

void PrintBorder(){ //Print a horizontal border with equal signs, with "<=" and "=>" at the beginning and end respectively to provide a decorative border for the output.
    printf("\n<==================================================>\n\n");
}