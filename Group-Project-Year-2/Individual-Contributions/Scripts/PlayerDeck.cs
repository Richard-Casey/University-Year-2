using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerDeck : MonoBehaviour
{
    public GameObject aiCardPrefab;
    public GameObject playerCardPrefab;
    public Transform aiPlayerPanel;
    public Transform playerCardPanel;

    void Start()
    {
        if (CardDataBase.cardList.Count < 32)
        {
            Debug.LogError("Insufficient cards in the database.");
            return;
        }

        List<Card> shuffledCards = ShuffleCards(CardDataBase.cardList);

        for (int i = 0; i < 16; i++)
        {
            CreateAICard(shuffledCards[i]);
        }

        for (int i = 16; i < 32; i++)
        {
            CreatePlayerCard(shuffledCards[i]);
        }
    }

    void CreateAICard(Card cardData)
    {
        GameObject cardObject = Instantiate(aiCardPrefab, aiPlayerPanel);
        ThisCard cardScript = cardObject.GetComponent<ThisCard>();

        Card databaseCard = CardDataBase.cardList.Find(card => card.id == cardData.id);

        cardScript.thisCard.Add(databaseCard);
        cardScript.thisId = databaseCard.id;
        cardScript.cardBack = true;
    }

    void CreatePlayerCard(Card cardData)
    {
        GameObject playerCardObject = Instantiate(playerCardPrefab, playerCardPanel);
        ThisCard playerCard = playerCardObject.GetComponent<ThisCard>();
        playerCard.thisCard.Add(cardData);
    }

    List<Card> ShuffleCards(List<Card> cards)
    {
        List<Card> shuffledCards = new List<Card>(cards);
        for (int i = shuffledCards.Count - 1; i > 0; i--)
        {
            int randomIndex = Random.Range(0, i + 1);
            Card temp = shuffledCards[i];
            shuffledCards[i] = shuffledCards[randomIndex];
            shuffledCards[randomIndex] = temp;
        }
        return shuffledCards;
    }
}
