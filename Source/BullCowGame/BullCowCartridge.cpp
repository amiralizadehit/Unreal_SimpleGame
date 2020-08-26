// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
//#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();


	//Loading Hidden Word List from a file into an array in runtime...
	const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
	TArray<FString> temp;
	FFileHelper::LoadFileToStringArray(temp, *WordListPath);
	
	Words = temp.FilterByPredicate([&](const FString& Word)
	{
		return IsValidWord(Word);
	});

	SetupGame();

	PrintLine(TEXT("The Hidden Word is: %s. It's %i characters long."), *HiddenWord, HiddenWord.Len());
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

	HiddenWord = Words[FMath::RandRange(0, Words.Num() - 1)];
	Lives = HiddenWord.Len();
	bGameOver = false;

	PrintLine(TEXT("The Hidden Word is %i characters long."), HiddenWord.Len());
	PrintLine(TEXT("You have %i lives."), Lives);
	PrintLine(TEXT("Type in your guess and press enter..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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

	if(!IsIsogram(Guess))
	{
		PrintLine(TEXT("No repeating letters, guess again"));
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
	auto Count = GetBullCows(Guess);

	PrintLine(TEXT("Number of Cows: %i, Number of Bulls: %i"), Count.Cows, Count.Bulls);
	
}

bool UBullCowCartridge::IsValidWord(const FString& Word) const
{
	auto WordLen = Word.Len();
	return IsIsogram(Word) && WordLen >= 4 && WordLen <= 8;
}


bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
	int32 Len = Word.Len();

	for(int32 i=0; i<Len-1; i++)
	{
		for(int32 j=i+1; j<Len; j++)
		{
			if(Word[i]== Word[j])
			{
				return false;
			}
		}
	}
	return true;
}


void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("The game is over. \nPress enter to play again!"));
}

FBUllCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
	FBUllCowCount Count{ 0, 0 };

	for(int32 i=0; i<Guess.Len(); i++)
	{
		if (Guess[i] == HiddenWord[i])
			Count.Bulls++;
		else
		{
			for(int32 j=0; j<HiddenWord.Len(); j++)
			{ 
				if (Guess[i] == HiddenWord[j])
				{
					Count.Cows++;
					break;
				}
					
			}
		}
	}
	return Count;
}

