#ifndef GAME_H
#define GAME_H

#include "Engine.h"
#include "Level.h"
#include "GlobalEnumClasses.h"
#include "Screen.h"

class Game final: public BaseGame
{
public:
    Game();
    virtual ~Game();

    Game(const Game& other) = delete;
    Game(Game&& other) noexcept = delete;
    Game& operator=(const Game& other) = delete;
    Game& operator=(Game&& other) noexcept = delete;

    virtual void Initialize() override;
    virtual void Draw() const override;
    virtual void Tick() override;
    virtual void KeyDown(int virtualKeycode) override;
    virtual void KeyUp(int virtualKeycode) override;
    virtual void MouseDown(bool isLeft, int x, int y) override;
    virtual void MouseUp(bool isLeft, int x, int y) override;
    virtual void MouseMove(int x, int y, int keyDown) override;
    virtual void MouseWheelTurn(int x, int y, int turnDistance, int keyDown) override;
private:
    // VARIABLES

    GameState m_GameState{ GameState::Start };
    std::unique_ptr<Level> m_pLevel;
    std::unique_ptr<Screen> m_pScreen;

    bool m_DebugScale{ false };
    float m_DScale{ 0.25f };

    // FUNCTIONS
    void Initialize();
    void Cleanup();
    void ClearBackground() const;
};

#endif // !GAME_H