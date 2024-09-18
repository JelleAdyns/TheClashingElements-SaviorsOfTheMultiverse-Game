#ifndef RESULTSSCREEN_H
#define RESULTSSCREEN_H

#include "Screen.h"
#include "Commands.h"
#include "Game.h"
#include "BackGround.h"

class ResultsScreen final : public Screen
{
public:
	explicit ResultsScreen(Game& game);
	virtual ~ResultsScreen() = default;

	ResultsScreen(const ResultsScreen& other) = delete;
	ResultsScreen(ResultsScreen&& other) noexcept = delete;
	ResultsScreen& operator=(const ResultsScreen& other) = delete;
	ResultsScreen& operator=(ResultsScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Tick() override;
	virtual void KeyInput(int virtualKeyCode) override;

	virtual void OnEnter() override;
	virtual void OnExit() override {};
	virtual void OnSuspend() override {};
	virtual void OnResume() override {};
private:
	void CycleName(int virtualKeyCode);
	tstring GetInitials() const;

	std::unique_ptr<LoadScreenCommand> m_pLoadScreen;
	std::unique_ptr<PushScreenCommand> m_pPushScreen;

	tstring m_Name;
	tstring m_Score;
	tchar m_CurrentCharacter{ _T('.') };

	bool m_NameEntered{false};

	BackGround m_BackGround;
};

#endif // !RESULTSSCREEN_H