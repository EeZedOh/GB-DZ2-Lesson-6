#pragma once
#include <iostream>
#include <vector>

/*HomeWork3
����������� ����� Player, ������� ��������� �� ������ GenericPlayer. � ����� ������ ����� 4 ������:
1. virtual bool IsHitting() const - ���������� ����� ����������� ������� �������� ������.
����� ���������� � ������������, ����� �� ��� ��� ���� ����� � ���������� ����� ������������ � ���� true ��� false.
2. void Win() const - ������� �� ����� ��� ������ � ���������, ��� �� �������.
3. void Lose() const - ������� �� ����� ��� ������ � ���������, ��� �� ��������.
4. void Push() const - ������� �� ����� ��� ������ � ���������, ��� �� ������ ������.
*/

/*HomeWork4
����������� ����� House, ������� ������������ ������.
���� ����� ��������� �� ������ GenericPlayer.
� ���� ���� 2 ������:
1. virtual bool IsHitting() const - ����� ���������, ����� �� ������ ��� ���� �����. ���� � ������ �� ������ 16 �����, �� �� ����� ��� ���� �����.
2. void FlipFirstCard() - ����� �������������� ������ ����� ������.
*/

/*HomeWork5
�������� ���������� ��������� ������ ��� ������ Card.
���� ����� ����������� �������� ����� (�� �� �� �����), ������� ��, ���� �� �� �����, ������� ����� � ������� �����.
����� ��� ������ GenericPlayer �������� ���������� ��������� ������, ������� ������ ���������� ��� ������ � ��� �����, � ����� ����� ����� ����� ��� ����.
*/


enum Suits {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

enum Ranks {
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

class Card
{
protected:
    Suits suit = CLUBS;
    Ranks rank = ACE;
    bool isFaceUp = false;
public:
    Card() {}
    Card(Ranks inputRank, Suits inputSuit)
        : suit(inputSuit), rank(inputRank)
    {

    }
    void Flip()
    {
        isFaceUp = !isFaceUp;
    }

    Ranks getValue()
    {
        return rank;
    }

    Suits getSuit()
    {
        return suit;
    }

    //dz5

    friend std::ostream& operator<<(std::ostream& out, const Card& card);
};

std::ostream& operator<<(std::ostream& out, const Card& card)
{
    if (card.isFaceUp)
    {
        out << "\n" << card.rank << " " << card.suit;
    }
    else out << "XX";
    return out;
}

// ====================================================================================

class Hand
{
protected:
    std::vector<Card*> hand;
public:
    void Add(Card* input)
    {
        hand.push_back(input);
    }

    void Clear()
    {
        hand.clear();
    }

    int GetValue() const
    {
        int sum = 0;
        for (Card* card : hand)
        {
            sum += card->getValue();
        }
        return sum;
    }
};

class GenericPlayer : public Hand
{
protected:
    std::string name;
public:
    GenericPlayer(std::string inputName)
        : name(inputName) {}

    virtual bool IsHitting() const = 0;

    bool IsBoosted() const
    {
        if (GetValue() > 21) return true;
        else return false;
    }

    void Bust()
    {
        std::cout << "\n" << name << " is Bust!\n";
    }

    // dz5

    friend std::ostream& operator<<(std::ostream& out, const GenericPlayer& genericPlayer);
};

std::ostream& operator<<(std::ostream& out, const GenericPlayer& genericPlayer)
{
    out << "\n" << genericPlayer.name << " has:\n";
    for (Card* card : genericPlayer.hand)
    {
        out << card->getValue() << " " << card->getSuit() << "\n";
    }
    out << genericPlayer.GetValue();
    return out;
}

//dz3

class Player : virtual public GenericPlayer
{
public:
    Player(std::string inputName)
        : GenericPlayer(inputName) {}
    virtual bool IsHitting() const override
    {
        while (true)
        {
            std::cout << "\nTake another card? (Y/N): ";
            char* input = 0;
            std::cin >> input;
            if (std::cin && input == "Y") return true;
            else if (std::cin && input == "N") return false;
            else
            {
                system("cls");
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Incorrect input!";
            }
        }
    }

    void Win() const
    {
        std::cout << "\n" << name << " have Won!";
    }

    void Lose() const
    {
        std::cout << "\n" << name << " have Lost.";
    }

    void Push() const
    {
        std::cout << "\n" << name << " played a Draw";
    }
};

//dz4

class House : virtual public GenericPlayer
{
public:
    House()
        : GenericPlayer("Diler") {}

    virtual bool IsHitting() const override
    {
        if (GetValue() <= 16) return true;
        else return false;
    }

    void FlipFirstCard()
    {
        hand.front()->Flip();
    }
};