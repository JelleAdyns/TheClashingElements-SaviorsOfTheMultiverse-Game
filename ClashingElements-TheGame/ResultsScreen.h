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
	virtual void HandleControllerInput() override;

	virtual void OnEnter() override;
	virtual void OnExit() override {};
	virtual void OnSuspend() override {};
	virtual void OnResume() override {};
private:


	void CycleName(int virtualKeyCode);
	void CycleNameController();
	tstring GetInitials() const;

	std::unique_ptr<LoadScreenCommand> m_pLoadScreen;
	std::unique_ptr<PushScreenCommand> m_pPushScreen;

	tstring m_Name;
	tstring m_Score;
	tchar m_CurrentCharacter{ _T('.') };

	bool m_NameEntered{false};
	int m_NrOfEnters{};
	int m_RankedPosition{0};
	BackGround m_BackGround;

	KeybindString m_CycleText{ _T("Cycle: ARROWS \n Confirm: ENTER") ,_T("Cycle: DPAD\n Confirm: A ") };
	KeybindString m_ContinueText{ _T("Title screen: SPACE"),_T("Title screen: A") };
};

#endif // !RESULTSSCREEN_H