#include <stdio.h>
#include "include/raylib.h"
#include "include/raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define SQUARE_SIZE 30
#define APPLE_SIZE 30
#define CENTER_X SCREEN_WIDTH / 2
#define CENTER_Y SCREEN_HEIGHT / 2



typedef struct snake
{
    int dir_x;
    int dir_y;
    struct body_part *head;

} Snake;

struct body_part {
    struct body_part *next;
    int x;
    int y;
};

typedef struct apple {
    int x;
    int y;
} Apple;


void add_body_part(struct body_part *head){

    struct body_part *new = (struct body_part*)malloc(sizeof(struct body_part));
    new->x = head->x + SQUARE_SIZE;
    new->y = head->y;

    // finding last body_part
    struct body_part *last = head;
    while (last->next != NULL) {
        last = last->next;
    }

    // linking last to new body_part
    last->next = new;

    return;
}


void render_snake(struct body_part *head){
    struct body_part *p = head;
    while (p != NULL) {
        DrawRectangle(p->x, p->y, SQUARE_SIZE, SQUARE_SIZE, GREEN);
        p = p->next;
    }
    return;
}

void handle_input(Snake *snake) {        
    if (IsKeyDown(KEY_RIGHT)) {
        snake->dir_x = 1;
        snake->dir_y = 0;
    };
    if (IsKeyDown(KEY_LEFT)){
        snake->dir_x = -1;
        snake->dir_y = 0;
    };
    if (IsKeyDown(KEY_UP)) {
        snake->dir_x = 0;
        snake->dir_y = -1;
    };
    if (IsKeyDown(KEY_DOWN)){
        snake->dir_x = 0;
        snake->dir_y = 1;
    };
}


// moves snake to direction provided by player
void move_to_dir(int dir_x, int dir_y, Snake *snake){
   
    struct body_part *new_head = (struct body_part*)malloc(sizeof(struct body_part));
    new_head->x = (snake->head)->x + SQUARE_SIZE * dir_x;
    new_head->y = (snake->head)->y + SQUARE_SIZE * dir_y;
    new_head->next = snake->head;
    snake->head = new_head;
    struct body_part *p = snake->head;
    struct body_part *prev = NULL;
    while (p->next != NULL) {
        prev = p;
        p = p->next;
    }
    if (prev != NULL) {
        prev->next = NULL;
        free(p);
    }

    return;
}


void render_apple(Apple apple){
    DrawRectangle(apple.x, apple.y, APPLE_SIZE, APPLE_SIZE, RED);
    return;
}


void init_snake(struct body_part *head){
    for (int i = 1; i < 3; i++){
        add_body_part(head);
    }
    return;
}

void check_for_apple(Apple *apple, Snake *snake){
    if ((snake->head)->x == apple->x && (snake->head)->y == apple->y) {
        apple->x = rand() % SCREEN_WIDTH - APPLE_SIZE;
        apple->y = rand() % SCREEN_HEIGHT - APPLE_SIZE;
        add_body_part(snake->head); 
    }

}





int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Snake snake;
    snake.head = (struct body_part*)malloc(sizeof(struct body_part));
    snake.dir_x = 1;
    snake.dir_y = 0;

    Apple apple = {0};

    srand((unsigned int)time(NULL));

    apple.x = rand() % SCREEN_WIDTH - APPLE_SIZE;
    apple.y = rand() % SCREEN_HEIGHT - APPLE_SIZE;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game");

    snake.head->next= NULL;
    snake.head->x = CENTER_X;
    snake.head->y = CENTER_Y;


    init_snake(snake.head);

    SetTargetFPS(10);               

    // Main game loop

    while (!WindowShouldClose()) {


        // Update
        handle_input(&snake);
        move_to_dir(snake.dir_x, snake.dir_y, &snake);

        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        srand((unsigned int)time(NULL));

        // Draw
        //----------------------------------------------------------------------------------
       
        BeginDrawing();
            render_snake(snake.head);
            render_apple(apple);
            ClearBackground(RAYWHITE);
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    return 0;
}