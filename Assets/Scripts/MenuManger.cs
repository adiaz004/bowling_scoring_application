using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


/*
 * This manager is used to drive all behavior going on in the Main Menu.
 */
public class MenuManger : MonoBehaviour
{
    GameManager gameManager = null;
    void Awake()
    {
        gameManager = GameManager.Instance;
        GameManager.OnGameStateChanged += GameManagerOnGameStateChanged;
    }

    void OnDestroy()
    {
        GameManager.OnGameStateChanged -= GameManagerOnGameStateChanged;

    }
    // Start is called before the first frame update
    void Start()
    {

    }

    private void GameManagerOnGameStateChanged(GameState state)
    {
        SceneManager.LoadScene("mainMenuScene");
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void NewGame()
    {

    }
    public void QuitGame()
    {
        Application.Quit();
    }
}
