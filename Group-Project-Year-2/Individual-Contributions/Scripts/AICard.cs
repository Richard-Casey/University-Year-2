using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AICard : MonoBehaviour
{
    public List<Card> aiCards = new List<Card>(); // List to store AI cards
    public List<Card> playerCards = new List<Card>(); // List to store player cards

    public GameObject cardPrefab; // Prefab for card UI
    public Transform aiPlayerPanelTransform; // Transform of the AI player panel
    public Transform playerCardPanelTransform; // Transform of the player card panel

    void Start()
    {
        // Check if there are enough cards in the card database
        if (CardDataBase.cardList.Count < 32)
        {
            Debug.LogError("Insufficient cards in the database.");
            return;
        }

        // Shuffle the card database
        List<Card> shuffledCards = ShuffleCards(CardDataBase.cardList);

        // Assign the AI cards
        for (int i = 0; i < 16; i++)
        {
            aiCards.Add(shuffledCards[i]);
            CreateCardUI(shuffledCards[i], aiPlayerPanelTransform);
        }

        // Assign the player cards
        for (int i = 16; i < 32; i++)
        {
            playerCards.Add(shuffledCards[i]);
            CreateCardUI(shuffledCards[i], playerCardPanelTransform);
        }
    }

    void CreateCardUI(Card cardData, Transform parentTransform)
    {
        GameObject cardObject = Instantiate(cardPrefab, parentTransform); // Instantiate the card UI prefab
        ThisCard cardScript = cardObject.GetComponent<ThisCard>(); // Get the card script component

        // Find the card data in the CardDataBase script based on the card ID
        Card databaseCard = CardDataBase.cardList.Find(card => card.id == cardData.id);

        // Assign the card data to the card script
        cardScript.thisCard.Add(databaseCard);
        cardScript.thisId = databaseCard.id;
        cardScript.cardBack = (parentTransform == aiPlayerPanelTransform); // Set card back based on whether it's an AI card or not
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
