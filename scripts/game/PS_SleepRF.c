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
		if (m_GameModeCoop.m_bFreezeTimeEnd)
		{
			ClearEventMask(owner, EntityEvent.FRAME);
			return;
		}
		
		IEntity character = SCR_PlayerController.GetLocalControlledEntity();
		if (!character)
			return;
		
		SCR_FactionAffiliationComponent factionAffiliationComponent = SCR_FactionAffiliationComponent.Cast(character.FindComponent(SCR_FactionAffiliationComponent));
		if (!factionAffiliationComponent)
			return;
		
		Faction faction = factionAffiliationComponent.GetDefaultAffiliatedFaction();
		if (faction.GetFactionKey() != "RHS_RF_MSV")
			return;
		
		SCR_EGameModeState gameModeState = m_GameModeCoop.GetState();
		if (gameModeState == SCR_EGameModeState.GAME)
		{
			MenuBase topMenu = GetGame().GetMenuManager().GetTopMenu();
			if (!topMenu)
			{
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