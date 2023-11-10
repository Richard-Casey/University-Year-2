using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class CardStats : MonoBehaviour
{
    public Text StrengthStat;
    public Text SpeedStat;
    public Text SizeStat;
    public Text WingspanStat;
    public Text WeightStat;

    public int selectedStatValue;
    
    public GameObject cardCover;

    private const float hoverHeight = 30f;
    private bool isHovering = false;

    private Vector3 originalPosition;
    private Vector3 raisedPosition;
    private float raiseAmount = 30f;
    private float moveDuration = 0.2f;

    private void OnMouseEnter()
    {
        if (!isHovering && transform.parent == CardManager.Instance.PlayerPanel)
        {
            // Raise the card when the mouse enters and it's in the PlayerPanel
            StartCoroutine(MoveCard(raisedPosition));
            isHovering = true;
        }
    }

    private void OnMouseExit()
    {
        if (isHovering && transform.parent == CardManager.Instance.PlayerPanel)
        {
            // Lower the card when the mouse exits and it's in the PlayerPanel
            StartCoroutine(MoveCard(originalPosition));
            isHovering = false;
        }
    }

    public void SetOriginalPosition(Vector3 position)
    {
        originalPosition = position;
    }

    public void SetRaisedPosition(Vector3 position)
    {
        raisedPosition = position;
    }

    private IEnumerator MoveCard(Vector3 targetPosition)
    {
        float elapsedTime = 0f;
        Vector3 startingPosition = transform.position;

        while (elapsedTime < moveDuration)
        {
            transform.position = Vector3.Lerp(startingPosition, targetPosition, elapsedTime / moveDuration);
            elapsedTime += Time.deltaTime;
            yield return null;
        }

        transform.position = targetPosition;
    }
}