#include "Gamepad.h"

// Link the 'Xinput' library - Important!
#pragma comment(lib, "Xinput.lib");

// Default constructor
Gamepad::Gamepad() 
{
	// Return gamepad state
	XINPUT_STATE Gamepad::GetState()
	{
		// Return true if the gamepad is connected
		bool Gamepad::Connected()
		{
			// Zero memory
			ZeroMemory(&m_State, sizeof(XINPUT_STATE));

			// Get the state of the gamepad
			DWORD Result = XInputGetState(m_iGamepadIndex, &m_State);

			if (Result == ERROR_SUCCESS)
				return true;  // The gamepad is connected
			else
				return false; // The gamepad is not connected
		}
		// Update gamepad state
		void Gamepad::Update()
		{
			m_State = GetState(); // Obtain current gamepad state
		}
		// The left stick is outside of its deadzone
		if (!LStick_InDeadzone())
		{
			// Use left stick input here...
		}
	}
}

// Overloaded constructor
Gamepad::Gamepad(int a_iIndex)
{
	// Return gamepad index
	int Gamepad::GetIndex()
	{
		return m_iGamepadIndex;
	}
}