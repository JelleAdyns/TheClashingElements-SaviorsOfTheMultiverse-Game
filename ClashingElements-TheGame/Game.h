#ifndef GAME_H
#define GAME_H

#include "Engine.h"
#include "GlobalEnumClasses.h"
#include "Screen.h"
#include "queue"

class Game final: public BaseGame
{
public:
    Game() = default;
    virtual ~Game() = default;

    Game(const Game& other) = delete;
    Game(Game&& other) noexcept = delete;
    Game& operator=(const Game& other) = delete;
    Game& operator=(Game&& other) noexcept = delete;

    virtual void Initialize() override;
    virtual void Cleanup() override;

    virtual void Draw() const override;
    virtual void Tick() override;
    virtual void KeyDown(int virtualKeycode) override;
    virtual void KeyDownThisFrame(int virtualKeycode) override;
    virtual void KeyUp(int virtualKeycode) override;
    virtual void HandleControllerInput() override;
    virtual void MouseDown(bool isLeft, int x, int y) override;
    virtual void MouseUp(bool isLeft, int x, int y) override;
    virtual void MouseMove(int x, int y, int keyDown) override;
    virtual void MouseWheelTurn(int x, int y, int turnDistance, int keyDown) override;
    
    enum class ScreenOperation
    {
        Set,
        Push,
        Pop
    };

    // FUNCTIONS
    void SetScreen(GameState newGameState);
    void AddOperationToQueue(ScreenOperation screenOper);

private:
    // VARIABLES
    
    GameState m_GameState{ GameState::Start };
    std::vector<std::pair<GameState,std::unique_ptr<Screen>>> m_pScreenStack{};

    std::queue<std::pair<GameState,ScreenOperation>> m_ScreenEventQueue{};

    bool m_UpdateScreen{ false };
    bool m_DebugScale{ false };

    // FUNCTIONS
    void DrawScreens() const;
    void LoadScreen();
    void PushScreen();
    void PopScreen();
    void HandleEventQueue();
};

#endif // !GAME_H