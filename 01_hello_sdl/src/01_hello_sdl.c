/*
 ============================================================================
 Name        : 01_hello_sdl.c
 Author      : Riapolov Mikhail
 Version     :
 Copyright   : Use at your own risk
 Description : Пример инициализации библиотеки SDL для вывода окна, залитого
               сплошным цветом. Окно не реагирует ни на какие события, просто
               задерживается на 5 секунд, после чего программа сама
               завершается
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// Размеры окна для вывода
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(void) {
	// Указатель на структуру, описывающую окно для вывода графики
	SDL_Window* window = NULL;
	// указатель на поверхность (surface), на которой мы будем рисовать и выводить её в окне
	SDL_Surface* screenSurface = NULL;
	// Инициализируем библиотеку SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// при появлении ошибки выводим её описание
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	} else {
		// После успешной инициализации создаём окно для вывода графики
		window = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN);
		if (window == NULL) {
			// выводим ошибку, если создать окно не удалось
			printf("Window could not be created! SDL_Error: %s\n",
					SDL_GetError());
		} else {
			// Получаем поверхность для рисования
			screenSurface = SDL_GetWindowSurface(window);
			// Заполняем её белым цветом
			SDL_FillRect(screenSurface, NULL,
					SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			// Обновляем (выводим содержимое поверхности в окно)
			SDL_UpdateWindowSurface(window);
			// Ждём 5 секунд
			SDL_Delay(2000);
		}
	}
	// Закрываем окно и освобождаем все выделенные ему ресурсы
	SDL_DestroyWindow( window );
	// Завершаем работу библиотеки и освобождаем все выделенные ей ресурсы
	SDL_Quit();
	return EXIT_SUCCESS;
}

