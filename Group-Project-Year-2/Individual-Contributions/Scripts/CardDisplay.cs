using UnityEngine;
using UnityEngine.UI;

public class CardDisplay : MonoBehaviour
{
    public Image baseColorImage;
    public Image cardImage;
    public Text cardNameText;
    public Text speedText;
    public Text sizeText;
    public Text strengthText;
    public Text weightText;
    public Text wingspanText;

    public void SetBaseColor(string color)
    {
        // Set the base color of the card
        // Example: baseColorImage.color = Color.red;
    }

    public void SetCardImage(Sprite image)
    {
        // Set the card image
        // Example: cardImage.sprite = image;
    }

    public void SetCardName(string name)
    {
        // Set the card name
        // Example: cardNameText.text = name;
    }

    public void SetCardStats(int speed, int size, int strength, int weight, int wingspan)
    {
        // Set the card stats
        // Example: speedText.text = "Speed: " + speed.ToString();
        //          sizeText.text = "Size: " + size.ToString();
        //          strengthText.text = "Strength: " + strength.ToString();
        //          weightText.text = "Weight: " + weight.ToString();
        //          wingspanText.text = "Wingspan: " + wingspan.ToString();
    }

    public void DisplayCardData()
    {
        // Display the card data
        // Example: baseColorImage.gameObject.SetActive(true);
        //          cardImage.gameObject.SetActive(true);
        //          cardNameText.gameObject.SetActive(true);
        //          speedText.gameObject.SetActive(true);
        //          sizeText.gameObject.SetActive(true);
        //          strengthText.gameObject.SetActive(true);
        //          weightText.gameObject.SetActive(true);
        //          wingspanText.gameObject.SetActive(true);
    }
}
