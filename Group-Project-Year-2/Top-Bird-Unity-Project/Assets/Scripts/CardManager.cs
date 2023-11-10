using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using UnityEditor.Experimental.GraphView;

public class CardManager : MonoBehaviour
{
    public static CardManager Instance;

    public Transform PlayerPanel;
    public Transform AIPanel;
    public Transform AISelectPanel; // Add reference to the AISelectPanel in the Inspector
    public Transform PlayerInspectPanel;

    public Button StrengthButton;
    public Button SpeedButton;
    public Button SizeButton;
    public Button WeightButton;
    public Button WingspanButton;
    public Button BackButton;


    public GameObject[] cardPrefabs;
    
    public GameState currentState;
    
    public int aiPairs = 0;
    public int playersPairs = 0;

    private PlayerInputHandler playerInputHandler;
    private List<GameObject> deck;

    private CardStats playerSelectedCardStat;
    private CardStats aiSelectedCardStat;

    
    private Dictionary<GameObject, Vector3> originalPositions = new Dictionary<GameObject, Vector3>();
    private Dictionary<GameObject, Vector3> raisedPositions = new Dictionary<GameObject, Vector3>();

    public enum GameState
    {
        PlayersTurn,
        AIsTurn,
        GameOver
    }

    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
        }
        else
        {
            Destroy(gameObject);
        }
    }

    private void Start()
    {
        InitializeDeck();
        Debug.Log("Deck Initialized");
        DealCards();
        Debug.Log("Cards have been shuffled and dealt.");
        playerInputHandler = FindObjectOfType<PlayerInputHandler>();

        // Determine who has been dealt the WRIGGLEBEAK card and therefore who goes first
        currentState = CheckPlayerGoesFirst() ? GameState.PlayersTurn : GameState.AIsTurn;

        if (currentState == GameState.PlayersTurn)
        {
            Debug.Log("You have the magical super duper rainbow card - you go first!");
            StartCoroutine(PlayerMakeMove());
        }
        else
        {
            Debug.Log("AI got the rainbow card - lucky bugger. They're going first!");
            StartCoroutine(AIMakeMove());
        }
    }

    private IEnumerator AIMakeMove()
    {

        // Add any AI thinking time here, for example:
        yield return new WaitForSeconds(1.5f);

        // Check if the AI has any cards left
        if (AIPanel.childCount > 0)
        {
            // Get a random card from the AI's panel
            int randomCardIndex = Random.Range(0, AIPanel.childCount);
            Transform cardTransform = AIPanel.GetChild(randomCardIndex);
            CardStats cardStats = cardTransform.GetComponent<CardStats>();

            // Set the AI's selected card stats
            aiSelectedCardStat = cardStats;

            // Get the list of Text fields (stats) from the selected card
            List<Text> statFields = new List<Text>
        {
            cardStats.StrengthStat,
            cardStats.SpeedStat,
            cardStats.SizeStat,
            cardStats.WingspanStat,
            cardStats.WeightStat
        };

            // Select a random stat from the list
            int randomStatIndex = Random.Range(0, statFields.Count);
            Text selectedStat = statFields[randomStatIndex];

            // Print the name of the selected card and the stat field
            Debug.Log("AI selected card: " + cardStats.name.Replace("(Clone)", "") + ", " + selectedStat.name.Substring(0, selectedStat.name.Length - "Stat".Length) + ": " + selectedStat.text);

            // Disable the CardStats script on the card so it won't update the text fields
            cardStats.enabled = false;

            // Move the selected card to the AISelectPanel 
            MoveCardToAISelectPanel(cardTransform.gameObject);

            // Disable the Image component of the selected card
            Image cardImage = cardTransform.GetComponent<Image>();
            if (cardImage != null)
            {
                cardImage.enabled = false;
            }

            //aiSelectedCard = cardTransform.gameObject;
            aiSelectedCardStat.selectedStatValue = int.Parse(selectedStat.text);

        }
        else
        {
            // If the AI has no cards left, the game is over
            currentState = GameState.GameOver;
            Debug.Log("AI has no cards left. Game over!");
        }

        // After AI's move, switch back to player's turn
        if (currentState != GameState.GameOver)
        {
            yield return StartCoroutine(PlayerMakeMove());
        }
        else
        {
            GameOver();
        }
    }


    private bool CheckPlayerGoesFirst()
    {
        // Search through the PlayerPanel to check if the "WRIGGLEBEAK(Clone)" card is in there
        foreach (Transform cardTransform in PlayerPanel)
        {
            CardStats cardStats = cardTransform.GetComponent<CardStats>();
            if (cardStats != null && cardStats.name == "WRIGGLEBEAK(Clone)")
            {
                return true;
            }
        }

        // If not found in PlayerPanel, it's AI's turn
        return false;
    }

    private void InitializeDeck()
    {
        deck = new List<GameObject>();
        foreach (GameObject cardPrefab in cardPrefabs)
        {
            deck.Add(cardPrefab);
        }
        ShuffleDeck();
    }

    private void ShuffleDeck()
    {
        int n = deck.Count;
        while (n > 1)
        {
            n--;
            int k = Random.Range(0, n + 1);
            GameObject tempCard = deck[k];
            deck[k] = deck[n];
            deck[n] = tempCard;
        }
    }

    private void DealCards()
    {
        int cardsPerPanel = 16;
        int totalCardsToDeal = cardsPerPanel * 2;
        int cardsDealt = 0;
        bool wrigglebeakFound = false;

        while (cardsDealt < totalCardsToDeal)
        {
            int randomIndex = Random.Range(0, deck.Count);
            GameObject cardPrefab = deck[randomIndex];

            GameObject cardInstance = Instantiate(cardPrefab);
            CardStats cardStats = cardInstance.GetComponent<CardStats>();

            Transform destinationPanel = (cardsDealt % 2 == 0) ? PlayerPanel : AIPanel;
            cardInstance.transform.SetParent(destinationPanel, false);

            // Access the CardStats component to set card information
            cardStats.StrengthStat.text = cardStats.StrengthStat.text;
            cardStats.SpeedStat.text = cardStats.SpeedStat.text;
            cardStats.SizeStat.text = cardStats.SizeStat.text;
            cardStats.WeightStat.text = cardStats.WeightStat.text;
            cardStats.WingspanStat.text = cardStats.WingspanStat.text;
            // ... (and so on for other stats)

            // Enable the CardCover Image component for cards dealt to AIPanel
            if (destinationPanel == AIPanel)
            {
                // Get the CardCover GameObject from the card prefab (assuming it's a direct child)
                Transform cardCover = cardInstance.transform.Find("CardCover");
                if (cardCover != null)
                {
                    // Get the Image component from the CardCover GameObject
                    Image cardCoverImage = cardCover.GetComponent<Image>();
                    if (cardCoverImage != null)
                    {
                        cardCoverImage.enabled = true;
                    }
                }
            }

            // Set the position of the card instance before calling SetOriginalPosition
            cardInstance.transform.position = destinationPanel.position;

            // Set the original position of the card to its new position
            cardStats.SetOriginalPosition(destinationPanel.position);

            deck.RemoveAt(randomIndex);
            cardsDealt++;

            // Check if "WRIGGLEBEAK(Clone)" is found in PlayerPanel
            if (!wrigglebeakFound && cardStats.name == "WRIGGLEBEAK(Clone)" && destinationPanel == PlayerPanel)
            {
                wrigglebeakFound = true;
            }
        }

        // Set the currentState based on the presence of "WRIGGLEBEAK(Clone)" in PlayerPanel
        currentState = wrigglebeakFound ? GameState.PlayersTurn : GameState.AIsTurn;

        // If you want to use GridLayoutGroup, set it to Force Update
        PlayerPanel.GetComponent<GridLayoutGroup>().CalculateLayoutInputVertical();
        AIPanel.GetComponent<GridLayoutGroup>().CalculateLayoutInputVertical();
    }

    private void MoveCardToAISelectPanel(GameObject card)
    {
        card.transform.SetParent(AISelectPanel, false);

        // Find the CardCover GameObject inside the card and disable its Image component
        Transform cardCover = card.transform.Find("CardCover");
        if (cardCover != null)
        {
            Image cardCoverImage = cardCover.GetComponent<Image>();
            if (cardCoverImage != null)
            {
                cardCoverImage.enabled = false;
            }
        }
    }

    public void MoveCardToPlayerInspectPanel(GameObject card)
    {
        if (currentState == GameState.PlayersTurn)
        {
            // Get it out of the PlayerPanel
            card.transform.SetParent(null);

            // Set the new parent to the PlayerInspectPanel
            card.transform.SetParent(PlayerInspectPanel);

            // Enlarge the card
            card.transform.localScale = Vector3.one * 2.5f;

            ShowButtons();
        }
    }

    private void CompareCards()
    {
        if (playerSelectedCardStat.selectedStatValue > aiSelectedCardStat.selectedStatValue)
        {
            // Player wins the pair
            Debug.Log("Player wins the pair.");

            //Update game state and pairs counter
            currentState = GameState.PlayersTurn;
            playersPairs++;
            
        }
        else if (aiSelectedCardStat.selectedStatValue > playerSelectedCardStat.selectedStatValue)
        {
            // Ai wins the pair
            Debug.Log("AI Wins the pair.");

            // Update Game state and pairs counted
            currentState = GameState.AIsTurn;
            aiPairs++;
        }
        else
        {
            // Its a draw
            Debug.Log("Its a draw!");

            // In the event of a draw both cards are removed from the table and no points or pairs are awarded
            currentState = GameState.PlayersTurn;
        }


    }

    private IEnumerator PlayerMakeMove()
    {
        // Wait for the players input
        while (playerInputHandler.selectedCard == null)
        {
            yield return null;
        }

        // Get the CardStats from the selected card
        CardStats cardStats = playerInputHandler.selectedCard.GetComponent<CardStats>();

        // Set the player's selected card stats
        playerSelectedCardStat = cardStats;

        // Move the selected card to the Pl;ayerSelectPanel
        MoveCardToPlayerInspectPanel(playerInputHandler.selectedCard);

        CompareCards();
    }


    private void GameOver()
    {
        if (playersPairs > aiPairs)
        {
            Debug.Log("Player wins the game!");
        }
        else if (aiPairs > playersPairs)
        {
            Debug.Log("AI Wins the game");
        }
        else
        {
            Debug.Log("The game is a draw");
        }
    }

    void SelectPlayerStat(Text selectedStat)
    {
        playerSelectedCardStat.selectedStatValue = int.Parse(selectedStat.text);
    }

    public void SelectStrength()
    {
        // Assuming the PlayerInspectPanel has only one child (the selected card)
        CardStats cardStats = PlayerInspectPanel.GetChild(0).GetComponent<CardStats>();
        cardStats.selectedStatValue = int.Parse(cardStats.StrengthStat.text);
        Debug.Log("Strength selected: " + cardStats.selectedStatValue);
    }

    public void SelectSpeed()
    {
        CardStats cardStats = PlayerInspectPanel.GetChild(0).GetComponent<CardStats>();
        cardStats.selectedStatValue = int.Parse(cardStats.SpeedStat.text);
        Debug.Log("Speed selected: " + cardStats.selectedStatValue);
    }

    public void SelectSize()
    {
        CardStats cardStats = PlayerInspectPanel.GetChild(0).GetComponent<CardStats>();
        cardStats.selectedStatValue = int.Parse(cardStats.SizeStat.text);
        Debug.Log("Size selected: " + cardStats.selectedStatValue);
    }

    public void SelectWeight()
    {
        CardStats cardStats = PlayerInspectPanel.GetChild(0).GetComponent<CardStats>();
        cardStats.selectedStatValue = int.Parse(cardStats.WeightStat.text);
        Debug.Log("Weight selected: " + cardStats.selectedStatValue);
    }

    public void SelectWingspan()
    {
        CardStats cardStats = PlayerInspectPanel.GetChild(0).GetComponent<CardStats>();
        cardStats.selectedStatValue = int.Parse(cardStats.WingspanStat.text);
        Debug.Log("Wingspan selected: " + cardStats.selectedStatValue);
    }

    public void BackButtonPressed()
    {
        // Do whatever you want to do when the back button is pressed
        Debug.Log("Back button pressed");

        // Hide the buttons.
        HideButtons();
    }


    public void ShowButtons()
    {
        GameObject strengthButton = GameObject.Find("StrengthButton");
        GameObject speedButton = GameObject.Find("SpeedButton");
        GameObject sizeButton = GameObject.Find("SizeButton");
        GameObject weightButton = GameObject.Find("WeightButton");
        GameObject wingspanButton = GameObject.Find("WingspanButton");
        GameObject backButton = GameObject.Find("BackButton");

        if (strengthButton != null && speedButton != null && sizeButton != null && weightButton != null &&
            wingspanButton != null && backButton != null)
        {
            strengthButton.SetActive(true);
            sizeButton.SetActive(true);
            speedButton.SetActive(true);
            weightButton.SetActive(true);
            wingspanButton.SetActive(true);
            backButton.SetActive(true);
        }
        else
        {
            Debug.LogError("Buttons not found!");
        }

    }

    public void HideButtons()
    {
        StrengthButton.gameObject.SetActive(false);
        SpeedButton.gameObject.SetActive(false);
        SizeButton.gameObject.SetActive(false);
        WeightButton.gameObject.SetActive(false);
        WingspanButton.gameObject.SetActive(false);
        BackButton.gameObject.SetActive(false);
    }

    public void OnCardClicked(GameObject card)
    {
        if (currentState == GameState.PlayersTurn)
        {
            MoveCardToPlayerInspectPanel(card);
        }
    }

}
