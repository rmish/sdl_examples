/*
 ============================================================================
 Name        : 02_show_picture.c
 Author      : Riapolov Mikhail
 Version     :
 Copyright   : Use at your own risk
 Description : Show picture in window
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Размеры окна для вывода
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

char image[] = "/home/MAIN/rmp/temp/leaves.jpg";

// Указатель на структуру, описывающую окно для вывода графики
SDL_Window* window = NULL;
// указатель на поверхность (surface), на которой мы будем рисовать и выводить её в окне
SDL_Surface* screenSurface = NULL;
// указатель на структуру с загруженной картинкой после подготовки её к выводу
SDL_Surface* optimizedSurface = NULL;

int main(void) {
	// Инициализируем библиотеку SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// при появлении ошибки выводим её описание
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	} else {
		// После успешной инициализации создаём окно для вывода графики
		window = SDL_CreateWindow("SDL Picture", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			// выводим ошибку, если создать окно не удалось
			printf("Window could not be created! SDL_Error: %s\n",
					SDL_GetError());
		} else {
			// инициализируем загрузку PNG
			int imgFlags = IMG_INIT_JPG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL_image Error: %s\n",
				IMG_GetError());
			} else {
				// Получаем поверхность для рисования
				screenSurface = SDL_GetWindowSurface(window);
				// Загружаем картинку в отдельную поверхность
				SDL_Surface* loadedSurface = IMG_Load(image);
				// Проверяем успешность загрузки
				if (loadedSurface == NULL) {
					printf("Unable to load image %s! SDL_image Error: %s\n",
							image, IMG_GetError());
				} else {

					// преобразуем загруженную поверхность в формат экранной
					optimizedSurface = SDL_ConvertSurface(loadedSurface,
							screenSurface->format, NULL);
					if (optimizedSurface == NULL) {
						printf("Unable to optimize image %s! SDL Error: %s\n",
								image, SDL_GetError());
					}
					// Удаляем загруженную поверхность
					SDL_FreeSurface(loadedSurface);
				}
			}
			SDL_BlitSurface(optimizedSurface, NULL, screenSurface, NULL);
			// Обновляем (выводим содержимое поверхности в окно)
			SDL_UpdateWindowSurface(window);
			// Ждём 5 секунд
			SDL_Delay(2000);
		}
	}

// Закрываем окно и освобождаем все выделенные ему ресурсы
	SDL_DestroyWindow(window);
// Завершаем работу библиотеки и освобождаем все выделенные ей ресурсы
	SDL_Quit();
	return EXIT_SUCCESS;
}

