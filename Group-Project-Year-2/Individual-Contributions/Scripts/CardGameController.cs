using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CardGameController : MonoBehaviour
{

    public CardDealer cardDealer;
    private GameObject currentPlayerPanel;
    private GameObject currentOpponentPanel;
    private bool playerTurn;
    private GameObject selectedCard;
    private string selectedStat;

    // Start is called before the first frame update
    void Start()
    {
        playerTurn = cardDealer.playerPanel.transform.childCount > 0;
        currentPlayerPanel = playerTurn ? cardDealer.playerPanel : cardDealer.aiPanel;
        currentOpponentPanel = playerTurn ? cardDealer.aiPanel : cardDealer.playerPanel;

    }

    public void SelectStat(string statName)
    {
        if (selectedCard != null && playerTurn)
        {
            selectedStat = statName;
            Debug.Log("Player selected Stat: " + selectedStat);

            // Get the selected stat value from the selected card
            int selectedStatValue = GetStatValue(selectedCard, selectedStat);

            // Find the opponents card with the same category and compare the stats
            int opponentStatValue = GetHighestStatValue(currentOpponentPanel, selectedStat);

            // Determine the winner and take actions
            if (selectedStatValue > opponentStatValue)
            {
                Debug.Log("Player Wins!");
            }

            else if (selectedStatValue < opponentStatValue)
            {
                Debug.Log("AI Wins!");
            }

            else
            {
                Debug.Log("Draw!");
            }

            // Switch turns
            playerTurn = !playerTurn;
            currentPlayerPanel = playerTurn ? cardDealer.playerPanel : cardDealer.aiPanel;
            currentOpponentPanel = playerTurn ? cardDealer.aiPanel : cardDealer.playerPanel;

            // Clear the selected card and stat
            selectedCard = null;
            selectedStat = null;

            if (!playerTurn)
            {
                // AI's turn - randomly select a stat
                SelectRandomStat();
            }
        }
    }

    private void SelectRandomStat()
    {
        if (currentOpponentPanel.transform.childCount > 0)
        {
            // Select a random card from the opponent's panel
            int randomIndex = Random.Range(0, currentOpponentPanel.transform.childCount);
            GameObject randomCard = currentOpponentPanel.transform.GetChild(randomIndex).gameObject;

            // Get a random stat from the card
            Transform stats = randomCard.transform.Find("Stats");
            if (stats != null && stats.childCount > 0)
            {
                int randomStatIndex = Random.Range(0, stats.childCount);
                Transform stat = stats.GetChild(randomStatIndex);
                string statName = stat.name.Replace("StatText", "");

                // Trigger the stat selection in the CardGameController
                SelectStat(statName);
            }
        }
    }

    private int GetStatValue(GameObject card, string statName)
    {
        Transform stats = card.transform.Find("Stats");
        if (stats != null)
        {
            Transform stat = stats.Find(statName + "StatText");
            if (stat != null)
            {
                Text statText = stat.GetComponent<Text>();
                if (statText != null && int.TryParse(statText.text, out int value))
                {
                    return value;
                }
            }
        }
        return 0; // Return a default value if the stat is not found or cannot be parsed
    }

    private int GetHighestStatValue(GameObject parent, string statName)
    {
        int highestValue = int.MinValue;

        CardUI[] cards = parent.GetComponentsInChildren<CardUI>();
        foreach (CardUI card in cards)
        {
            Transform statsTransform = card.transform.Find("Stats");
            if (statsTransform != null)
            {
                Transform stat = statsTransform.Find(statName);
                if (stat != null)
                {
                    Text statText = stat.GetComponent<Text>();
                    if (statText != null)
                    {
                        int statValue;
                        if (int.TryParse(statText.text, out statValue))
                        {
                            highestValue = Mathf.Max(highestValue, statValue);
                        }
                    }
                }
            }
        }

        return highestValue;
    }

    public void SelectCard(CardUI card)
    {
        if (playerTurn)
        {
            // Store the selected card
            selectedCard = card.gameObject;

            // Add visual indication that the card is selected (maybe change colour?)
            card.SetSelected(true);

            Debug.Log("Player selected card: " + selectedCard.name);
        }
    }





}
