// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    HiddenWordList = GetValidWords(Words);

    InitGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(bGameOver == true)
    {
        ClearScreen();
        InitGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::InitGame()
{
    HiddenWord = GetValidWords(Words)[FMath::RandRange(0,HiddenWordList.Num()-1)];
    Lives = HiddenWord.Len();
    bGameOver = false;
    //Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cow Game"));
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Guess the %i letters word"), HiddenWord.Len());
    PrintLine(TEXT("Press ENTER to Continue"));
    PrintLine(TEXT("The Hiddenword is : %s"), *HiddenWord);
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    //compare the input to hiddenworld
    if(HiddenWord == Guess)
    {
        PrintLine(TEXT("You Win"));
        EndGame();
        return;
    }

    if(Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The length of the character is %i"), HiddenWord.Len());
        PrintLine(TEXT("You still have %i lives, try again"), Lives);
        return;
    }

    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("The word is isogram"));
        PrintLine(TEXT("You still have %i lives, try again"), Lives);
        return;
    }

    --Lives;
    
    FBullCowCount Score = GetBullCow(Guess);

    PrintLine("You Lost a Live");
    PrintLine(TEXT("You get %i Cow and %i Bull"), Score.Cows, Score.Bulls);

    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left"));
        PrintLine(TEXT("The HiddenWord was : %s"), *HiddenWord);
        PrintLine(TEXT("You Lose"));
        EndGame();
        return;
    }
    
    PrintLine(TEXT("You still have %i lives, try again"), Lives);//show life left
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for(int32 Comparison = i + 1; Comparison < Word.Len(); Comparison++)
        {
            if(Word[i] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    for(FString Words: WordList)
    {
        if(Words.Len() >= 4 && Words.Len() <= 8 && IsIsogram(Words))
        {
            ValidWords.Emplace(Words);
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCow(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 i = 0; i < Guess.Len(); i++)
    {
        if(Guess[i] == HiddenWord[i])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 j = 0; j < Guess.Len(); j++)
        {
            if(Guess[i] == HiddenWord[j])
            {
                Count.Cows++;
                break;
            }
        }
        
    }
    return Count;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress ENTER to play again"));
}