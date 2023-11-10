using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ThisCard : MonoBehaviour
{
    public List<Card> thisCard = new List<Card>();

    public GameObject cardPrefab;

    public Sprite[] cardImages;
    public Material rainbowMaterial;

    void Start()
    {
        if (CardDataBase.cardList.Count < 32)
        {
            Debug.LogError("Insufficient cards in the database.");
            return;
        }

        cardImages = new Sprite[32];
        for (int i = 0; i < 32; i++)
        {
            cardImages[i] = Resources.Load<Sprite>((i + 1).ToString());
        }

        rainbowMaterial = Resources.Load<Material>("Rainbow");

        DealCards();
    }

    void DealCards()
    {
        if (thisCard.Count + 16 > CardDataBase.cardList.Count)
        {
            Debug.LogError("Not enough cards in the database to deal.");
            return;
        }

        thisCard.Clear();

        for (int i = 0; i < 16; i++)
        {
            thisCard.Add(CardDataBase.cardList[i]);
        }

        CardDataBase.cardList.RemoveRange(0, 16);

        ClearPile(transform);
        CreateCardObjects();

        UpdatePileDetails();
    }

    void ClearPile(Transform pile)
    {
        foreach (Transform child in pile)
        {
            Destroy(child.gameObject);
        }
    }

    void CreateCardObjects()
    {
        foreach (Card card in thisCard)
        {
            GameObject cardObject = Instantiate(cardPrefab, transform);
            ThisCardObject cardObjectScript = cardObject.GetComponent<ThisCardObject>();

            // Set cardObject's properties based on card details
            cardObjectScript.cardNameText.text = card.card_Name;
            cardObjectScript.wingSpanText.text = "WINGSPAN: " + card.wingSpan.ToString();
            cardObjectScript.speedText.text = "SPEED: " + card.speed.ToString();
            cardObjectScript.strengthText.text = "STRENGTH: " + card.strength.ToString();
            cardObjectScript.weightText.text = "WEIGHT: " + card.weight.ToString();
            cardObjectScript.sizeText.text = "SIZE: " + card.size.ToString();

            if (cardImages != null && cardImages.Length > card.id && cardImages[card.id] != null)
            {
                cardObjectScript.cardImage.sprite = cardImages[card.id];
            }
            else
            {
                Debug.LogError("Card image for ID " + card.id + " is missing or not assigned.");
            }

            // Set frame color or material based on card color
            Image frame = cardObjectScript.frameImage;

            if (frame != null)
            {
                switch (card.color)
                {
                    case "Grey":
                        frame.color = new Color32(128, 128, 128, 255);
                        break;
                    case "Blue":
                        frame.color = new Color32(135, 206, 250, 255);
                        break;
                    case "Red":
                        frame.color = new Color32(220, 20, 60, 255);
                        break;
                    case "Green":
                        frame.color = new Color32(173, 255, 47, 255);
                        break;
                    case "Gold":
                        frame.color = new Color32(212, 175, 55, 255);
                        break;
                    case "Rainbow":
                        frame.material = rainbowMaterial;
                        break;
                    default:
                        Debug.LogError("Unknown color for card ID " + card.id);
                        break;
                }
            }
        }
    }

    void UpdatePileDetails()
    {
        Text pileDetailsText = GetComponentInChildren<Text>();
        if (pileDetailsText != null)
        {
            pileDetailsText.text = "CARDS REMAINING: " + CardDataBase.cardList.Count.ToString();
        }
    }
}
