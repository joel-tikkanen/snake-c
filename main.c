#include "snake.h"
#include <stdio.h>
#include "include/raylib.h"
#include "include/raylib.h"
#include <stdlib.h>
#include <time.h>


void add_body_part(Snake *snake){
    BodyPart* new = (BodyPart*)malloc(sizeof(BodyPart));
    new->x = snake->head->x - SQUARE_SIZE * snake->dir_x;
    new->y = snake->head->y - SQUARE_SIZE * snake->dir_y;

    new->next = NULL;

    BodyPart* last =snake-> head;
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new;
}


void render_snake(BodyPart *head){
    BodyPart* p = head;
    while (p != NULL) {
        DrawRectangle(p->x, p->y, SQUARE_SIZE, SQUARE_SIZE, GREEN);
        p = p->next;
    };
}

void handle_input(Snake *snake) {        
    if (IsKeyDown(KEY_RIGHT)  && snake->dir_x != -1) {
        snake->dir_x = 1;
        snake->dir_y = 0;
    };
    if (IsKeyDown(KEY_LEFT) && snake->dir_x != 1){
        snake->dir_x = -1;
        snake->dir_y = 0;
    };
    if (IsKeyDown(KEY_UP) && snake->dir_y != 1) {
        snake->dir_x = 0;
        snake->dir_y = -1;
    };
    if (IsKeyDown(KEY_DOWN) && snake->dir_y != -1){
        snake->dir_x = 0;
        snake->dir_y = 1;
    };
}

bool check_walls(Snake *snake) {
    return !(snake->head->x >= 0 && snake->head->x <= SCREEN_WIDTH-SQUARE_SIZE) ||
    !(snake->head->y >= 0 && snake->head->y <= SCREEN_HEIGHT-SQUARE_SIZE);
  
}

bool check_body(Snake *snake) {
    struct body_part *p = snake->head->next;
    p = p->next;
    while (p != NULL) {
        if (snake->head->x == p->x && snake->head->y == p->y) {
            return true;
        }
        p = p->next;
    }
    return false;
}


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


void render_apple(Apple *apple){
    DrawRectangle(apple->x, apple->y, APPLE_SIZE, APPLE_SIZE, RED);
    return;
}


void init_snake(Snake *snake){
    for (int i = 1; i < 3; i++){
        add_body_part(snake);
    }
    return;
}

void check_for_apple(Apple *apple, Snake *snake){
    if ((snake->head->x < apple->x + APPLE_SIZE && snake->head->x + SQUARE_SIZE > apple->x) &&
        (snake->head->y < apple->y + APPLE_SIZE && snake->head->y + SQUARE_SIZE > apple->y)) {
        apple->x = rand() % (SCREEN_WIDTH - APPLE_SIZE);
        apple->y = rand() % (SCREEN_HEIGHT - APPLE_SIZE);
        add_body_part(snake);
    }
}



void restart(Snake *snake, Apple *apple){
    
    BodyPart *p = snake->head;
    BodyPart *next;
    while (p != NULL){
        next = p->next;
        free(p);
        p = next;
    }

    snake->dir_x = 1;
    snake->dir_y = 0;

    srand((unsigned int)time(NULL));

    apple->x = rand() % (SCREEN_WIDTH - APPLE_SIZE);
    apple->y = rand() % (SCREEN_HEIGHT - APPLE_SIZE);

    snake->head = (BodyPart*)malloc(sizeof(BodyPart));
    snake->head->next = NULL;
    snake->head->x = CENTER_X;
    snake->head->y = CENTER_Y;

    init_snake(snake);
}


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "snake");
    SetTargetFPS(10);

    Snake *snake = (Snake*)malloc(sizeof(Snake));
    Apple *apple = (Apple*)malloc(sizeof(Apple));

    snake->head = (BodyPart*)malloc(sizeof(BodyPart));
    
    restart(snake, apple);

    while (!WindowShouldClose()) {
        handle_input(snake);
        move_to_dir(snake->dir_x, snake->dir_y, snake);

        if (check_walls(snake) || check_body(snake)) {
            restart(snake, apple);
        }

        check_for_apple(apple, snake);

        BeginDrawing();
        ClearBackground(BLACK);
        render_snake(snake->head);
        render_apple(apple);
        EndDrawing();
    }

    CloseWindow();

    free(snake->head);
    free(snake);
    free(apple);

    return 0;
}