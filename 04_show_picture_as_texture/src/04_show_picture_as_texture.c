/*
 ============================================================================
 Name        : 04_show_picture_as_texture.c
 Author      : Riapolov Mikhail
 Version     :
 Copyright   : Use at your own risk
 Description : Загрузка и вывод картинки на экран. Использование дополнительной
               библиотеки SDL_imgae для загрузки jpg файла. При выводе картинки
               на экран для хранения изображения использвуется структура
               SDL_texture. В отличии от предыдущего примера с SDL_surface
               использование текстур позволяет применить для вывода на экран
               апаратное скорение средствами видеокарты. В остальном функционал
               этого примера аналогичен 03_show_picture
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#if defined(__MINGW32__)
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

// Размеры окна для вывода
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static const char image[] = "resources/404cat.jpg";

// Функция для инициализации библиотеки и создания окна
int initSDL();
// функция для проведения завершения работы библиотеки и освобождения всех ресурсов
void closeSDL();
// загрузка изображения
SDL_Texture* loadImage(char imagePath[]);

// Указатель на структуру, описывающую окно для вывода графики
SDL_Window* window = NULL;
// Указательн на структуру, описывающую механизм отрисовки в окне с применением аппаратного ускорения
SDL_Renderer* renderer = NULL;
// указатель на поверхность (surface), на которой мы будем рисовать и выводить её в окне
SDL_Surface* screenSurface = NULL;

int main(int argc,char *argv[]) {

	// Инициализируем библиотеку SDL
	if (initSDL() > 1) {
		printf("Error in initialization.\n");
	} else {
		// Загружаем картирнку из файла
		SDL_Texture* img = loadImage(image);
		// Очищаем буфер рисования
		SDL_RenderClear(renderer);
		// выводим картинку на экран. Указываем структуру с описанием механихма
		// отрисовки, текстуру, область текстуры для вывода и область, в которую
		// текстура будет скопирована (по умолчанию - вся текстура, растянутая на
		// всю доступную область)
		SDL_RenderCopy(renderer,img, NULL, NULL);
		// Выводим буфер на экран
		SDL_RenderPresent(renderer);
		// Ждём 5 секунд
		SDL_Delay(5000);
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
			// Инициализируем библиотеку загрузки изображений (только для JPG)
			int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL_image Error: %s\n",
				IMG_GetError());
				success = 0;
			}
			// Получаем поверхность для рисования
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if ( renderer == NULL ) {
				// выводим ошибку, если создать окно не удалось
				printf("Renderer could not be created! SDL_Error: %s\n",
						SDL_GetError());
				success = 0;
			}
			else {
				// Задаём цвет отрисовки по умолчанию - белый
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
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

SDL_Texture* loadImage(char imagePath[]) {
	printf("%s\n",imagePath);
	SDL_Texture *newTexture;
	// Загружаем изображение
	SDL_Surface* loadedSurface = IMG_Load(imagePath);
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", imagePath,
		IMG_GetError());
	} else {
		// Если успешно загрузили, преобразуем загруженную поверхность в формат экранной
		// Если этого не сделать, то при каждом выводе будет проводится преобразование
		 newTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to load texture %s! SDL Error: %s\n", imagePath,
					SDL_GetError());
		} else
			// если успешно, возвращаем указатель на поверхность с изображенеим
			return newTexture;
		// Удаляем загруженную поверхность
		SDL_FreeSurface(loadedSurface);
	}
	return NULL;
}
