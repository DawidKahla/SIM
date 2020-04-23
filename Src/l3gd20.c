/*
 * l3gd20.c
 *
 *  Created on: 21.04.2020
 *      Author: Dawid
 */

#include "l3gd20.h"

// Funkcje typu GET_A_B mają na celu czytanie wartości z konkretnych osi żyroskopu
// A jest nazwą osi
// Wartości są złożone z dwóch komplementarnych liczb oznaczonych przez B,
// Gdzie B==L -> młodsze bity, B==H -> starsze bity
// Wartości z bitów młodszych bardzo często pływają i nawet przy niezauważlnym ruchu nie są zerowe
// Funkcje zostały napisane pod płytkę stm32f429_discovery, gdzie w bazowych ustawieniach za CS odpowiada pin 1 portu C
// zwrócony zostaje odczyt o wartości 0-255
// w przypadku nagłych odchyleń żyroskop zwraca przez kilka odczytów tą samą wartosc, dodatkowo nie sa one zbyt miarodajne
// przy ruchach niewidocznych GET_X_H zwraca 0, natomiast GET_Y_H 255
// TIMEOUT_GYRO został ujęty w ten sposób, aby zapobiec kilku errorom przy kompilacji
uint8_t const TIMEOUT_GYRO = 50;

uint8_t GET_X_L(SPI_HandleTypeDef hspi_in){
	uint8_t data;
	uint8_t address = 0x28 | 0x80;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi_in, &address, 1, TIMEOUT_GYRO);
	HAL_SPI_Receive(&hspi_in, &data, 1, TIMEOUT_GYRO);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	return data;
}

uint8_t GET_X_H(SPI_HandleTypeDef hspi_in){
	uint8_t data;
	uint8_t address = 0x29 | 0x80;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi_in, &address, 1, TIMEOUT_GYRO);
	HAL_SPI_Receive(&hspi_in, &data, 1, TIMEOUT_GYRO);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	return data;
}

uint8_t GET_Y_L(SPI_HandleTypeDef hspi_in){
	uint8_t data;
	uint8_t address = 0x2A | 0x80;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi_in, &address, 1, TIMEOUT_GYRO);
	HAL_SPI_Receive(&hspi_in, &data, 1, TIMEOUT_GYRO);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	return data;
}

uint8_t GET_Y_H(SPI_HandleTypeDef hspi_in){
	uint8_t data;
	uint8_t address = 0x2B | 0x80;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi_in, &address, 1, TIMEOUT_GYRO);
	HAL_SPI_Receive(&hspi_in, &data, 1, TIMEOUT_GYRO);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	return data;
}

uint8_t GET_Z_L(SPI_HandleTypeDef hspi_in){
	uint8_t data;
	uint8_t address = 0x2C | 0x80;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi_in, &address, 1, TIMEOUT_GYRO);
	HAL_SPI_Receive(&hspi_in, &data, 1, TIMEOUT_GYRO);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	return data;
}

uint8_t GET_Z_H(SPI_HandleTypeDef hspi_in){
	uint8_t data;
	uint8_t address = 0x2D | 0x80;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi_in, &address, 1, TIMEOUT_GYRO);
	HAL_SPI_Receive(&hspi_in, &data, 1, TIMEOUT_GYRO);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	return data;
}
