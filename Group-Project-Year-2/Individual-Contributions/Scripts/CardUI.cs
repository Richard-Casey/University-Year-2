using UnityEngine;
using UnityEngine.UI;

public class CardUI : MonoBehaviour
{
    private bool isHovering = false;
    private Vector3 hoverOffset;
    private Transform startingParent;
    private CardDealer cardDealer; // Reference to the CardDealer script
    private int startingSortingOrder;
    private bool isEnlarged = false;
    private Vector3 originalScale;
    private Vector3 scaledDownScale;

    private void Awake()
    {
        hoverOffset = Vector3.zero;
        cardDealer = FindObjectOfType<CardDealer>(); // Find the CardDealer script in the scene
        startingSortingOrder = GetComponent<Renderer>().sortingOrder;
        startingParent = transform.parent;
        originalScale = transform.localScale;
        scaledDownScale = originalScale * 0.75f; // Calculate the scaled-down scale
    }

    public void OnPointerEnter()
    {
        if (startingParent == cardDealer.playerPanel.transform && !isHovering)
        {
            // Store the current position as the hover offset
            hoverOffset = Vector3.up * 10f;
            transform.localPosition += hoverOffset;
            isHovering = true;
        }
    }

    public void OnPointerClick()
    {
        Debug.Log("Card clicked!");

        // Get the main camera
        Camera mainCamera = Camera.main;
        if (mainCamera == null)
        {
            Debug.LogWarning("Main camera not found!");
            return;
        }

        // Calculate the center position of the screen
        Vector3 centerScreenPosition = new Vector3(Screen.width * 0.5f, Screen.height * 0.5f, 0f);

        // Convert the center position from screen space to world space
        Vector3 centerWorldPosition = mainCamera.ScreenToWorldPoint(centerScreenPosition);

        // Find the playerPanel and aiPanel in the scene hierarchy
        GameObject playerPanel = GameObject.Find("playerPanel");
        GameObject aiPanel = GameObject.Find("aiPanel");
        if (playerPanel != null && aiPanel != null)
        {
            // Check if the card belongs to the playerPanel or aiPanel
            if (transform.IsChildOf(playerPanel.transform))
            {
                // Player's card clicked
                CardGameController cardGameController = FindObjectOfType<CardGameController>();
                if (cardGameController != null)
                {
                    // Trigger the card selection in the CardGameController
                    cardGameController.SelectCard(gameObject);
                }
            }
            else if (transform.IsChildOf(aiPanel.transform))
            {
                // AI's card clicked
                CardGameController cardGameController = FindObjectOfType<CardGameController>();
                if (cardGameController != null)
                {
                    
                }
            }
        }
        else
        {
            Debug.LogWarning("playerPanel or aiPanel not found!");
        }
    }









    public void ScaleDown(float scale)
    {
        transform.localScale = new Vector3(scale, scale, 1f);
    }

    private int GetHighestSortingOrder(GameObject parent)
    {
        int highestSortingOrder = int.MinValue;

        CardUI[] cards = parent.GetComponentsInChildren<CardUI>();
        foreach (CardUI card in cards)
        {
            Renderer cardRenderer = card.GetComponent<Renderer>();
            if (cardRenderer != null)
            {
                highestSortingOrder = Mathf.Max(highestSortingOrder, cardRenderer.sortingOrder);
            }
        }

        return highestSortingOrder;
    }

    public void SelectStat(string statName)
{
    Debug.Log("Player selected Stat: " + statName);

    
}

}
