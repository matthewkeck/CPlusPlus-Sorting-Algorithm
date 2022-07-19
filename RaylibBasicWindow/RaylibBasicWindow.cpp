
/*******************************************************************************************
*
*   raylib [core] examples - Mouse wheel input
*
*   This test has been created using raylib 1.1 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

// Matthew R Keck 7/18/2022

#define _USE_MATH_DEFINES

#include "raylib.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <ctime>
#include <cstdlib>


using namespace std;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------


// class stores the start and end positions of the lines generated in the spiral aswell as radius, angles, colors, index in the randomized array, and the length of
// the array
class Line {
    
// private varables in the class
private:
    float startPositionX;
    float startPositionY;

    float endPositionX;
    float endPositionY;

    float red = 0;
    float green = 0;
    float blue = 0;
    float other = 255;

    float theta = 0;
    float radius = 0;
    float thick;

    int array_length;
    
// geters and seters for private varables
public:

    int index;

    void setArrayLength(int a) { array_length = a; }

    void setStartX(int x) { startPositionX = x; }
    void setStartY(int y) { startPositionY = y; }

    void setEndX(int x) { endPositionX = x; }
    void setEndY(int y) { endPositionY = y; }

    void setRed(float r) { red = r; }
    void setBlue(float b) { blue = b; }
    void setGreen(float g) { green = g; }
    void setOther(float o) { other = o; }

    void setTheta(float t) { theta = t; }
    void setRadius(float r) { radius = r; }
    void setThick(float th) { thick = th; }

    int getArrayLength() { return array_length; }

    float getStartX() { return startPositionX; }
    float getStartY() { return startPositionY; }

    float getEndX() { return endPositionX; }
    float getEndY() { return endPositionY; }

    float getRed() { return red; }
    float getBlue() { return blue; }
    float getGreen() { return green; }
    float getOther() { return other; }

    float getTheta() { return theta; }
    float getRadius() { return radius; }
    float getThick() { return thick; }
};

// global varables for desplaying the selected sort algorithm and allowing the user to skip animations
static const char* algorithm_names[] = { "Bubble Sort", "A Sort", "Quick Sort", "Merge Sort" };
int name_selector = 0;

bool stop_animation = false;

// function animates the randomization and sorting of the spiral by drawing the array on the screen
void generate_spiral(Line spiral[], int size_of_array, Vector2 start, Vector2 end) {
    BeginDrawing();
    ClearBackground(BLACK);

    // draws the instructions for the user
    DrawText(TextFormat("Left Click To Change Sort :"), 50, 100, 20, WHITE);
    DrawText(algorithm_names[name_selector], 350, 100, 20, WHITE);
    DrawText(TextFormat("Use the Scroll Wheel To Increase Or Decrease The Number Of Lines"), 50, 50, 20, WHITE);

    DrawText(TextFormat("To Randomize Press : R"), 50, 950, 20, WHITE);
    DrawText(TextFormat("To Sort Press : S"), 950, 950, 20, WHITE);
    DrawText(TextFormat("To Stop Animation Press : F"), 500, 950, 20, WHITE);
    
    // iterates through the array keeps the radus lengeth and changes the angle by recalculateing the end position based on the position in the array
    for (int i = 0; i < size_of_array; i++) {
        Color color = { spiral[i].getRed(), spiral[i].getGreen(), spiral[i].getBlue(), spiral[i].getOther() };
        end = { float((cos(i * spiral[i].getTheta()) * spiral[i].getRadius()) + spiral[i].getStartX()), float((sin(i * spiral[i].getTheta()) * spiral[i].getRadius()) + spiral[i].getStartY()) };
        DrawLineEx(start, end, spiral[i].getThick(), color);
    }
    EndDrawing();
}


void sort_func(Line spiral[], int size_of_array, Line* my_pointer, Vector2 start, Vector2 end) { // sort function to sort the radiuses from high to low

    Line largest_radius, prev_radius; // local varbles to save the largest radiuses and the prev radiuses

    for (int i = 0; i < size_of_array; i = i + 1) { // for loop to iterate the size of radiuses and increment by one
        my_pointer = &spiral[i]; // sets my_pointer to where i is in the array
        largest_radius = *my_pointer; // sets largest radiuses equal to temp pointer at i

        for (int j = i; j < size_of_array; j = j + 1) { // for loop starts at i and iterates the size of radiuses again and inrement by one

            if (largest_radius.getRadius() < my_pointer->getRadius()) { // if statment to compaire largest radiuses to radiuses if pointer is smaller then largest radiuses it skips the steps

                prev_radius = largest_radius; // saves previous largest radiuses
                largest_radius = *my_pointer; // grabs new largest radiuses
                *(my_pointer - j + i) = largest_radius; // moves largest radiuses to the top of the array
                *my_pointer = prev_radius; // radiuses pointer takes the smaller radiuses and moves it to where the larger radiuses was

                if (IsKeyPressed(KEY_F)) {
                    stop_animation = true;
                }

                if (stop_animation == false) {
                    generate_spiral(spiral, size_of_array, start, end);
                }
            }

            my_pointer++; // increments pointer
        }
    }
}

// bubble sorting algorithm
void bubble_sort(Line spiral[], int size_of_array, Vector2 start, Vector2 end) {
    // prev temp allows swap to happen 
    Line prev_temp;
    // comparison determins if the array has been sorted
    int comparison;

    // loops through the size if the arrry
    for (int i = 0; i < size_of_array - 1; i = i + 1) {
        // sets the comparsion of this time through the array to zero
        comparison = 0;
        // loops through the size of the array to compary valuse
        for (int j = 0; j < size_of_array; j = j + 1) {

            // compares the values next to each other if the smaller index is smaller we swap
            if (spiral[j].getRadius() < spiral[j + 1].getRadius() && (j + 1) != size_of_array) {
                // swaping valuse
                prev_temp = spiral[j];
                spiral[j] = spiral[j + 1];
                spiral[j + 1] = prev_temp;
                // adding to comparison
                comparison++;

                // allows the user to skip animation
                if (IsKeyPressed(KEY_F)) {
                    stop_animation = true;
                }

                if (stop_animation == false) {
                    // animates changes in array
                    generate_spiral(spiral, size_of_array, start, end);
                }
                
            }

        }
        // if there were no swaps we break the loop
        if (comparison == 0) {
            break;
        }

    }
}

// quick sort function uses th quick sort algorithm to sort the radius form largest to smallest
void quick_sort(Line spiral[], int lower_bound, int upper_bound, int size_of_array, Vector2 start, Vector2 end, bool stop_animation) {

    // breaks the recursive algorithm
    if (lower_bound >= upper_bound) {
        return;
    }

    // selects the pivoit for wich valluse that are greater will be sorted on one side of the pivot and values that are smaller will be sorted to the other side
    int pivot = upper_bound;

    int left_pointer = lower_bound;
    int right_pointer = upper_bound;

    Line temp_value;

    // while statment itterates through both sides of the partition
    while (left_pointer < right_pointer) {

        // while statement compares the left side of the spiral until it finds a value that needs to be moved to the other side
        while (spiral[left_pointer].getRadius() >= spiral[pivot].getRadius() && left_pointer < right_pointer) {
            left_pointer = left_pointer + 1;
        }
        // while statement compares the right side of the spiral until it finds a value that needs to be moved to the other side
        while (spiral[right_pointer].getRadius() <= spiral[pivot].getRadius() && left_pointer < right_pointer) {
            right_pointer = right_pointer - 1;
        }

        // once values are found that need to be swaped the next three lines of codes swap them
        temp_value = spiral[right_pointer];
        spiral[right_pointer] = spiral[left_pointer];
        spiral[left_pointer] = temp_value;
        
        // if statements allow the user to stop the animation form playing
        if (IsKeyPressed(KEY_F)) {
            stop_animation = true;
        }

        if (stop_animation == false) {
            // function call animates the changes to the spiral
            generate_spiral(spiral, size_of_array, start, end);
        }
    }

    // swaps the partition to the correct side
    temp_value = spiral[left_pointer];
    spiral[left_pointer] = spiral[pivot];
    spiral[pivot] = temp_value;

    // determens the bounds of the recuresive call
    int index = left_pointer;

    // function calls itself tell the array is sorted
    quick_sort(spiral, lower_bound, index - 1, size_of_array, start, end, stop_animation);
    quick_sort(spiral, index + 1, upper_bound, size_of_array, start, end, stop_animation);

}

// merge function takes two smaller arrays sorts the contents while merging it into a larger array
void merge(Line* current_array, int size_of_array, Line* left_array, int left_size, Line* right_array, int right_size,
    Vector2 start, Vector2 end, Line* spiral, int ArrayLength) {

    // iterators for right left and current arrays
    int i = 0, j = 0, k = 0;

    // lowerbound helps us to determine the position fo the merged array in the original array so we can animate the algorithm correctly
    int lowerbound = current_array[0].index;

    // iterates tell it has gone through both left and right arrays
    while (i < left_size && j < right_size) {
        // compares the radiuses of the left array with the right array
        if (left_array[i].getRadius() >= right_array[j].getRadius()) {
            // if the values in the left arra grater they are moved into the position in merged array
            current_array[k] = left_array[i];

            // if statment stops an animation bug that occures on the final merging
            if (size_of_array != ArrayLength) {
                // copys the changes made to the main array
                spiral[lowerbound + k + 1] = current_array[k];
            }
            

            if (IsKeyPressed(KEY_F)) {
                stop_animation = true;
            }

            if (stop_animation == false) {
                generate_spiral(spiral, ArrayLength, start, end);
            }

            // increases the iterator for the left array
            i++;
        }
        // same process but if the right array is greater
        else {
            current_array[k] = right_array[j];

            if (size_of_array != ArrayLength) {
                spiral[lowerbound + k + 1] = current_array[k];
            }

            if (IsKeyPressed(KEY_F)) {
                stop_animation = true;
            }

            if (stop_animation == false) {
                generate_spiral(spiral, ArrayLength, start, end);
            }

            j++;
        }
        // increass the merged array iterator for the next positon to be compared
        k++;
    }

    // while statment moves the remaining lines in the left array to the merged array now that the valuse that need to be sorted have been
    while (i < left_size) {
        current_array[k] = left_array[i];
        
        if (size_of_array != ArrayLength) {
            spiral[lowerbound + k + 1] = current_array[k];
        }

        if (IsKeyPressed(KEY_F)) {
            stop_animation = true;
        }

        if (stop_animation == false) {
            generate_spiral(spiral, ArrayLength, start, end);
        }

        i++;
        k++;
    }
    // while statment moves the remaining lines in the right array to the merged array now that the valuse that need to be sorted have been
    while (j < right_size) {
        current_array[k] = right_array[j];
        
        if (size_of_array != ArrayLength) {
            spiral[lowerbound + k + 1] = current_array[k];
        }


        if (IsKeyPressed(KEY_F)) {
            stop_animation = true;
        }

        if (stop_animation == false) {
            generate_spiral(spiral, ArrayLength, start, end);
        }

        j++;
        k++;
    }
    
}

// function uses the merge sort algortim to sort the spiral
void merge_sort(Line* current_array, int size_of_array, Vector2 start, Vector2 end, Line* spiral, int ArrayLength) {

    // if statment to break the recursive algorithm form diveding into arrays that are smaller then 2
    if (size_of_array < 2) {
        return;
    }

    // determens the index that we will split the current array in two 
    int mid_index = size_of_array / 2;

    // instancates the two arrays with the correct lengths
    Line* left_array = new Line[mid_index];
    Line* right_array = new Line[size_of_array - mid_index];

    // loops move the data from the old array to the two new arrays
    for (int i = 0; i < mid_index; i++) {
        left_array[i] = current_array[i];
    }

    for (int i = mid_index; i < size_of_array; i++) {
        right_array[i - mid_index] = current_array[i];
    }

    // calls itself recursivly tell the array is spillt into a bunce of arrays of length one
    merge_sort(left_array, mid_index, start, end, spiral, ArrayLength);
    merge_sort(right_array, size_of_array - mid_index, start, end, spiral, ArrayLength);

    // now that the array has been devied we merge the smaller arrays back to the larger arrays while we sort the contents of the smaller arrays
    merge(current_array, size_of_array, left_array, mid_index, right_array, size_of_array - mid_index, start, end, spiral, ArrayLength);
}

// function randomize the spiral by changing there positions in the array but keep the original radus
int randomize_spiral(Line spiral[], int size_of_array, Vector2 start, Vector2 end, int iterator) {
    Line temp;

    // iterates therough the intire array by using the while loop in main to increase the iterator vable tell it is the size of the array
    if (iterator < size_of_array) {
        // generates a random number withing the size of the array
        int random_number = rand() % size_of_array;
        // swaps the lines to differnet positions int the array
        temp = spiral[iterator];
        spiral[iterator] = spiral[random_number];
        spiral[random_number] = temp;

        // saves the index of the line in the randomized array
        spiral[iterator].index = iterator -1;
        spiral[random_number].index = random_number - 1;

        // inecreas the itterator variable
        iterator++;
    }

    // retuerns itterator
    else {
        return iterator;
    }

}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    // delecaring varables fo the screen and line position colors angles and more
    const int screenWidth = 1200;
    const int screenHeight = 1000;

    Vector2 start = { screenWidth / 2 , screenHeight / 2 };
    Vector2 end = { screenWidth / 2 , screenHeight / 2 };

    float theta = -.1;
    float prev_theta = theta;

    float red = 255;
    float green = 0;
    float blue = 0;
    float other = 255;

    int ArrayLength;
    float color_gradent;
    float alpha_gradent;
    float thick;

    // intaling the the arrays that will be sorted
    Line spiral_array[10][629];

    int array_selector = 0;

    int color_selector = -1;

    // double for loop to create all ten arrays
    for (int j = 0; j < 10; j++) {

        // determins the amount of lines in each array by dividing -2 pie by the sive of the angle
        ArrayLength = int((-2 * M_PI) / theta);

        // ditermins the change in color by dividing 255 by the amount of lines and the number of colors we want to transition two
        color_gradent = float(255) / (float(ArrayLength) / float(5));
        // ditermens the intensity of the color by the same methoed but we want the intensity of the last line to be about half of the starting line
        alpha_gradent = float(255) / float(ArrayLength) / float(2);
        // the number 1275 is the circumference of the spiral. i found this number by using the arc lenght formula
        // circumferenc is divided by the number of lines in the sipral to determin the proper thickness of each line
        thick = float(1275 / ArrayLength);

        // for loop sets the values of the lines for each spiral
        for (int i = 0; i < ArrayLength; i++) {
            // sets the color of the line
            Color color = { spiral_array[j][i].getRed(), spiral_array[j][i].getGreen(), spiral_array[j][i].getBlue(), spiral_array[j][i].getOther()};

            // sets the thickness, angle and length of the array of the line
            spiral_array[j][i].setThick(thick);
            spiral_array[j][i].setTheta(theta);
            spiral_array[j][i].setArrayLength(ArrayLength);

            // raduis is calcualted using the position in the array the angle and a constant of 60
            spiral_array[j][i].setRadius((i * theta) * 60);

            // we increment the alpha down as we progress through the array
            other -= alpha_gradent;
            spiral_array[j][i].setOther(other);
            
            // if statment determins the color we will be progressing to by increasing our selector every time the remandier of the array length divided by 5
            // reaches zero
            if (i % (ArrayLength / 5) == 0) {
                color_selector++;
            }

            // case swithch takes determins the colors we will be increaisng and decreasing
            switch (color_selector) {

                // at zero we are increasing green tell we reach a yellow color
            case 0:
                green += color_gradent;
                spiral_array[j][i].setRed(red);
                spiral_array[j][i].setGreen(green);
                break;

                // at 1 we decrease red tell we reach a zero color
            case 1:
                red -= color_gradent;
                green = 255;
                spiral_array[j][i].setGreen(green);
                spiral_array[j][i].setRed(red);
                break;

                // at 2 we increas blue tell we reach a light blue color
            case 2:
                blue += color_gradent;
                spiral_array[j][i].setGreen(green);
                spiral_array[j][i].setBlue(blue);
                break;

                // at 3 we decreas green to reach a blue color
            case 3:
                green -= color_gradent;
                blue = 255;
                spiral_array[j][i].setBlue(blue);
                spiral_array[j][i].setGreen(green);
                break;

                // at 4 we increas red to get a purple color
            case 4:
                red += color_gradent;
                spiral_array[j][i].setBlue(blue);
                spiral_array[j][i].setRed(red);
                break;
                // what ever is left we keep at a purple color
            default:
                red = 255;
                blue = 255;
                spiral_array[j][i].setBlue(blue);
                spiral_array[j][i].setRed(red);
                break;
            }

            // sets the start position to the center of the screen
            spiral_array[j][i].setStartX(screenWidth / 2);
            spiral_array[j][i].setStartY(screenHeight / 2);

            // sets the end position using the peremeteric equation for a spiral
            spiral_array[j][i].setEndX((cos(i * theta) * spiral_array[j][i].getRadius()) + spiral_array[j][i].getStartX());
            spiral_array[j][i].setEndY((sin(i * theta) * spiral_array[j][i].getRadius()) + spiral_array[j][i].getStartY());

        }
        // resets varables for the next array
        red = 255;
        green = 0;
        blue = 0;
        other = 255;
        color_selector = -1;
        theta += .01;
    }

    // timer and fram vables allow us to animate changes in the array
    float timer = 0.0f;
    int frame = 0;
    int temp_frame = 0;

    int counter = 0;
    int iterator = 0;

    // varable lets us know if the array has been randomized
    bool randomized = false;

    Line* my_pointer = NULL; // declares pointer and sets it to nothing

    InitWindow(screenWidth, screenHeight, "Matthew R Keck - Sorting Algorithms");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {


        my_pointer = &spiral_array[array_selector][0];// sets the pointer adress to spiral indice 0

        // timer equals the time the frame has been open
        timer += GetFrameTime();

        // increments the fram every .1 seconds
        if (timer >= 0.1f) {
            timer = 0.0f;
            frame += 1;
        }

        // resets the frames back to zero once it has iterated the length of the array
        frame = frame % spiral_array[array_selector]->getArrayLength();

        // allows the user to randomize the array if the array is sorted and in the correct state
        if (IsKeyPressed(KEY_R) && counter == 1) {
            counter = 6;
        }

        // allows the user to sort the array if it has been randomized and is in the correct state
        if (IsKeyPressed(KEY_S) && counter == 1 && randomized == true) {
            counter = name_selector + 2;
        }

        // alows the user to select between sorting algourtihms
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (name_selector < 3) {
                name_selector++;
            }
            // resets back to the first algorithm wonce the user has gon throuhg the whole list
            else {
                name_selector = 0;
            }
        }

        // allows the user to change between arrays that have different amount of lines
        array_selector += GetMouseWheelMove();

        // if the scrool is outside the 10 arrays we created or if it has been randomized and is not in the correct state we remove the scroll that accured
        if (array_selector > 9 || array_selector < 0 || counter != 1 || randomized == true) {
            array_selector -= GetMouseWheelMove();
        }

        // sets the upper and lower bound for quick sort algorithm
        int lower_bound = 0;
        int upper_bound = spiral_array[array_selector]->getArrayLength() - 1;

        // swicht statment determins the state in which the array is in
        switch (counter) {
            // case 0 is the start animation that animates the lines being added one at a time
        case 0:
            // calls generate function to display the array with the length being the frame
            generate_spiral(spiral_array[array_selector], frame, start, end);
            // sets the state to 1 after it is done animating
            if (frame == spiral_array[array_selector]->getArrayLength() - 1) {
                counter = 1;
            }
            break;

            // case 1 is the no changes happeing to the array state
        case 1:
            generate_spiral(spiral_array[array_selector], spiral_array[array_selector]->getArrayLength(), start, end);
            break;

            // case 2 is the buble sort animation state
        case 2:
            bubble_sort(spiral_array[array_selector], spiral_array[array_selector]->getArrayLength(), start, end);
            randomized = false;
            stop_animation = false;
            counter = 1;
            break;

            // case three is the a sort animation state
        case 3:
            sort_func(spiral_array[array_selector], spiral_array[array_selector]->getArrayLength(), my_pointer, start, end);
            randomized = false;
            stop_animation = false;
            counter = 1;
            break;

            // case 4 is the quick sort animation state
        case 4:
            quick_sort(spiral_array[array_selector], lower_bound, upper_bound, spiral_array[array_selector]->getArrayLength(), start, end, stop_animation);
            randomized = false;
            stop_animation = false;
            counter = 1;
            break;

            // case 5 is the merge sort animation state
        case 5:
            merge_sort(spiral_array[array_selector], spiral_array[array_selector]->getArrayLength(), start, end, spiral_array[array_selector], spiral_array[array_selector]->getArrayLength());
            randomized = false;
            stop_animation = false;
            counter = 1;
            break;

            // case 6 is the ranomiztaton animation state
        case 6:
            // allows the user to stop animation
            if (IsKeyPressed(KEY_F)) {
                stop_animation = true;
            }

            if (stop_animation == false) {
                generate_spiral(spiral_array[array_selector], spiral_array[array_selector]->getArrayLength(), start, end);
            }

            // if
            if (frame > temp_frame) {
                iterator = randomize_spiral(spiral_array[array_selector], spiral_array[array_selector]->getArrayLength(), start, end, iterator);
            }

            // deterimes when the array has been suffecently randomized and rests it back to the stable state of case 1
            if (iterator == spiral_array[array_selector]->getArrayLength() - 1) {
                counter = 1;
                iterator = 0;
                stop_animation = false;
            }
            randomized = true;
            temp_frame = frame;
            break;

        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
