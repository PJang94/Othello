// Player.h - Othello player class declaration
// Written by Paul Jang

#pragma once

class Player
{
public:
	// default constructor, takes the color and AI bool as arguments
	Player(char color, bool ai)
	{
		Color = color;
		AI = ai;
	}

	// sets the color of the player, takes the color as an argument
	void setColor(char color)
	{
		Color = color;
	}

	// sets whether or not the player is an AI, takes the AI bool as an argument
	void setAI(bool ai)
	{
		AI = ai;
	}

	// returns the color of the player
	char getColor() const
	{
		return Color;
	}

private:
	// the color of the player
	char Color;

	// whether or not the player is an AI
	bool AI;
};