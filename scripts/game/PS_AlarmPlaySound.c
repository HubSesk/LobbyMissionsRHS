class PS_AlarmPlaySoundClass: ScriptComponentClass
{
};

class PS_AlarmPlaySound: ScriptComponent
{
	[Attribute("")]
	protected string m_sEventName;
	
	[RplProp(), Attribute()]
	protected float m_fPlayTime;
	protected bool m_bPlaying;
	
	SoundComponent m_SoundComponent;
	
	override void OnPostInit(IEntity owner) {
		m_SoundComponent = SoundComponent.Cast(owner.FindComponent(SoundComponent));
		SetEventMask(owner, EntityEvent.FRAME);
	};

	override void EOnFrame(IEntity owner, float timeSlice) {
		if (m_fPlayTime >= 0 && Replication.IsServer() && m_bPlaying)
		{
			m_fPlayTime -= timeSlice;
			Replication.BumpMe();
		}
		
		if (m_fPlayTime <= 0)
		{
			if (m_SoundComponent)
				m_SoundComponent.TerminateAll();
			ClearEventMask(owner, EntityEvent.FRAME);
			return;
		}
		
		if (!m_SoundComponent)
			return;
		
		if (PS_FreezeTimeCounter.s_iCurrentFreezeTime > 50000 || m_SoundComponent.IsPlaying() || m_bPlaying)
			return;	
		
		if (m_SoundComponent)
		{
			m_SoundComponent.SoundEvent(m_sEventName);
			GetGame().GetCallqueue().CallLater(m_SoundComponent.TerminateAll, m_fPlayTime*1000, false)
		}
		
		m_bPlaying = true;
	};
};