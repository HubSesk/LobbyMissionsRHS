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