using UnityEngine;
using UnityEngine.EventSystems;

public class PlayerInputHandler : MonoBehaviour, IPointerClickHandler
{
    public GameObject selectedCard;

    // Update is called once per frame
    void Update()
    {
        if (CardManager.Instance.currentState != CardManager.GameState.PlayersTurn)
            return;  // if it's not the player's turn, don't process input

        if (Input.GetMouseButtonDown(0))
        {
            RaycastHit hit;
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

            if (Physics.Raycast(ray, out hit))
            {
                if (hit.transform.parent == CardManager.Instance.PlayerPanel)
                {
                    selectedCard = hit.transform.gameObject;
                    OnMouseDown();
                }
            }
        }
    }

    public void OnPointerClick(PointerEventData eventData)
    {
        if (CardManager.Instance.currentState != CardManager.GameState.PlayersTurn)
            return;  // if it's not the player's turn, don't process input

        // Enlarge card and move it to PlayerInspectPanel
        transform.localScale = new Vector3(2.5f, 2.5f, 2.5f);
        CardManager.Instance.MoveCardToPlayerInspectPanel(gameObject);
    }

    private void OnMouseDown()
    {
        if (selectedCard != null)
        {
            // Enlarge card and move it to PlayerInspectPanel
            selectedCard.transform.localScale = new Vector3(2.5f, 2.5f, 2.5f);
            CardManager.Instance.MoveCardToPlayerInspectPanel(selectedCard);
        }
    }
}