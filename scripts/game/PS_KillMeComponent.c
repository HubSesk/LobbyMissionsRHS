[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class PS_KillMeComponentClass : ScriptComponentClass
{
}

class PS_KillMeComponent : ScriptComponent
{
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		GetGame().GetCallqueue().Call(KillLater);
	}
	
	//------------------------------------------------------------------------------------------------
	void KillLater()
	{
		SCR_ChimeraCharacter character = SCR_ChimeraCharacter.Cast(GetOwner());
		character.GetCharacterController().ForceDeath();
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT);
	}
}
