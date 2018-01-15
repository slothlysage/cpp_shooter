/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 23:10:41 by sjones            #+#    #+#             */
/*   Updated: 2018/01/13 15:10:55 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "Player.hpp"
#include <unistd.h>
#include <signal.h>
#define FRAME_RATE 60
#define CLOCKS_PER_FRAME (CLOCKS_PER_SEC / FRAME_RATE)

int	gameLoop(Game *game, Player *player) {
	int ch;
	static clock_t lastSec = 0;
	static int FPS = 0;
	static int frames = 0;
	clock_t now = clock();

	frames++;
	if (lastSec / CLOCKS_PER_SEC != now / CLOCKS_PER_SEC)
	{
		game->addTimer();
		clear();
		game->alignPlayer(player);
		game->spawn();
		lastSec = now;
		FPS = frames;
		frames = 0;
	}
	game->drawBorder();
	ch = getch();
	game->move(player, ch);
	game->score(player, FPS);
	refresh();
	game->checkEnd(player);
	if (ch == ESC || game->isEnd())
		return (0);
	while(clock() / CLOCKS_PER_FRAME == now / CLOCKS_PER_FRAME) {}
	return (1);
}

int main() {
	Game *game = new Game;
	Player *player = new Player;
	bool playing = true;
	game->loadScreen();
	while (playing) {
		playing = game->menu();
		clear();
		system("afplay sfx/music.mp3 &");
		while (playing && gameLoop(game, player)) {}
		game->resetGame(player);
	}
	game->loadScreen();
	delete(game);
	delete(player);
	return (0);
	}
