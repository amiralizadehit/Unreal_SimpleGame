// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	SetupGame();
	
	PrintLine(TEXT("Welcome to Bull Cow Game!")) ;
	PrintLine(FString::Printf(TEXT("The Hidde Word is: %s"),*HiddenWord));
	PrintLine(TEXT("Input something and press enter"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	ClearScreen();
	

	if(Input == HiddenWord)
	{
		PrintLine(TEXT("Won!"));
	}else
	{
		if(Input.Len() != HiddenWord.Len())
		{
			PrintLine(TEXT("Wrong number of characters"));
		}
		
		PrintLine(TEXT("Lose!"));
	}

	
}

void UBullCowCartridge::SetupGame()
{
	HiddenWord = TEXT("kire");
	Lives = 4;
}