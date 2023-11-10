using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ThisCardObject : MonoBehaviour
{
    public Text cardNameText;
    public Text wingSpanText;
    public Text speedText;
    public Text strengthText;
    public Text weightText;
    public Text sizeText;
    public Image frameImage;

    private Card card;

    public void SetCard(Card card, Sprite cardImage)
    {
        this.card = card;
        GetComponent<RawImage>().texture = cardImage.texture;
    }

    public void UpdateCardDetails()
    {
        if (card != null)
        {
            cardNameText.text = " " + card.card_Name;
            wingSpanText.text = "WINGSPAN: " + card.wingSpan;
            speedText.text = "SPEED: " + card.speed;
            strengthText.text = "STRENGTH: " + card.strength;
            weightText.text = "WEIGHT: " + card.weight;
            sizeText.text = "SIZE: " + card.size;

            Material frameMaterial = frameImage.material;
            frameMaterial.SetTexture("_MainTex", GetComponent<RawImage>().texture);

            switch (card.color)
            {
                case "Red":
                    frameImage.color = new Color32(220, 20, 60, 255);
                    break;
                case "Green":
                    frameImage.color = new Color32(60, 179, 113, 255);
                    break;
                case "Yellow":
                    frameImage.color = new Color32(255, 255, 0, 255);
                    break;
                case "Rainbow":
                    frameImage.material = frameMaterial;
                    break;
                default:
                    Debug.LogWarning("Invalid color for the card.");
                    break;
            }
        }
        else
        {
            Debug.LogError("Card object is null.");
        }
    }
}
