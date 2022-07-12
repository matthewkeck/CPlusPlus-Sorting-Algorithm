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

class Line{
private:
    float startPositionX;
    float startPositionY;

    float endPositionX;
    float endPositionY;

    int red = 255;
    int green = 0;
    int blue = 0;
    int other = 255;

    float theta = 0;
    float radius = 0;
    
public:
    void setStartX(int x) { startPositionX = x; }
    void setStartY(int y) { startPositionY = y; }

    void setEndX(int x) { endPositionX = x; }
    void setEndY(int y) { endPositionY = y; }

    void setRed(int r) { red = r; }
    void setBlue(int b) { blue = b; }
    void setGreen(int g) { green = g; }
    void setOther(int o) { other = o; }

    void setTheta(float t) { theta = t; }
    void setRadius(float r) { radius = r; }

    float getStartX() { return startPositionX; }
    float getStartY() { return startPositionY; }

    float getEndX() { return endPositionX; }
    float getEndY() { return endPositionY; }

    int getRed() { return red; }
    int getBlue() { return blue; }
    int getGreen() { return green; }
    int getOther() { return other; }

    float getTheta() { return theta; }
    float getRadius() { return radius; }
};

static const char* algorithm_names[] = { "Bubble Sort", "My Sort", "Quick Sort", "Merge Sort" };
int name_selector = 0;

void generate_spiral(Line spiral[], int size_of_array, Vector2 start, Vector2 end, int thick, float theta) {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText(TextFormat("Left Click To Change Sort :"), 50, 50, 20, RED);
    DrawText(algorithm_names[name_selector], 350, 50, 20, RED);
    DrawText(TextFormat("To Randomize Press : R"), 50, 950, 20, WHITE);
    DrawText(TextFormat("To Sort Press : S"), 950, 950, 20, WHITE);

    for (int i = 0; i < size_of_array; i++) {
        Color color = { spiral[i].getRed(), spiral[i].getGreen(), spiral[i].getBlue(), spiral[i].getOther() };
        //cout << spiral[i].getRadius() << endl;
        end = { float((cos(i * theta) * spiral[i].getRadius()) + spiral[i].getStartX()), float((sin(i * theta) * spiral[i].getRadius()) + spiral[i].getStartY()) };
        DrawLineEx(start, end, thick, color);
    }
    //cout << "\n -------------------------------------------- \n";
    EndDrawing();
}

void sort_func(Line spiral[], int size_of_array, Line* my_pointer, Vector2 start, Vector2 end, int thick, float theta) { // sort function to sort the temps from high to low

    Line largest_radius, prev_radius; // local varbles to save the largest temp and the prev temp

    for (int i = 0; i < size_of_array; i = i + 1) { // for loop to iterate the size of temperature and increment by one
        my_pointer = &spiral[i]; // sets temp_pointer to where i is in the array
        largest_radius = *my_pointer; // sets largest temp equal to temp pointer at i

        for (int j = i; j < size_of_array; j = j + 1) { // for loop starts at i and iterates the size of temperature again and inrement by one

            if (largest_radius.getRadius() < my_pointer->getRadius()) { // if statment to compaire largest temp to temp if pointer is smaller then largest temp it skips the steps

                prev_radius = largest_radius; // saves previous largest temp
                largest_radius = *my_pointer; // grabs new largest temp
                *(my_pointer - j + i) = largest_radius; // moves largest temp to the top of the array
                *my_pointer = prev_radius; // temp pointer takes the smaller temp and moves it to where the larger temp was

                generate_spiral(spiral, size_of_array, start, end, thick, theta);
            }

            my_pointer++; // increments pointer
        }
    }
}

void bubble_sort(Line spiral[], int size_of_array, Vector2 start, Vector2 end, int thick, float theta) {
    Line prev_temp;
    int comparison;
    for (int i = 0; i < size_of_array - 1; i = i + 1) {
        comparison = 0;
        for (int j = 0; j < size_of_array; j = j + 1) {

            if (spiral[j].getRadius() < spiral[j + 1].getRadius() && (j + 1) != size_of_array) {
                prev_temp = spiral[j];
                spiral[j] = spiral[j + 1];
                spiral[j + 1] = prev_temp;
                comparison++;
                generate_spiral(spiral, size_of_array, start, end, thick, theta);
            }

        }

        if (comparison == 0) {
            break;
        }
        
    }
}

// must fix
void my_swap(float current_array[], int left_pointer, int right_pointer, int pivot) {
    float temp_value = current_array[left_pointer];
    current_array[left_pointer] = current_array[pivot];
    current_array[pivot] = temp_value;
}
// must fix
int my_partion(float current_array[], int left_pointer, int right_pointer, int pivot) {
    while (left_pointer < right_pointer) {

        while (current_array[left_pointer] >= current_array[pivot] && left_pointer < right_pointer) {
            left_pointer = left_pointer + 1;
        }
        while (current_array[right_pointer] <= current_array[pivot] && left_pointer < right_pointer) {
            right_pointer = right_pointer - 1;
        }

        my_swap(current_array, left_pointer, right_pointer, pivot);

    }

    return left_pointer;
}

// add functions partition and swap. add better pivot selection.
void quick_sort(Line spiral[], int lower_bound, int upper_bound, int size_of_array, Vector2 start, Vector2 end, int thick, float theta) {

    if (lower_bound >= upper_bound) {
        return;
    }

    int pivot = upper_bound;

    int left_pointer = lower_bound;
    int right_pointer = upper_bound;

    Line temp_value;
    while (left_pointer < right_pointer) {

        while (spiral[left_pointer].getRadius() >= spiral[pivot].getRadius() && left_pointer < right_pointer) {
            left_pointer = left_pointer + 1;
        }
        while (spiral[right_pointer].getRadius() <= spiral[pivot].getRadius() && left_pointer < right_pointer) {
            right_pointer = right_pointer - 1;
        }

        temp_value = spiral[right_pointer];
        spiral[right_pointer] = spiral[left_pointer];
        spiral[left_pointer] = temp_value;
        generate_spiral(spiral, size_of_array, start, end, thick, theta);
    }

    temp_value = spiral[left_pointer];
    spiral[left_pointer] = spiral[pivot];
    spiral[pivot] = temp_value;

    int index = left_pointer;

    quick_sort(spiral, lower_bound, index - 1, size_of_array, start, end, thick, theta);
    quick_sort(spiral, index + 1, upper_bound, size_of_array, start, end, thick, theta);

}

void merge(Line* current_array, int size_of_array, Line* left_array, int left_size, Line* right_array, int right_size, 
           Vector2 start, Vector2 end, int thick, float theta , Line* spiral, int ArrayLength) {

    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) {
        if (left_array[i].getRadius() >= right_array[j].getRadius()) {
            
            current_array[k] = left_array[i];
            spiral[k + size_of_array] = left_array[i];

            i++;
            generate_spiral(spiral, ArrayLength, start, end, thick, theta);
        }
        else {
            current_array[k] = right_array[j];
            //spiral[k + int(ArrayLength / 2)] = current_array[k];
            spiral[k + size_of_array] = right_array[j];

            j++;
            generate_spiral(spiral, ArrayLength, start, end, thick, theta);
        }
        k++;
    }

    while (i < left_size) {
        current_array[k] = left_array[i];
        spiral[k + size_of_array] = left_array[i];

        i++;
        k++;
        generate_spiral(spiral, ArrayLength, start, end, thick, theta);
    }

    while (j < right_size) {
        current_array[k] = right_array[j];
        //spiral[k + int(ArrayLength / 2)] = current_array[k];
        spiral[k + size_of_array] = right_array[j];

        j++;
        k++;
        generate_spiral(spiral, ArrayLength, start, end, thick, theta);
    }
    
}

void merge_sort(Line* current_array, int size_of_array, Vector2 start, Vector2 end, int thick, float theta,Line* spiral, int ArrayLength) {

    int insertion_position;

    if (size_of_array < 2) {
        return;
    }

    int mid_index = size_of_array / 2;

    Line* left_array = new Line[mid_index];
    Line* right_array = new Line[size_of_array - mid_index];

    for (int i = 0; i < mid_index; i++) {
        left_array[i] = current_array[i];
    }

    for (int i = mid_index; i < size_of_array; i++) {
        right_array[i - mid_index] = current_array[i];
    }

    merge_sort(left_array, mid_index, start, end, thick, theta, spiral, ArrayLength);
    merge_sort(right_array, size_of_array - mid_index, start, end, thick, theta, spiral, ArrayLength);

    //Merge
    //cout << "\n\n---------------merge------------------\n\n";
    //generate_spiral(spiral, ArrayLength, start, end, thick, theta);
    merge(current_array, size_of_array, left_array, mid_index, right_array, size_of_array - mid_index, start, end, thick, theta, spiral, ArrayLength);
    
    //cout << "\n\n---------------out------------------\n\n";
}

int randomize_spiral(Line spiral[], int size_of_array, Vector2 start, Vector2 end, int thick, int iterator) {
    Line temp;

    if (iterator < size_of_array) {
        int random_number = rand() % size_of_array;
        temp = spiral[iterator];
        spiral[iterator] = spiral[random_number];
        spiral[random_number] = temp;

        iterator++;
    }

    else {
        return iterator;
    }
    
}

void create_spiral(Line spiral[], int ArrayLength, float theta, int screenWidth, int screenHeight, float color_gradent) {
    for (int i = 0; i < ArrayLength; i++) {
        Color color = { spiral[i].getRed(), spiral[i].getGreen(), spiral[i].getBlue(), spiral[i].getOther() };


        spiral[i].setRadius((i * theta) * 100);

        spiral[i].setOther(spiral[i].getOther() + (i * color_gradent * -1));

        spiral[i].setStartX(screenWidth / 2);
        spiral[i].setStartY(screenHeight / 2);

        spiral[i].setEndX((cos(i * theta) * spiral[i].getRadius()) + spiral[i].getStartX());
        spiral[i].setEndY((sin(i * theta) * spiral[i].getRadius()) + spiral[i].getStartY());

    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input mouse wheel");

    Vector2 start = { screenWidth / 2 , screenHeight / 2 };
    Vector2 end = { screenWidth / 2 , screenHeight / 2 };

    float theta = -.04;
    float prev_theta = theta;

    int ArrayLength = int((-2 * M_PI) / theta);
    float color_gradent = float(255 / ArrayLength);
    float thick = 2125 / ArrayLength;

    Line spiral[2125];

    int lower_bound = 0;
    int upper_bound = ArrayLength - 1;

    float timer = 0.0f;
    int frame = 0;
    int temp_frame = 0;

    int counter = 0;
    int iterator = 0;

    create_spiral(spiral, ArrayLength, theta, screenWidth, screenHeight, color_gradent);

    Line* my_pointer = NULL; // declares pointer and sets it to nothing
    my_pointer = &spiral[0];// sets the pointer adress to spiral indice 0


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Draw
        //----------------------------------------------------------------------------------

        //ArrayLength = int((-2 * M_PI) / theta);
        //color_gradent = float(255 / ArrayLength);
        //thick = float(2125 / ArrayLength);

        
        timer += GetFrameTime();

        if (timer >= 0.1f ) {
            timer = 0.0f;
            frame += 1;
        }

        frame = frame % ArrayLength;

        if (IsKeyPressed(KEY_R) && counter == 1) {
            counter = 6;
        }

        if (IsKeyPressed(KEY_S) && counter == 1) {
            counter = name_selector + 2;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (name_selector < 3) {
                name_selector++;
            }
            else {
                name_selector = 0;
            }
        }

        //theta += GetMouseWheelMove() * .01;

        //if (theta >= -.01 || theta < -.1 || counter != 1) {
        //    theta -= GetMouseWheelMove() * .01;
        //}

        //if (prev_theta != theta) {
        //    create_spiral(spiral, ArrayLength, theta, screenWidth, screenHeight, color_gradent);
        //    prev_theta = theta;
        //}

        switch (counter) {
            case 0:
                generate_spiral(spiral, frame, start, end, thick, theta);
                if (frame == ArrayLength - 1) {
                    counter = 1;
                }
                break;

            case 1:
                generate_spiral(spiral, ArrayLength, start, end, thick, theta);
                break;

            case 2:
                bubble_sort(spiral, ArrayLength, start, end, thick, theta);
                counter = 1;
                break;

            case 3:
                sort_func(spiral, ArrayLength, my_pointer, start, end, thick, theta);
                counter = 1;
                break;

            case 4:
                quick_sort(spiral, lower_bound, upper_bound, ArrayLength, start, end, thick, theta);
                counter = 1;
                break;

            case 5:
                merge_sort(spiral, ArrayLength, start, end, thick, theta, spiral, ArrayLength);
                counter = 1;
                break;

            case 6:

                generate_spiral(spiral, ArrayLength, start, end, thick, theta);

                if (frame > temp_frame) {
                    iterator = randomize_spiral(spiral, ArrayLength, start, end, thick, iterator);
                }
                if (iterator == ArrayLength - 1) {
                    counter = 1;
                    iterator = 0;
                }

                temp_frame = frame;
                break;
            
        }
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}