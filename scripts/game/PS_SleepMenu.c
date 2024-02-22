modded enum ChimeraMenuPreset : ScriptMenuPresetEnum
{
	SleepMenu
}

//------------------------------------------------------------------------------------------------
//! Fullscreen map menu
class PS_SleepMenu: ChimeraMenuBase
{
	PS_GameModeCoop m_GameModeCoop;
	
	override void OnMenuOpen()
	{
		m_GameModeCoop = PS_GameModeCoop.Cast(GetGame().GetGameMode());
	}
	
	override void OnMenuUpdate(float tDelta)
	{
		if (m_GameModeCoop.m_bFreezeTimeEnd) 
			Close();
	}
};