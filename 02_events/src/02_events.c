/*
 ============================================================================
 Name        : 02_events.c
 Author      : Riapolov Mikhail
 Version     :
 Copyright   : Use at your own risk
 Description : Events Hahdling
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// Размеры окна для вывода
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int greylevel = 0x0F;

// Функция для инициализации библиотеки и создания окна
int initSDL();
// функция для проведения завершения работы библиотеки и освобождения всех ресурсов
void closeSDL();
// изменение цвета окна
void updateColor();

// Глобальная переменная, соответствующая окну программы
SDL_Window* window = NULL;
// Глобальная переменная, соответствующая поверхности, которую мы выводим в окне
SDL_Surface* screenSurface = NULL;

int main(void) {
	// Инициализируем библиотеку SDL
	if (initSDL() > 1) {
		printf("Error in initialization.\n");
	} else {

		updateColor();

		int quit = 1;
		SDL_Event event;
		while (quit != 0) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT)
					quit = 1;
				else if (event.type == SDL_KEYDOWN) {
					switch (event.key.keysym.sym) {
					case SDLK_UP:
						if (greylevel < 0xFF) greylevel = greylevel + 10;
						break;
					case SDLK_DOWN:
						if (greylevel > 0x0) greylevel = greylevel - 10;
						break;
					case SDLK_LEFT:
						greylevel = 0x0;
						break;
					case SDLK_RIGHT:
						greylevel = 0xFF;
						break;
					case SDLK_ESCAPE:
						quit = 1;
						break;
					}
				}
			}
			updateColor();
		}
	}
	closeSDL();
	return EXIT_SUCCESS;
}

int initSDL() {
	int success = 1;
	// Инициализируем библиотеку SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// при появлении ошибки выводим её описание
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = 0;
	} else {
		// После успешной инициализации создаём окно для вывода графики
		window = SDL_CreateWindow("SDL example", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			// выводим ошибку, если создать окно не удалось
			printf("Window could not be created! SDL_Error: %s\n",
					SDL_GetError());
			success = 0;
		} else {
			// Получаем поверхность для рисования
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return success;
}

void closeSDL() {
	// Закрываем окно и освобождаем все выделенные ему ресурсы
	SDL_DestroyWindow(window);
	// Завершаем работу библиотеки и освобождаем все выделенные ей ресурсы
	SDL_Quit();
}

void updateColor() {
	// обновляем цвет в соответствии с текущим показателем серости
	SDL_FillRect(screenSurface, NULL,
			SDL_MapRGB(screenSurface->format, greylevel, greylevel, greylevel));
	SDL_UpdateWindowSurface(window);
}
