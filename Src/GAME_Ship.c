///*
// * GAME_Ship.c
// *
// *  Created on: 16.04.2020
// *      Author: Dawid Kahla
// */
//
//#include "GAME_Ship.h"
//
////GAME_Ship GAME_Ship_create(uint16_t const scale, uint16_t x, uint16_t const y){
////	GAME_Ship ship;
////	ship.fig = PAW_Figure_create(0, 16, 16, 0);
////	ship.scale = scale;
////	ship.horizontal = x;
////	ship.vertical = y;
////	return ship;
////}
////
////void GAME_Ship_destr(GAME_Ship* ship){
////	PAW_Figure_destr(&ship->fig);
////}
////
////
////void GAME_Ship_draw(GAME_Ship* const ship, const uint32_t a_color){
////
////
////	const float width = ship->horizontal;
////	const float scale = ship->scale;
////
////	PAW_Vector P1 = {3, {width, 35*scale, 0.0f}};
////	PAW_Vector P2 = {3, {width+4*scale, 29*scale, 0.0f}};
////	PAW_Vector P3 = {3, {width+6*scale, 29*scale, 0.0f}};
////	PAW_Vector P4 = {3, {width+6*scale, 33.7*scale, 0.0f}};
////	PAW_Vector P5 = {3, {width+12*scale, 29*scale, 0.0f}};
////	PAW_Vector P6 = {3, {width+8*scale, 20*scale, 0.0f}};
////	PAW_Vector P7 = {3, {width+12*scale, 11*scale, 0.0f}};
////	PAW_Vector P8 = {3, {width+4*scale, 11*scale, 0.0f}};
////	PAW_Vector P9 = {3, {width, 5*scale, 0.0f}};
////	PAW_Vector P10 = {3, {width-4*scale, 11*scale, 0.0f}};
////	PAW_Vector P11 = {3, {width-12*scale, 11*scale, 0.0f}};
////	PAW_Vector P12 = {3, {width-8*scale, 20*scale, 0.0f}};
////	PAW_Vector P13 = {3, {width-12*scale, 29*scale, 0.0f}};
////	PAW_Vector P14 = {3, {width-6*scale, 29*scale, 0.0f}};
////	PAW_Vector P15 = {3, {width-6*scale, 33.7*scale, 0.0f}};
////	PAW_Vector P16 = {3, {width-4*scale, 29*scale, 0.0f}};
////
////	PAW_Line L1 = {a_color, false, P1, P2};
////
////	PAW_Line L2 = {a_color, false, P2, P3};
////
////	PAW_Line L3 = {a_color, false, P3, P4};
////
////	PAW_Line L4 = {a_color, false, P3, P5};
////
////	PAW_Line L5 = {a_color, false, P5, P6};
////
////	PAW_Line L6 = {a_color, false, P6, P7};
////
////	PAW_Line L7 = {a_color, false, P7, P8};
////
////	PAW_Line L8 = {a_color, false, P8, P9};
////
////	PAW_Line L9 = {a_color, false, P9, P10};
////
////	PAW_Line L10 = {a_color, false, P10, P11};
////
////	PAW_Line L11 = {a_color, false, P11, P12};
////
////	PAW_Line L12 = {a_color, false, P12, P13};
////
////	PAW_Line L13 = {a_color, false, P13, P14};
////
////	PAW_Line L14 = {a_color, false, P14, P15};
////
////	PAW_Line L15 = {a_color, false, P14, P16};
////
////	PAW_Line L16 = {a_color, false, P16, P1};
////
////
////	PAW_figure_push_line(ship->fig, L1);
////	PAW_figure_push_line(ship->fig, L2);
////	PAW_figure_push_line(ship->fig, L3);
////	PAW_figure_push_line(ship->fig, L4);
////	PAW_figure_push_line(ship->fig, L5);
////	PAW_figure_push_line(ship->fig, L6);
////	PAW_figure_push_line(ship->fig, L7);
////	PAW_figure_push_line(ship->fig, L8);
////	PAW_figure_push_line(ship->fig, L9);
////	PAW_figure_push_line(ship->fig, L10);
////	PAW_figure_push_line(ship->fig, L11);
////	PAW_figure_push_line(ship->fig, L12);
////	PAW_figure_push_line(ship->fig, L13);
////	PAW_figure_push_line(ship->fig, L14);
////	PAW_figure_push_line(ship->fig, L15);
////	PAW_figure_push_line(ship->fig, L16);
////
////}
////
////void GAME_Ship_show(GAME_Ship* const ship, const uint32_t buffer){
////	PAW_Figure_show(&ship->fig, buffer);
////}
//

