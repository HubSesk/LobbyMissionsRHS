class PS_DispositionBoxWidgetComponent : SCR_ScriptedWidgetComponent
{
	[Attribute("10")]
	float m_fLifeTime;
	
	[Attribute("1")]
	float m_fFadeSpeed;
	
	bool m_bShow = true;
	
	//------------------------------------------------------------------------------------------------
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);
		if (GetGame().InPlayMode())
			m_wRoot.SetOpacity(0);
		GetGame().GetCallqueue().CallLater(Update, 0, true);
	}
	
	void Update()
	{
		float timeSlice = GetGame().GetWorld().GetTimeSlice();
		m_fLifeTime -= timeSlice;
		if (m_fLifeTime < 0)
			m_bShow = false;
		
		if (m_bShow)
			m_wRoot.SetOpacity(Math.Min(1, m_wRoot.GetOpacity() + timeSlice*m_fFadeSpeed));
		else
		{
			m_wRoot.SetOpacity(Math.Max(0, m_wRoot.GetOpacity() - timeSlice*m_fFadeSpeed));
			if (m_wRoot.GetOpacity() <= 0)
				m_wRoot.RemoveFromHierarchy();
		}
	}
}
