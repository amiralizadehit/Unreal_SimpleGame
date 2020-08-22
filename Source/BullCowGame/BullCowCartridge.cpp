// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
	SetupGame();

	PrintLine(TEXT("The Hidde Word is: %s. It's %i characters long."), *HiddenWord, HiddenWord.Len());
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	if (bGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else
	{
		ProcessGuess(Input);
	}
}

void UBullCowCartridge::SetupGame()
{
	PrintLine(TEXT("Welcome to Bull Cow Game!"));

	HiddenWord = TEXT("kire");
	Lives = HiddenWord.Len();
	bGameOver = false;

	PrintLine(TEXT("The Hidden Word is %i characters long."), HiddenWord.Len());
	PrintLine(TEXT("You have %i lives."), Lives);
	PrintLine(TEXT("Type in your guess and press enter..."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("Won!"));
		EndGame();
		return;
	}

	
	if (Guess.Len() != HiddenWord.Len())
	{
		PrintLine(TEXT("The Hidden Word is %i characters long. Try again!"), HiddenWord.Len());
		return;
	}
	
	Lives--;
	PrintLine(TEXT("You lost a life!. %i live(s) left."), Lives);
	if (Lives == 0)
	{
		ClearScreen();
		PrintLine("You have no lives left!");
		PrintLine(TEXT("The Hidden Word was %s"), *HiddenWord);
		EndGame();
	}

	
}


void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("The game is over. \nPress enter to play again!"));
}
