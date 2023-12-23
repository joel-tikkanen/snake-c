#include <stdbool.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define SQUARE_SIZE 30
#define APPLE_SIZE 30
#define CENTER_X SCREEN_WIDTH / 2
#define CENTER_Y SCREEN_HEIGHT / 2

typedef struct body_part {
    struct body_part* next;
    int x;
    int y;
} BodyPart;

typedef struct snake {
    int dir_x;
    int dir_y;
    BodyPart* head;
} Snake;

typedef struct apple {
    int x;
    int y;
} Apple;



void add_body_part(Snake* snake);
void render_snake(BodyPart* head);
void handle_input(Snake* snake);
bool check_walls(Snake* snake);
bool check_body(Snake* snake);
void move_to_dir(int dir_x, int dir_y, Snake* snake);
void render_apple(Apple* apple);
void init_snake(Snake* snake);
void check_for_apple(Apple* apple, Snake* snake);