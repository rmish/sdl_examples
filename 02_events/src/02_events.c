/*
 ============================================================================
 Name        : 02_events.c
 Author      : Riapolov Mikhail
 Version     :
 Copyright   : Use at your own risk
 Description : Работа с событиями. Используется основной цикл, завершающийся
               при событии выхода из приложения (получается от ОС) или нажатии
               ESC. Кнопки влево-вправо заливают окно белым и чёрным цветом
               соответсвенно, вверх и вниз делают окно светлее или темнее и
               позволяют залить его различными оттенками серого цвета.
               Из функции main вынесена инициализация программы (в данном
               случае только инициализация бибилиотеки SDL) и завершение работы
               (освобождение ресурсов и работы бибилиотеки SDL).
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#if defined(__MINGW32__)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

// Размеры окна для вывода
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

uint8_t greylevel = 0x0F;

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
// Глобальная переменная, соответствующая поверхности, на которой мы рисуем
SDL_Surface* drawSurface = NULL;

int main(int argc, char *argv[]) {
	// Инициализируем библиотеку SDL
	if (initSDL() > 1) {
		printf("Error in initialization.\n");
	} else {

		updateColor();

		int quit = 0;
		// Структура для хранения информации о событии
		SDL_Event event;
		// Основной цикл программы, выход из которого происходит при
		// появлении события выхода (от ОС или по нажатию ESC)
		while (quit == 0) {
			// Ждём появления события
			while (SDL_PollEvent(&event) != 0) {
				// При его появлении проверяем тип
				if (event.type == SDL_QUIT)
					// Если событие выхода (сигнал от ОС, что приложение
					// нужно завершить), меняем флаг выхода
					quit = 1;
				else if (event.type == SDL_KEYDOWN) {
					// Если это нажатие на клавишу клавиатуры, смотрим код
					// нажатой клавиши
					switch (event.key.keysym.sym) {
					case SDLK_UP:
						if (greylevel < 0xFF) greylevel = greylevel + 10;
						break;
					case SDLK_DOWN:
						if (greylevel > 0x0) greylevel = greylevel - 10;
						break;
					case SDLK_LEFT:
						greylevel = 0;
						break;
					case SDLK_RIGHT:
						greylevel = 255;
						break;
					case SDLK_ESCAPE:
						// Нажата клавиша ESC, меняем флаг выхода
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
			SDL_FillRect(screenSurface, NULL,
					SDL_MapRGB(screenSurface->format, 255, 255, 255));
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
			SDL_MapRGB(screenSurface->format, greylevel,  greylevel,  greylevel));
	SDL_UpdateWindowSurface(window);
}
