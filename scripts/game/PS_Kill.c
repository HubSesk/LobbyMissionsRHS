[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class PS_KillComponentClass : ScriptComponentClass
{
}

class PS_KillComponent : ScriptComponent
{
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		GetGame().GetCallqueue().CallLater(Kill, 0, true, owner);
	}
	
	int m_iTimer = 6;
	void Kill(IEntity owner)
	{
		if (m_iTimer > 0)
		{
			m_iTimer--;
			return;
		}
		
		SCR_ChimeraCharacter chimeraCharacter = SCR_ChimeraCharacter.Cast(owner);
		SCR_DamageManagerComponent damageManagerComponent = chimeraCharacter.GetDamageManager();
		HitZone hitZone = damageManagerComponent.GetDefaultHitZone();
		hitZone.HandleDamage(90000.0, EDamageType.MELEE, owner);
		
		GetGame().GetCallqueue().Remove(Kill);
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		if (Replication.IsServer())
			SetEventMask(owner, EntityEvent.INIT);
	}
}
