modded class PS_GameModeCoop
{
	[RplProp()]
	bool m_bFreezeTimeEnd = false;
	
	override void removeRestrictedZones()
	{
		super.removeRestrictedZones();
		
		m_bFreezeTimeEnd = true;
		Replication.BumpMe();
	}
}

// Best way possible
modded class PS_FreezeTimeCounter
{
	static int s_iCurrentFreezeTime = int.MAX;
	
	override void SetTime(int time)
	{
		super.SetTime(time);
		s_iCurrentFreezeTime = time;
	}
}