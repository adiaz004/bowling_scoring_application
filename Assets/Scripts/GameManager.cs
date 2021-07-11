using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
 * This singleton class will manage the entire game.
 */
public class GameManager : MonoBehaviour
{
    public static event Action<GameState> OnGameStateChanged;
    private static GameManager instance = null;


    public static GameState State;

    /*
     * Handler to do whatever needs to be done base on the new state that 
     * we're switching over too.
     */
    public void UpdateGameState (GameState newState)
    {
        State = newState;
        switch(newState)
        {
            case GameState.GameMenu:
                break;
            case GameState.GameInProgress:
                break;
            case GameState.GameOver:
                break;
            default:
                throw new ArgumentOutOfRangeException(nameof(newState), newState, null);
        }
        OnGameStateChanged(newState);

    }

    /*
     * Since we're first starting up, set the GameMenu as the first state.
     */
    void Start()
    {
        UpdateGameState(GameState.GameMenu);
    }

    public static GameManager Instance
    {
        get
        {
            if (GameManager.instance == null)
            {
                DontDestroyOnLoad(GameManager.instance);
                GameManager.instance = new GameManager();
            }
            return GameManager.instance;
        }

    }
}

/*
 * enum used to define all states of this app
 */
public enum GameState
{
    GameMenu,
    GameInProgress,
    GameOver
}
