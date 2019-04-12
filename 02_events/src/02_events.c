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
int init();
// функция для проведения завершения работы библиотеки и освобождения всех ресурсов
void close();
// изменение цвета окна
void updateColor();

// Глобальная переменная, соответствующая окну программы
SDL_Window* gWindow = NULL;
// Глобальная переменная, соответствующая поверхности, которую мы выводим в окне
SDL_Surface* gScreenSurface = NULL;

int main(void) {
	// Инициализируем библиотеку SDL
	if (init() > 1) {
		printf("Error in initialization.\n");
	} else {
		//main loop
	}

	close();
	return EXIT_SUCCESS;
}

int init() {
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
			// Заполняем её белым цветом
			SDL_FillRect(screenSurface, NULL,
					SDL_MapRGB(screenSurface->format, 0x05, 0x05, 0x05));
			// Обновляем (выводим содержимое поверхности в окно)
			SDL_UpdateWindowSurface(window);
		}
	}
	return success;
}

void close() {
	// Закрываем окно и освобождаем все выделенные ему ресурсы
	SDL_DestroyWindow(window);
	// Завершаем работу библиотеки и освобождаем все выделенные ей ресурсы
	SDL_Quit();
}
