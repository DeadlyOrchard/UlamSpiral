#include <iostream>
#include <SDL2/SDL.h>

class Point{
    int x{}, y{};
    public:
        Point(int posX, int posY){
            x = posX;
            y = posY;
        }
        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
        void moveRight(int distance = 1){
            x += distance;
        }
        void moveLeft(int distance = 1){
            x -= distance;
        }
        void moveUp(int distance = 1){
            y += distance;
        }
        void moveDown(int distance = 1){
            y -= distance;
        }
};

int toPixels(int coordinate, char axis);
bool isPrime(int value);

// set up default viewing settings
const int WIDTH {1920}, HEIGHT {1080}; // width and height of renderer
const int STEP {1}; // pixel distance between coordinate points
Point point {0, 0}; // used to store x, y graph coordinates | (0, 0) = screen center

int main(int argc, char *args[] ){
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_Event e;
    bool quit {false};
    bool first (true);

    // set default background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // values to control movement of point
    int distanceTraveled {}; // number of steps taken since last turn
    int turnDistance {1}; // number of steps until a turn will be taken
    int turnInterval {}; // controls direction of the turn
    int turnIncrementor {}; // counts how many turns have been made to know if the turn distance should increase
    int stepIncrementor {}; // counts how many steps have been taken
    SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255); // set spiral color
    
    // game loop
    while (!quit){
        // event handling
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                quit = true;
            }
        }
        // update screen here
        if (isPrime(stepIncrementor)){
            SDL_RenderDrawPoint(renderer, toPixels(point.getX(), 'x'), toPixels(point.getY(), 'y'));
            std::cout << stepIncrementor << std::endl;
        }
        // move point in the current direction
        switch (turnInterval){
            case 0:
                point.moveRight();
                break;
            case 1:
                point.moveUp();
                break;
            case 2:
                point.moveLeft();
                break;
            case 3:
                point.moveDown();
                break;
        }
        stepIncrementor++;
        distanceTraveled++;
        // check for a turn
        if (distanceTraveled == turnDistance){
            // change direction
            if (turnInterval < 3){
                turnInterval++;
            } else{
                turnInterval = 0;
            }
            turnIncrementor++;
            distanceTraveled = 0; // reset distance traveled
            if (turnIncrementor % 2 == 0){
                turnDistance++;
            }
        }
        SDL_RenderPresent(renderer);

        if (first){
            // console testing
            for (int i{}; i < 150; i++){
                if (isPrime(i)){
                    std::cout << i << std::endl;
                }
            }
        }
        first = false;
    }
    return 0;
}

int toPixels(int coordinate, char axis){
    int range{};
    int pixelValue {};
    switch (axis){
        case 'x':
            range = WIDTH;
            break;
        case 'y':
            range = HEIGHT;
            break;
    }
    return (range / 2) + coordinate * STEP;
}

bool isPrime(int value){
    for (int i{2}; i < value / 2 + 1; i++){
        if (value % i ==  0){
            return false;
        }
    }
    return true;
}