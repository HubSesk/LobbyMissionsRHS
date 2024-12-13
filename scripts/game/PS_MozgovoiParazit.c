// Не комить меня пожалуйста
// Иначе в РХС-е жепу оторвут

[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class PS_MozgovoiParazitComponentClass : ScriptComponentClass
{
}

class PS_MozgovoiParazitComponent : ScriptComponent
{
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT);
	}
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		GetGame().GetCallqueue().Call(Delay);
	}
	
	//------------------------------------------------------------------------------------------------
	void Delay()
	{
		GetGame().GetPlayerController().SetControlledEntity(GetOwner());
	}
}
