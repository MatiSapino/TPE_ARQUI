#include <utils.h>
#include <colors.h>
#include <UserSyscalls.h>

int headX, headY, fruitX, fruitY;
int width=30;
int height=30;
int gameOver=0;
int direction=2;
int size=0;
int score=0;
int speed=80;
int bodyX[100];
int bodyY[100];
int seed_count = 0;
int buffer_pos;
int prev_pos = 0;

void render(void);
void setupGame(void);
void inputCheck(void);
void moveSnake(void);
void gameOverCheck(void);
void placeFruit(void);
void renderFrame();
void fruitCheck(void);
int custom_rand();

void snake() {
	setupGame();
	placeFruit();
	while(!gameOver) {
		clearScreen();
		render();
		inputCheck();
		moveSnake(); 
		gameOverCheck();
		fruitCheck();
		call_sleepms(speed);
  	}
	call_sleepms(400);
	call_clear_screen();
	putString("\n\n\n\n\t\tYour final Score: ", WHITE);
	putInt(score);
	putString("\n\n\t\tThank You for playing!! (press any key to exit)\n\n\n\n", WHITE);
}

void snake_multiplayer() {
	setupGame();
	placeFruit();
	while(!gameOver) {
		clearScreen();
		render();
		moveSnake();
		gameOverCheck();
		fruitCheck();
		call_sleepms(speed);
  	}
	inputCheck();
	call_sleepms(1500);
	call_clear_screen();
	putString("\n\n\n\n\t\tYour final Score: ", WHITE);
	putInt(score);
	putString("\n\n\t\tThank You for playing!!\n\n\n\n", WHITE);
}


void render(void) {
    call_clear_screen();
    int i, j, k, p;
    for (j = 0; j <= height; j++) {
        for (i = 0; i <= width; i++) {
            p = 1;
            if (i == 0 || j == 0 || i == width || j == height) {
                putString("*", WHITE);
            } else if (i == fruitX && j == fruitY && !(headX==fruitX && headY==fruitY)) {
                putString("0", WHITE);
            } else if (i == headX && j == headY) {
                putString("o", WHITE);
            } else {
                for (k = 0; k < size; k++) {
                    if (i == bodyX[k] && j == bodyY[k]) {
                        putString("+", WHITE);
                        p = 0;
                        break;
                    }
                }
                if (p) {
                    putString(" ", WHITE);
                }
            }
        }
        putNewLine();
    }
    putString("Score: ", WHITE);
    putInt(score);
}

void placeFruit(void) {
    int maxTries = 100; // Límite de intentos para evitar bucles infinitos
    for (int try = 0; try < maxTries; try++) {
        fruitX = custom_rand() % (width - 2) + 1;
        fruitY = custom_rand() % (height - 2) + 1;

        // Asegúrate de que la fruta no se superponga con el cuerpo de la serpiente
        int overlap = 0;
        for (int i = 0; i < size; i++) {
            if (fruitX == bodyX[i] && fruitY == bodyY[i]) {
                overlap = 1;
                break;
            }
        }

        if (!overlap) {
            break; // Ubicación válida para la fruta
        }
    }
}



// Esta función genera un número pseudoaleatorio en el rango [0, RAND_MAX]
int custom_rand() {
	int numeros[] = {56, 34, 72, 19, 88, 45, 27, 63, 11, 75,
                    90, 30, 12, 50, 42, 67, 22, 98, 14, 61,
                    25, 84, 37, 70, 17, 93, 76, 29, 58, 39,
                    66, 21, 83, 52, 15, 97, 41, 89, 33, 60}; 
	seed_count = (seed_count + 1) % (sizeof(numeros) / sizeof(numeros[0]));
    numeros[seed_count] = (214013 * numeros[seed_count] + 2531011);
    return (numeros[seed_count] >> 16) & 0x7FFF;
}

void setupGame(void) {
	headX=height/2;
	headY=width/2;
	call_getBuffPosition(&buffer_pos);
	width=30;
	height=30;
	gameOver=0;
	direction=2;
	size=0;
	score=0;
	speed=50;
	seed_count = 0;
	prev_pos = 0;
}

void fruitCheck(void) {
	if(headX==fruitX && headY==fruitY) {
		score+=10;
		size++;
		placeFruit();
	}
}

void inputCheck(void) {
	char c;
	call_getBuffPosition(&buffer_pos);
	if (prev_pos < buffer_pos){
		prev_pos = buffer_pos;
		call_getLastKey(&c, buffer_pos);
		switch (c) {
			case 'w':
				if(direction!=3)
					direction=1;
				break;
			case 'd':
				if(direction!=4)
					direction=2;
				break;
			case 's':
				if(direction!=1)
					direction=3;
				break;
			case 'a':
				if(direction!=2)
					direction=4;
		}
	}
}

void moveSnake(void) {
	int x1,x2,y1,y2,i;
	if(size==1){
		bodyX[0]=headX;
		bodyY[0]=headY;
	} else {
		x1=headX;
		y1=headY;
		for(i=0;i<size;i++) {
			x2=bodyX[i];
			y2=bodyY[i];
			bodyX[i]=x1;
			bodyY[i]=y1;
			x1=x2;
			y1=y2;
		}
	}
	switch (direction) {
		case 1:
			headY--;
			break;
		case 2:
			headX++;
			break;
		case 3:
			headY++;
			break;
		case 4:
			headX--;
	}
}

void gameOverCheck(void) {
	int i;
	for(i=0;i<size-1;i++) {
		if(headX==bodyX[i] && headY==bodyY[i])
			gameOver=1;
	}
	if(headX==width||headX==0||headY==height||headY==0)
		gameOver=1;
}