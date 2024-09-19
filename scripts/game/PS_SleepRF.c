[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class PS_SleepRFComponentClass : ScriptComponentClass
{
}

class PS_SleepRFComponent : ScriptComponent
{
	PS_GameModeCoop m_GameModeCoop;
	//------------------------------------------------------------------------------------------------
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		if (m_GameModeCoop.m_bFreezeTimeEnd || PS_FreezeTimeCounter.s_iCurrentFreezeTime < 40000)
		{
			ClearEventMask(owner, EntityEvent.FRAME);
			return;
		}
		
		IEntity character = SCR_PlayerController.GetLocalControlledEntity();
		if (!character || character != GetOwner())
			return;
		
		FactionAffiliationComponent factionAffiliationComponent = FactionAffiliationComponent.Cast(character.FindComponent(FactionAffiliationComponent));
		if (!factionAffiliationComponent)
			return;
		
		Faction faction = factionAffiliationComponent.GetDefaultAffiliatedFaction();
		if (faction.GetFactionKey() != "RHS_AFRF")
			return;
		
		PS_SleepResistComponent sleepResistComponent = PS_SleepResistComponent.Cast(character.FindComponent(PS_SleepResistComponent));
		if (sleepResistComponent)
			return;
		
		SCR_EGameModeState gameModeState = m_GameModeCoop.GetState();
		if (gameModeState == SCR_EGameModeState.GAME)
		{
			MenuBase topMenu = GetGame().GetMenuManager().GetTopMenu();
			MenuBase fadeMenu = GetGame().GetMenuManager().FindMenuByPreset(ChimeraMenuPreset.FadeToGame);
			if (!topMenu || fadeMenu == topMenu)
			{
				GetGame().GetMenuManager().CloseMenuByPreset(ChimeraMenuPreset.FadeToGame);
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.SleepMenu);	
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_GameModeCoop = PS_GameModeCoop.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT | EntityEvent.FRAME);
	}
}

class PS_SleepResistComponentClass : ScriptComponentClass
{
	
}

class PS_SleepResistComponent : ScriptComponent
{
	
}

